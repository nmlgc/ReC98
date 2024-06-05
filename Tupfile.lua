-- Tupfile for the 32-part of the build process
-- --------------------------------------------

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

---@alias TupInput string | { [1]: string, extra_inputs: string | string[] }
---@alias ReC98Input string | { [1]: string, extra_inputs: string | string[], o?: string}

---@class (exact) ConfigShape
---@field obj_root? string Root directory for all intermediate files
---@field bin_root? string Root directory for shipped binaries
---@field aflags? string

---@class Config
local Config = {
	obj_root = "obj/",
	bin_root = "bin/",
	aflags = "/m /mx /kh32768 /t",
}
Config.__index = Config

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
		local cmd = string.format(
			"tasm32 %s %s %%o", self.aflags, fn:gsub("/", "\\")
		)
		return tup.rule(input, cmd, out_file:gsub("/", "\\"))[1]
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
	end
	return ret
end

---@param inputs ReC98Input[]
function Config:link(exe_stem, inputs)
	local objs = self:build(inputs)
end

-- Pipeline
-- --------

local pipeline_cfg = Config:branch(Subdir("Pipeline/"), {
	cflags = "-IPipeline/",
})

local bmp2arr = tup.rule(
	{ "Pipeline/bmp2arr.c", "Pipeline/bmp2arrl.c" },
	"bcc32 -w-8004 -w-8012 -O2 -v- -x- -nbin/Pipeline/ %f",
	{ "bin/Pipeline/bmp2arr.exe", extra_outputs = {
		"%O.tds", "bin/Pipeline/%1B.obj", "bin/Pipeline/%2B.obj"
	} }
)[1]

---@class BMPShape
---@field [1] string Input .BMP file
---@field [2] "asm" | "cpp" Output format
---@field [3] string Symbol
---@field [4] integer Width
---@field [5] integer Height
---@field [6] string? Additional arguments

---@param bmp BMPShape
---@return string
function BMP(bmp)
	local out_fn = bmp[1]:gsub("%..+$", (bmp[2] == "asm" and ".asp" or ".csp"))
	local inputs = { bmp[1], extra_inputs = bmp2arr }
	local sym = ((bmp[2] == "asm" and "_" or "") .. bmp[3])
	local additional = ((bmp[6] and (" " .. bmp[6])) or "")
	local cmd = string.format(
		"%s -q -i %%f -o %%o -sym %s -of %s -sw %d -sh %d%s",
		bmp2arr:gsub("/", "\\"), sym, bmp[2], bmp[4], bmp[5], additional
	)
	return tup.rule(inputs, cmd, out_fn)[1]
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
