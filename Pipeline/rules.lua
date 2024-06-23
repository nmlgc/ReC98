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
		local ECHO = "echo"
		if (rule.tool == ECHO) then
			local rsp_ext = cmd:match(".@(.)$")

			-- Two spaces rather than one are, in fact, necessary to increase
			-- the stability of TCC's optimizer in very rare cases? Not doing
			-- this ends up inserting a bunch of useless instructions into the
			-- TH01 Elis translation unit, but only on 32-bit Windows 10.
			-- Really, I couldn't make this up.
			if (rsp_ext == "c") then
				cmd = cmd:gsub(" ", "  ")
			end
		end
		print(string.format("$ %s %s", rule.tool:gsub("/", "\\"), cmd))
	end
end
