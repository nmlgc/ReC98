---@alias TupInput string | { [1]: string, extra_inputs: string | string[] }
---@alias TupOutput string | { [1]: string, extra_outputs: string | string[] }

---@class (exact) Rule
---@field inputs string[]
---@field tool string
---@field args string

---ReC98-specific reimplementation of `tup generate` in Lua. Wraps `tup.rule()`
---and transforms the rules into a full dumb sequential batch file, but with
---the following benefits to create an ideal native 16-/32-bit build:
---
---* Automatic slash-to-backslash conversion for tool filenames
---* Emits `mkdir` commands for *all* referenced output directories, not just
---  the ones that are missing from the current working tree.
---* Bundles all single-file TCC invocations that share the same compiler flags
---  into a single batched one
---* Splits long `echo` lines to fit within Windows 9x limits.
---
---Since Tup forbids writing files from the Tupfile, we have to abuse stdout
---to get the transformed rules back into the repo. All rule lines are printed
---with a fixed prefix, which is then filtered and redirected into the final
---batch file inside `build.bat`.
---@class Rules
---@field private rules Rule[]
---@field private outdirs table<string, boolean> Set of output directories
---@field private batch_root string Root directory for TCC batch response files
---@field private tcc_batch table<string, Rule> Command-line arguments → rule that receives all input files compiled with these arguments
---@field private tcc_batch_count number Because # only works with sequential tables
local Rules = {}
Rules.__index = Rules

---@param batch_root string
function NewRules(batch_root)
	---@type Rules
	local ret = {
		rules = {},
		outdirs = {},
		batch_root = batch_root,
		tcc_batch = {},
		tcc_batch_count = 0,
	}
	return setmetatable(ret, Rules)
end

---@private
---@param inputs TupInput
---@param tool string
---@param args string
---@param outputs TupOutput
---@return string cmd
function Rules:insert(inputs, tool, args, outputs)
	---@type string[]
	local ins = {}
	---@type string[]
	local outs = {}

	-- Using the function instead of `+=` preserves the `string[]` type in the
	-- LSP.
	tup_append_assignment(ins, inputs)
	tup_append_assignment(outs, outputs)

	local replace_table = { f = inputs, i = inputs.extra_inputs }
	args = args:gsub("%%(%d+)([fi])", function (i, type)
		return replace_table[type][tonumber(i)]
	end)
	args = args:gsub("%%o", table.concat(outs, " "))

	tup_append_assignment(outs, outputs.extra_outputs)
	for _, output in ipairs(outs) do
		local dir = output:gsub("/", "\\"):match("(.*)\\")
		if (dir ~= nil) then
			self.outdirs[dir] = true
		end
	end

	if (tool == "tcc") then
		local batch = self.tcc_batch[args]
		if batch == nil then
			local rsp_fn = string.format(
				"%sbatch%03d.@c", self.batch_root, self.tcc_batch_count
			)
			batch = {
				inputs = ins,
				tool = "echo",
				args = string.format("%s>%s", args, rsp_fn:gsub("/", "\\")),
			}
			table.insert(self.rules, batch)
			table.insert(self.rules, {
				inputs = { rsp_fn }, tool = "tcc", args = "@%f",
			})
			self.tcc_batch[args] = batch
			self.tcc_batch_count = (self.tcc_batch_count + 1)
		else
			batch.inputs += ins
		end
	else
		local rule = { inputs = ins, tool = tool, args = args }
		table.insert(self.rules, rule)
	end
	return string.format("%s %s", tool, args)
end

---Adds a rule for a 32-bit build tool.
---@param inputs TupInput
---@param tool string
---@param args string
---@param outputs TupOutput
---@return string[]
function Rules:add_32(inputs, tool, args, outputs)
	return tup.rule(inputs, self:insert(inputs, tool, args, outputs), outputs)
end

---Splits `line` into multiple lines to work around the no longer documented
---parsing craziness that Windows 9x's `COMMAND.COM` blindly performs before
---executing any line of a batch file:
---
---* Truncate to 1023 bytes
---* Parse out redirector
---* Strip trailing whitespace of remaining line
---* Split line into up to 64 tokens, around/excluding whitespace and '=' and
---  before/including '/'
---* Throw a `Bad command or file name` error once the token count would reach
---  65, regardless of whether the command would actually need the tokens
---@param line string
---@param sub_bytes number | nil Subtracted from 1023.
---@param sub_args number | nil Subtracted from 64.
---@return fun(): string | nil,boolean it Iterator over the split lines, plus an indicator of whether the current string is the final one
local function split_batch_line_for_win9x(line, sub_bytes, sub_args)
	local max_bytes = (1023 - ((sub_bytes and sub_bytes) or 0))
	local max_args = (64 - ((sub_args and sub_args) or 0))
	local switchar = string.byte("/")
	local equals = string.byte("=")

	---@param chunk string
	local function cut(chunk)
		---@type integer | nil
		local prev_end = nil

		local argc = 0
		local cur_start, cur_end = chunk:find("%S+")
		while ((cur_start ~= nil) and (cur_end ~= nil)) do
			local cur_argc = 0
			for i = (cur_start + 1), (cur_end - 1) do
				local c = chunk:byte(i)
				if ((c == switchar) or (c == equals)) then
					cur_argc = (cur_argc + 1)

					-- Subtracting 1 because the surrounding word may or may
					-- not be OK.
					if ((argc + cur_argc) >= (max_args - 1)) then
						-- Back up to the previous word if we can…
						if (prev_end and (cur_argc < max_args)) then
							return chunk:sub(1, prev_end)
						end

						-- …or split the string inside the word. Only here for
						-- tests, as it would corrupt the response files if it
						-- ever happened.
						return chunk:sub(1, (i - 1))
					end
				end
			end

			-- Separator characters are fine? Yield up to the entire word
			argc = (argc + cur_argc + 1)
			if (argc >= max_args) then
				return chunk:sub(1, cur_end)
			end
			prev_end = cur_end
			cur_start, cur_end = chunk:find("%S+", (cur_end + 1))
		end
		return chunk
	end

	---@type string
	line = line:match("%s*(.*)%s*$")

	return function ()
		if (#line == 0) then
			return nil, true
		end

		local chunk
		if (#line > max_bytes) then
			chunk = cut(line:sub(0, (max_bytes + 1)):match("(.+) "))
		else
			chunk = cut(line:sub(0, max_bytes))
		end
		line = line:sub(chunk:len() + 1):match("%s*(.*)%s*$")
		return chunk, (#line == 0)
	end
end

---Prints the current rules to stdout.
function Rules:print()
	print([[
$ : Dumb, full batch build script for 32-bit systems that can't run Tup, but can
$ : natively run DOS-based tools. Automatically generated whenever `Tupfile.lua`
$ : is modified.
$ @echo off
]])
	local outdirs_sorted = {}
	for dir in pairs(self.outdirs) do
		table.insert(outdirs_sorted, dir)
	end
	table.sort(outdirs_sorted)
	for _, dir in pairs(outdirs_sorted) do
		print(string.format("$ mkdir %s %%STDERR_IGNORE%%", dir))
	end

	for _, rule in pairs(self.rules) do
		local cmd = rule.args:gsub("%%f", table.concat(rule.inputs, " "))

		-- Work around command line length limits by splitting long `echo`
		-- lines. This also must be done for the link response files used for
		-- the regular Tup build.
		local ECHO = "echo"
		if (rule.tool == ECHO) then
			local redirector = ">"

			---@type string, string
			local args, fn = cmd:match("(.*)>(.+)")

			local rsp_ext = fn:match(".@(.)$")

			-- Two spaces rather than one are, in fact, necessary to increase
			-- the stability of TCC's optimizer in very rare cases? Not doing
			-- this ends up inserting a bunch of useless instructions into the
			-- TH01 Elis translation unit, but only on 32-bit Windows 10.
			-- Really, I couldn't make this up.
			if (rsp_ext == "c") then
				args = args:gsub(" ", "  ")
			end

			-- Adding 2 to leave room for the longer `>>` redirector
			for chunk, final in split_batch_line_for_win9x(
				args, (ECHO:len() + 1 + fn:len() + 2), 1
			) do
				-- TLINK response files need some separate massaging when split
				-- into multiple lines.
				if (rsp_ext == "l") then
					if chunk:sub(-1) == "," then
						chunk = chunk:sub(0, (chunk:len() - 1))
					elseif not final then
						chunk = (chunk .. "+")
					end
				end

				print(string.format("$ %s %s%s%s", ECHO, chunk, redirector, fn))
				redirector = ">>"
			end
		else
			print(string.format("$ %s %s", rule.tool:gsub("/", "\\"), cmd))
		end
	end
end
