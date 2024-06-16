---@alias TupInput string | { [1]: string, extra_inputs: string | string[] }
---@alias TupOutput string | { [1]: string, extra_outputs: string | string[] }

---@class (exact) Rule
---@field inputs string[]
---@field tool string
---@field args string

---ReC98-specific reimplementation of `tup generate` in Lua. Wraps `tup.rule()`
---and transforms the rules into a full dumb sequential batch file, but with
---the following benefits:
---
---* Automatic slash-to-backslash conversion for tool filenames
---* Emits `mkdir` commands for *all* referenced output directories, not just
---  the ones that are missing from the current working tree.
---
---Since Tup forbids writing files from the Tupfile, we have to abuse stdout
---to get the transformed rules back into the repo. All rule lines are printed
---with a fixed prefix, which is then filtered and redirected into the final
---batch file inside `build.bat`.
---@class Rules
---@field private rules Rule[]
---@field private outdirs table<string, boolean> Set of output directories
local Rules = {}
Rules.__index = Rules

function NewRules()
	---@type Rules
	local ret = {
		rules = {},
		outdirs = {},
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

	local rule = { inputs = ins, tool = tool, args = args }
	table.insert(self.rules, rule)
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
		print(string.format("$ %s %s", rule.tool:gsub("/", "\\"), cmd))
	end
end
