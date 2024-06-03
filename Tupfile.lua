--[[








⚠️ CAUTION! ⚠️

You are on the `master` branch, which builds PC-98 DOS binaries that are
identical to ZUN's originally released binaries. If you want to port the game
to other architectures or develop a mod that doesn't need to be byte-for-byte
comparable to the original binary, start from the cleaned-up `debloated` branch
instead. That branch is easier to read and modify, and builds smaller and
slightly faster PC-98 binaries while leaving all bugs and quirks from ZUN's
original code in place.
Seriously, you'd just be torturing yourself if you do anything nontrivial based
on this branch.

⚠️ CAUTION! ⚠️







--]]

---@alias ReC98Input string | { [1]: string, extra_inputs: string | string[], o?: string}

tup.include("Pipeline/rules.lua")

---@class (exact) ConfigShape
---@field obj_root? string Root directory for all intermediate files
---@field bin_root? string Root directory for shipped binaries
---@field aflags? string
---@field cflags? string
---@field lflags? string

---@class Config
local Config = {
	obj_root = "obj/",
	bin_root = "bin/",
	aflags = "/m /mx /kh32768 /t",
	cflags = "-I. -O -b- -3 -Z -d",
	lflags = "-s",
}
Config.__index = Config

local Rules = NewRules(Config.obj_root)

MODEL_TINY = { cflags = "-mt", lflags = "-t" }

---Generates a ConfigShape for an output subdirectory.
---@param dir string
---@return ConfigShape
function Subdir(dir)
	return { obj_root = dir, bin_root = dir }
end

---Maps each source filename to its compiled object file. Allows the same
---source file to be listed in multiple binaries – later occurrences get
---replaced with the previous build output.
---@type { [string]: string }
local PreviousOutputForSource = {}

---@param ... ConfigShape
function Config:branch(...)
	local arg = { ... }

	---@class Config
	local ret = setmetatable({}, self)
	ret.__index = self

	for field, value in pairs(self) do
		ret[field] = value
		for _, other in pairs(arg) do
			if other[field] then
				-- By only space-separating flags, we allow custom directories.
				if (field:sub(-5) == "flags") then
					ret[field] = (ret[field] .. " " .. other[field])
				else
					ret[field] = (ret[field] .. other[field])
				end
			end
		end
	end
	return ret
end

---@param input ReC98Input
function Config:build_uncached(input)
	local fn = ((type(input) == "string" and input) or input[1])
	local out_basename = (tup.base(fn):gsub("th0%d_", "") .. ".obj")
	if input.o then
		out_basename = input.o
		input.o = nil
	end
	local out_file = (self.obj_root .. out_basename)

	local ext = tup.ext(fn)
	if (ext == "asm") then
		-- We can't use %f since TASM32 wants backslashes and Tup would
		-- automatically rewrite them to slashes.
		local args = string.format("%s %s %%o", self.aflags, fn:gsub("/", "\\"))
		return Rules:add_32(input, "tasm32", args, out_file:gsub("/", "\\"))[1]
	elseif ((ext == "c") or (ext == "cpp")) then
		local args = string.format("-c %s -n%s %%f", self.cflags, self.obj_root)
		return Rules:add_16(input, "tcc", args, out_file)[1]
	elseif ((ext == "obj") or (ext == "lib")) then
		return fn
	end
	error(string.format("Unknown file extension, can't build: `%s`", fn))
end

---@param inputs ReC98Input[]
---@return string[]
function Config:build(inputs)
	local ret = {}
	for _, input in pairs(inputs) do
		local fn = ((type(input) == "string" and input) or input[1])

		local output = PreviousOutputForSource[fn]
		if (output == nil) then
			output = self:build_uncached(input)
			PreviousOutputForSource[fn] = output
		end
		ret += { output }
	end
	return ret
end

---@param inputs ReC98Input[]
function Config:link(exe_stem, inputs)
	local model_c = self.cflags:match("-m([tsmclh])")
	local objs = self:build(inputs)
	if model_c == nil then
		return
	end

	local obj_root = self.obj_root:gsub("/", "\\")
	local bin_root = self.bin_root:gsub("/", "\\")

	local ext = (self.lflags:find("-t") and ".com" or ".exe")
	local rsp_fn = string.format("%s%s.@l", obj_root, exe_stem)
	local map_fn = string.format("%s%s.map", obj_root, exe_stem)
	local bin_fn = string.format("%s%s%s", bin_root, exe_stem, ext)

	-- When TCC spawns TLINK, it writes the entire link command line into a
	-- file with the fixed name `turboc.$ln`. This can't ever work with
	-- parallel builds, so we have to replicate TCC's response file generation
	-- ourselves here.
	-- This not only saves one emulated process spawn call, but also gives us
	-- full control over the linker command line, allowing us to place the map
	-- file under `obj/` rather than next to the binary in `bin/`.
	-- Thankfully, we can even omit the directory for Borland's C standard
	-- library and rely on `TLINK.CFG` to supply it. Deriving it from the
	-- `PATH` would be quite annoying on Windows 9x…
	local lflags = string.format("-c %s ", self.lflags)
	if model_c then
		lflags = string.format("%sc0%s.obj", lflags, model_c)
	end

	-- Can't use %f because we need backslashes…
	local libs = ""
	for _, obj in pairs(objs) do
		if (obj:sub(-4) == ".lib") then
			libs = (libs .. obj:gsub("/", "\\") .. " ")
		else
			lflags = (lflags .. " " .. obj:gsub("/", "\\"))
		end
	end
	lflags = string.format("%s, %s, %s, %s", lflags, bin_fn, map_fn, libs)
	if model_c then
		local model_math = (model_c == "t" and "s" or model_c)
		lflags = string.format(
			"%semu.lib math%s.lib c%s.lib", lflags, model_math, model_c
		)
	end
	objs += Rules:add_32({}, "echo", (lflags .. ">%o"), rsp_fn)

	local outputs = { bin_fn, map_fn }
	return Rules:add_16(objs, "tlink", ("@" .. rsp_fn), outputs)[1]
end

-- Additional generally good compilation flags. Should be used for all code
-- that does not need to match the original binaries.
local optimized_cfg = Config:branch({ cflags = "-G -k- -p -x-" })

-- Pipeline
-- --------

local pipeline_cfg = optimized_cfg:branch(Subdir("Pipeline/"), {
	cflags = "-IPipeline/",
})

local pipeline_tool_cfg = pipeline_cfg:branch(MODEL_TINY)

local bmp2arr = pipeline_tool_cfg:link("bmp2arr", {
	"Pipeline/bmp2arrl.c",
	"Pipeline/bmp2arr.c",
})

---@class BMPShape
---@field [1] string Input .BMP file
---@field [2] "asm" | "cpp" Output format
---@field [3] string Symbol
---@field [4] integer Width
---@field [5] integer Height
---@field [6] string? Additional arguments

---@param bmp BMPShape
function BMP(bmp)
	local out_fn = bmp[1]:gsub("%..+$", (bmp[2] == "asm" and ".asp" or ".csp"))
	local inputs = { bmp[1], extra_inputs = bmp2arr }
	local sym = ((bmp[2] == "asm" and "_" or "") .. bmp[3])
	local additional = ((bmp[6] and (" " .. bmp[6])) or "")
	local args = string.format(
		"-q -i %%f -o %%o -sym %s -of %s -sw %d -sh %d%s",
		sym, bmp[2], bmp[4], bmp[5], additional
	)
	return Rules:add_16(inputs, bmp2arr, args, out_fn)[1]
end

---@param bmps BMPShape[]
---@return table<string, string> sprites Sprite basename → source file
function Sprites(bmps)
	local ret = {}
	for _, bmp in pairs(bmps) do
		ret[tup.base(bmp[1])] = BMP(bmp)
	end
	return ret
end

local zun_stub = pipeline_cfg:build({ "Pipeline/zun_stub.asm" })
local cstmstub = pipeline_cfg:build({ "Pipeline/cstmstub.asm" })

---@param bin_fn string
---@param procs [string, string][] [Menu name, input filename]
function Config:zungen(bin_fn, procs)
end
-- --------

-- Third-party libraries
-- ---------------------

local piloadc = Config:branch({ aflags = "/ml" }):build({
	"libs/piloadc/piloadc.asm"
})[1]
local sprite16 = Config:branch({ aflags = "/dTHIEF" }):build({
	{ "libs/sprite16/sprite16.asm", o = "th03/zunsp.obj" }
})[1]
-- ---------------------

-- Games
-- -----

---@param game number
function GameShape(game)
	local ret = Subdir(string.format("th0%d/", game))
	ret.aflags = string.format("/dGAME=%d", game)
	return ret
end

local th01 = Config:branch(GameShape(1))
local th02 = Config:branch(GameShape(2))
local th03 = Config:branch(GameShape(3))
local th04 = Config:branch(GameShape(4))
local th05 = Config:branch(GameShape(5))
-- -----

-- TH01
-- ----

local th01_sprites = Sprites({
	{ "th01/sprites/leaf_s.bmp", "cpp", "sSPARK", 8, 8 },
	{ "th01/sprites/leaf_l.bmp", "cpp", "sLEAF_LEFT", 8, 8 },
	{ "th01/sprites/leaf_r.bmp", "cpp", "sLEAF_RIGHT", 8, 8 },
	{ "th01/sprites/ileave_m.bmp", "cpp", "sINTERLEAVE_MASKS", 8, 8 },

	-- ZUN bug: Supposed to be 8 preshifted sprites, with a height of 1 and a
	-- width of SHOOTOUT_LASER_MAX_W pixels each, but ZUN messed up a single
	-- pixel in the first pre-shifted sprite.
	-- So, we're forced to manually unroll them…
	{ "th01/sprites/laser_s.bmp", "cpp", "sSHOOTOUT_LASER", 16, 8 },

	{ "th01/sprites/mousecur.bmp", "cpp", "sMOUSE_CURSOR", 16, 16 },
	{ "th01/sprites/pellet.bmp", "cpp", "sPELLET", 8, 8, "-pshf inner" },
	{ "th01/sprites/pellet_c.bmp", "cpp", "sPELLET_CLOUD", 16, 16 },
	{ "th01/sprites/pillar.bmp", "cpp", "sPILLAR", 32, 8 },
	{ "th01/sprites/shape8x8.bmp", "cpp", "sSHAPE8X8", 8, 8 },
	{ "th01/sprites/bonusbox.bmp", "cpp", "sSTAGEBONUS_BOX", 8, 4 },
})

th01:link("op", {
	"th01_op.asm",
})
th01:link("reiiden", {
	"th01_reiiden.asm",
})
th01:link("fuuin", {
	"th01_fuuin.asm",
})
-- ----

-- TH02
-- ----

local th02_sprites = Sprites({
	{ "th02/sprites/bombpart.bmp", "asm", "sBOMB_PARTICLES", 8, 8 },
	{ "th02/sprites/pellet.bmp", "asm", "sPELLET", 8, 8, "-pshf outer" },
	{ "th02/sprites/sparks.bmp", "asm", "sSPARKS", 8, 8, "-pshf outer" },
	{ "th02/sprites/pointnum.bmp", "asm", "sPOINTNUMS", 8, 8 },
	{ "th02/sprites/verdict.bmp", "cpp", "sVERDICT_MASKS", 16, 16 },
})

local th02_zuninit = th02:link("zuninit", {
	"th02_zuninit.asm",
})
th02:link("op", {
	"th02_op.asm",
})
th02:link("main", {
	{ "th02_main.asm", extra_inputs = {
		th02_sprites["pellet"],
		th02_sprites["bombpart"],
		th02_sprites["sparks"],
		th02_sprites["pointnum"],
	} },
})
th02:link("maine", {
	"th02_maine.asm",
})
-- ----

-- TH03
-- ----

local th03_sprites = Sprites({
	{ "th03/sprites/score.bmp", "asm", "sSCORE_FONT", 8, 8, "-u" },
})

th03:zungen("bin/th03/zun.com", {
	{ "-4", th03:link("zunsp", { sprite16 }) },
})
th03:link("op", {
	"th03_op2.asm",
	"th03_op.asm",
	"th03/cdg_put.asm",
	"th03/cdg_p_na.asm",
	"th03/hfliplut.asm",
})
th03:link("main", {
	{ "th03_main.asm", extra_inputs = th03_sprites["score"] },
	"th03/collmap.asm",
	"th03/hfliplut.asm",
})
th03:link("mainl", {
	"th03_mainl.asm",
	"th03/cdg_put.asm",
	"th03/cdg_p_na.asm",
	"th03/hfliplut.asm",
})
-- ----

-- TH04
-- ----

local th04_sprites = Sprites({
	{"th04/sprites/pelletbt.bmp", "asm", "sPELLET_BOTTOM", 8, 4, "-pshf outer"},
	{"th04/sprites/pointnum.bmp", "asm", "sPOINTNUMS", 8, 8, "-pshf inner"},
})

local th04_zuncom = th04:zungen("obj/th04/zuncom.bin", {
	{ "-I", th04:link("zuninit", { "th04_zuninit.asm" }) },
	{ "-M", th04:link("memchk", { "th04_memchk.asm" }) },
})
th04:link("op", {
	{ "th04_op_master.asm", o = "opm.obj" },
	"th03/hfliplut.asm",
	"th04/cdg_p_nc.asm",
	"th04/grppsafx.asm",
	"th04_op2.asm",
	"th04/cdg_put.asm",
	"th04/input_s.asm",
	"th04/bgimager.asm",
	"th04/cdg_load.asm",
	"th04_op.asm",
})
th04:link("main", {
	{ "th04_main.asm", extra_inputs = {
		th02_sprites["pellet"],
		th02_sprites["sparks"],
		th04_sprites["pelletbt"],
		th04_sprites["pointnum"],
	} },
	"th04/scoreupd.asm",
	"th03/hfliplut.asm",
	"th04/cdg_put.asm",
	"th04/cdg_p_pr.asm",
	"th04/input_s.asm",
	"th04/cdg_load.asm",
	"th04/motion_3.asm",
	"th04/vector2n.asm",
	"th04/spark_a.asm",
})
th04:link("maine", {
	{ "th04_maine_master.asm", o = "mainem.obj" },
	"th03/hfliplut.asm",
	"th04/cdg_p_pl.asm",
	"th04/grppsafx.asm",
	"th04_maine.asm",
	"th04/cdg_put.asm",
	"th04/input_s.asm",
	"th04/bgimager.asm",
	"th04/cdg_load.asm",
})
-- ----

-- TH05
-- ----

local th05_sprites = Sprites({
	{ "th05/sprites/gaiji.bmp", "asm", "sGAIJI", 16, 16 },
	{ "th05/sprites/piano_l.bmp", "asm", "sPIANO_LABEL_FONT", 8, 8 },
})

local th05_zuncom = th05:zungen("obj/th05/zuncom.bin", {
	{ "-I", th05:link("zuninit", { "th05_zuninit.asm" }) },
	{ "-G", th05:link("gjinit", {
		{ "th05_gjinit.asm", extra_inputs = th05_sprites["gaiji"] },
	}) },
	{ "-M", th05:link("memchk", { "th05_memchk.asm" }) },
})
th05:link("op", {
	{ "th05_op_master.asm", o = "opm.obj" },
	"th03/hfliplut.asm",
	"th04/grppsafx.asm",
	{ "th05_op2.asm", extra_inputs = th05_sprites["piano_l"] },
	"th05/cdg_put.asm",
	"th05/musicp_a.asm",
	"th05/bgimager.asm",
	"th05/pi_asm_1.asm",
	"th05/pi_asm_2.asm",
	"th05/input_s.asm",
	"th04/cdg_load.asm",
	"th05_op.asm",
})
th05:link("main", {
	{ "th05_main.asm", extra_inputs = {
		th02_sprites["pellet"],
		th02_sprites["sparks"],
		th04_sprites["pelletbt"],
		th04_sprites["pointnum"],
	} },
	"th05/player.asm",
	"th05/hud_bar.asm",
	"th05/scoreupd.asm",
	"th04/vector2n.asm",
	"th05/spark_a.asm",
	"th05/bullet_1.asm",
	"th05/bullet.asm",
	"th03/hfliplut.asm",
	"th05/cdg_put.asm",
	"th05/input_s.asm",
	"th04/cdg_load.asm",
	"th04/motion_3.asm",
})
th05:link("maine", {
	{ "th05_maine_master.asm", o = "mainem.obj" },
	"th03/hfliplut.asm",
	"th04/grppsafx.asm",
	"th05_maine.asm",
	"th05/bgimager.asm",
	"th05/pi_asm_1.asm",
	"th05/pi_asm_2.asm",
	"th05/input_s.asm",
	"th04/cdg_load.asm",
})
-- ----

-- Research
-- --------

local research_sprites = Sprites({
	{ "Research/blitperf.bmp", "cpp", "sBLITPERF", 16, 16 }
})
-- --------

Rules:print()
