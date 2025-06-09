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

MODEL_ASM = { lflags = "-t -3" }
MODEL_TINY = { cflags = "-mt", lflags = "-t" }
MODEL_SMALL = { cflags = "-ms" }

-- Currently, it only makes sense to enable extended dictionary processing for
-- binaries that don't link the original binary release of MASTERS.LIB, which
-- doesn't come with them.
MODEL_LARGE = { cflags = "-ml", lflags = "-E" }

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

---@param exe_stem string
---@param inputs ReC98Input[]
function Config:link(exe_stem, inputs)
	local model_c = self.cflags:match("-m([tsmclh])")
	local objs = self:build(inputs)

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
local pipeline_stub_cfg = pipeline_cfg:branch(MODEL_ASM)

pipeline_tool_cfg:link("grzview", {
	"Pipeline/grzview.cpp",
	"th01/formats/grz.cpp",
	"platform/x86real/pc98/palette.cpp",
	"bin/masters.lib",
})

local bmp2arr = pipeline_tool_cfg:link("bmp2arr", {
	"Pipeline/bmp2arrl.c",
	"Pipeline/bmp2arr.c",
})

---@class BMPShape
---@field [1] string Input .BMP file
---@field [2] "asm" | "c" | "cpp" Output format
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

---@param input string
function Config:stub(input)
	local obj_fn = self:build({ input })[1]
	local bin_fn = obj_fn:gsub("%..+$", ".bin")
	local args = string.format("-x -t %s, %s", obj_fn, bin_fn)
	return Rules:add_16(obj_fn, "tlink", args:gsub("/", "\\"), bin_fn)[1]
end

local zungen = pipeline_tool_cfg:link("zungen", { "Pipeline/zungen.c" })
local comcstm = pipeline_tool_cfg:link("comcstm", { "Pipeline/comcstm.c" })
local zun_stub = pipeline_stub_cfg:stub("Pipeline/zun_stub.asm")
local cstmstub = pipeline_stub_cfg:stub("Pipeline/cstmstub.asm")

---@param bin_fn string
---@param procs [string, string][] [Menu name, input filename]
function Config:zungen(bin_fn, procs)
	local rsp_fn = string.format(
		"%s%s.@z", self.obj_root, tup.base(bin_fn)
	):gsub("/", "\\")
	local inputs = { extra_inputs = { zungen, zun_stub, rsp_fn }}

	local names = ""
	local fns = ""
	for _, proc in pairs(procs) do
		inputs += { proc[2] }
		names = string.format("%s %s", names, proc[1])
		fns = string.format("%s %s", fns, proc[2])
	end

	Rules:add_32(
		{}, "echo", string.format("%d%s%s>%%o", #procs, names, fns), rsp_fn
	)
	return Rules:add_16(inputs, zungen, "%2i %3i %o", bin_fn)[1]
end

---@param out_basename string
---@param prog_fn string
---@param usage_fn string
---@param timestamp number
function Config:comcstm(out_basename, usage_fn, prog_fn, timestamp)
	local inputs = { comcstm, usage_fn, prog_fn, cstmstub }
	local cmd = string.format("%%2f %%3f %%4f %d %%o", timestamp)
	return Rules:add_16(
		inputs, comcstm, cmd, (self.bin_root .. out_basename)
	)[1]
end
-- --------

-- Third-party libraries
-- ---------------------

local piload_cfg = Config:branch({ aflags = "/ml" })
local piloadc = piload_cfg:build({ "libs/piloadc/piloadc.asm" })
local piloadm = piload_cfg:build({ "libs/piloadc/piloadm.asm" })
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
	ret.cflags = string.format("-DGAME=%d", game)
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

local th01_zunsoft = th01:branch(MODEL_TINY):link("zunsoft", {
	"th01/zunsoft.cpp",
	"bin/masters.lib",
})
th01:branch(MODEL_LARGE, { cflags = "-DBINARY='O'" }):link("op", {
	piloadc,
	"th01/op_01.cpp",
	"th01/frmdelay.cpp",
	{ "th01/vsync.cpp", extra_inputs = th01_sprites["mousecur"] },
	"th01/ztext.cpp",
	"th01/initexit.cpp",
	"th01/graph.cpp",
	"th01/ptn_0to1.cpp",
	"th01/vplanset.cpp",
	"th01/op_07.cpp",
	"th01/grp_text.cpp",
	"th01/ptn.cpp",
	"th01/op_09.cpp",
	"th01/f_imgd.cpp",
	"th01/grz.cpp",
	"th01_op.asm",
	"th01/resstuff.cpp",
	"th01/mdrv2.cpp",
	"th01/pf.cpp",
})
th01:branch(MODEL_LARGE, { cflags = "-DBINARY='M'" }):link("reiiden", {
	piloadc,
	"th01/main_01.cpp",
	"th01/frmdelay.cpp",
	{ "th01/vsync.cpp", extra_inputs = th01_sprites["mousecur"] },
	"th01/ztext.cpp",
	"th01/initexit.cpp",
	"th01/graph.cpp",
	"th01/ptn_0to1.cpp",
	"th01/vplanset.cpp",
	"th01/main_07.cpp",
	"th01/ptn.cpp",
	"th01/main_08.cpp",
	"th01/f_imgd.cpp",
	"th01/grz.cpp",
	"th01_reiiden.asm",
	{ "th01/main_09.cpp", extra_inputs = th01_sprites["pellet_c"] },
	"th01/bullet_l.cpp",
	"th01/grpinv32.cpp",
	"th01/resstuff.cpp",
	"th01/scrollup.cpp",
	"th01/egcrows.cpp",
	{ "th01/pgtrans.cpp", extra_inputs = th01_sprites["ileave_m"] },
	"th01/2x_main.cpp",
	"th01/egcwave.cpp",
	"th01/grph1to0.cpp",
	"th01/main_14.cpp",
	{ "th01/main_15.cpp", extra_inputs = th01_sprites["laser_s"] },
	"th01/mdrv2.cpp",
	"th01/main_17.cpp",
	{ "th01/main_18.cpp", extra_inputs = th01_sprites["bonusbox"] },
	"th01/main_19.cpp",
	"th01/main_20.cpp",
	"th01/main_21.cpp",
	"th01/pf.cpp",
	{ "th01/main_23.cpp", extra_inputs = th01_sprites["shape8x8"] },
	"th01/main_24.cpp",
	"th01/main_25.cpp",
	"th01/main_26.cpp",
	"th01/main_27.cpp",
	"th01/main_28.cpp",
	{ "th01/main_29.cpp", extra_inputs = th01_sprites["pillar"] },
	"th01/main_30.cpp",
	"th01/main_31.cpp",
	"th01/main_32.cpp",
	"th01/main_33.cpp",
	"th01/main_34.cpp",
	"th01/main_35.cpp",
	{ "th01/main_36.cpp", extra_inputs = {
		th01_sprites["leaf_s"],
		th01_sprites["leaf_l"],
		th01_sprites["leaf_r"],
	} },
	"th01/main_37.cpp",
	{ "th01/main_38.cpp", extra_inputs = th01_sprites["pellet"] },
})
th01:branch(MODEL_LARGE, { cflags = "-DBINARY='E'" }):link("fuuin", {
	piloadc,
	"th01/fuuin_01.cpp",
	"th01/input_mf.cpp",
	"th01/fuuin_02.cpp",
	"th01/fuuin_03.cpp",
	"th01/fuuin_04.cpp",
	{ "th01/vsync.cpp", extra_inputs = th01_sprites["mousecur"] },
	"th01/ztext.cpp",
	"th01/initexit.cpp",
	"th01/graph.cpp",
	"th01/grp_text.cpp",
	"th01/fuuin_10.cpp",
	"th01/f_imgd_f.cpp",
	"th01/vplanset.cpp",
	"th01/fuuin_11.cpp",
	"th01/2x_fuuin.cpp",
	"th01/mdrv2.cpp",
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

local th02_zuninit = th02:branch(MODEL_ASM):link("zuninit", {
	"th02_zuninit.asm",
})
th02:zungen("bin/th02/zun.com", {
	{ "ONGCHK", "libs/kaja/ongchk.com" },
	{ "ZUNINIT", th02_zuninit },
	{ "ZUN_RES", th02:branch(MODEL_TINY):link("zun_res", {
		"th02/zun_res1.cpp",
		"th02/zun_res2.cpp",
		"bin/masters.lib",
	}) },
	{ "ZUNSOFT", th01_zunsoft },
})
th02:branch(MODEL_LARGE, { cflags = "-DBINARY='O'" }):link("op", {
	"th02/op_01.cpp",
	"th02/exit_dos.cpp",
	"th02/zunerror.cpp",
	"th02/grppsafx.cpp",
	"th02_op.asm",
	"th01/vplanset.cpp",
	"th02/pi_load.cpp",
	"th02/grp_rect.cpp",
	"th02/frmdely2.cpp",
	"th02/input_rs.cpp",
	"th02/initop.cpp",
	"th02/exit.cpp",
	"th02/snd_mmdr.c",
	"th02/snd_mode.c",
	"th02/snd_pmdr.c",
	"th02/snd_load.cpp",
	"th02/pi_put.cpp",
	"th02/snd_kaja.cpp",
	"th02/op_02_3.cpp",
	"th02/snd_se_r.cpp",
	"th02/snd_se.cpp",
	"th02/frmdely1.cpp",
	"th02/op_03.cpp",
	"th02/globals.cpp",
	"th02/op_04.cpp",
	"th02/op_05.cpp",
	"th02/op_music.cpp",
})
th02:branch(MODEL_LARGE, { cflags = "-DBINARY='M'" }):link("main", {
	{ "th02_main.asm", extra_inputs = {
		th02_sprites["pellet"],
		th02_sprites["bombpart"],
		th02_sprites["sparks"],
		th02_sprites["pointnum"],
	} },
	"th02/spark.cpp",
	"th02/spark_i.asm",
	"th02/tile.cpp",
	"th02/pointnum.cpp",
	"th02/item.cpp",
	"th02/hud.cpp",
	"th02/player_b.cpp",
	"th02/player.cpp",
	"th02/zunerror.cpp",
	"th02/keydelay.cpp",
	"th02/main02_1.cpp",
	"th01/vplanset.cpp",
	"th02/pi_load.cpp",
	"th02/vector.cpp",
	"th02/frmdely1.cpp",
	"th02/input_rs.cpp",
	"th02/exit.cpp",
	"th02/snd_mmdr.c",
	"th02/snd_mode.c",
	"th02/snd_pmdr.c",
	"th02/snd_dlyv.c",
	"th02/snd_load.cpp",
	"th02/mpn_l_i.cpp",
	"th02/initmain.cpp",
	"th02/pi_put.cpp",
	"th02/snd_kaja.cpp",
	"th02/snd_dlym.cpp",
	"th02/snd_se_r.cpp",
	"th02/snd_se.cpp",
	"th02/main_03.cpp",
	"th02/hud_ovrl.cpp",
	"th02/bullet.cpp",
	"th02/dialog.cpp",
	"th02/boss_5.cpp",
	"th02/regist_m.cpp",
})
th02:branch(MODEL_LARGE, { cflags = "-DBINARY='E'" }):link("maine", {
	{ "th02/end.cpp", extra_inputs = th02_sprites["verdict"] },
	"th02_maine.asm",
	"th02/grppsafx.cpp",
	"th02/keydelay.cpp",
	"th01/vplanset.cpp",
	"th02/pi_load.cpp",
	"th02/frmdely1.cpp",
	"th02/maine022.cpp",
	"th02/input_rs.cpp",
	"th02/exit.cpp",
	"th02/snd_mmdr.c",
	"th02/snd_mode.c",
	"th02/snd_pmdr.c",
	"th02/snd_load.cpp",
	"th02/initmain.cpp",
	"th02/pi_put.cpp",
	"th02/snd_kaja.cpp",
	"th02/snd_dlym.cpp",
	"th02/globals.cpp",
	"th02/maine_03.cpp",
	"th02/maine_04.cpp",
	"th02/staff.cpp",
})
-- ----

-- TH03
-- ----

local th03_sprites = Sprites({
	{ "th03/sprites/score.bmp", "asm", "sSCORE_FONT", 8, 8, "-u" },

	-- ZUN bloat: Investing 32 bytes just so that the individual rows can be
	-- loaded with a 16-bit `MOV`…
	{ "th03/sprites/flake.bmp", "asm", "sFLAKE", 16, 8 },
})

th03:zungen("bin/th03/zun.com", {
	{ "-1", "libs/kaja/ongchk.com" },
	{ "-2", th02_zuninit },
	{ "-3", th01_zunsoft },
	{ "-4", th03:branch(MODEL_ASM):link("zunsp", { sprite16 }) },
	{ "-5", th03:branch(MODEL_TINY):link("res_yume", {
		"th03/res_yume.cpp",
		"bin/masters.lib",
	})}
})
th03:branch(MODEL_LARGE, { cflags = "-DBINARY='O'" }):link("op", {
	"th03/op_01.cpp",
	"th03_op.asm",
	"th03/op_music.cpp",
	"th03/op_main.cpp",
	"th03/op_02.cpp",
	"th03/scoredat.cpp",
	"th03/op_sel.cpp",
	"th02/exit_dos.cpp",
	"th01/vplanset.cpp",
	"th02/snd_mode.c",
	"th02/snd_pmdr.c",
	"th02/snd_load.cpp",
	"th03/exit.cpp",
	"th03/polar.cpp",
	"th03/cdg_put.asm",
	"th02/frmdely1.cpp",
	"th03/input_s.cpp",
	"th03/pi_put.cpp",
	"th03/snd_kaja.cpp",
	"th03/initop.cpp",
	"th03/cdg_load.cpp",
	"th03/grppsafx.cpp",
	"th03/pi_load.cpp",
	"th03/inp_m_w.cpp",
	"th03/cdg_p_na.asm",
	"th03/hfliplut.asm",
	"th02/frmdely2.cpp",
})
th03:branch(MODEL_LARGE, { cflags = "-DBINARY='M'" }):link("main", {
	{ "th03_main.asm", extra_inputs = th03_sprites["score"] },
	"th03/playfld.cpp",
	"th03/cfg_lres.cpp",
	"th03/hitcirc.cpp",
	"th03/hud_stat.cpp",
	"th03/player_m.cpp",
	"th03/main_010.cpp",
	"th03/main_011.cpp",
	"th01/vplanset.cpp",
	"th02/snd_mode.c",
	"th02/snd_pmdr.c",
	"th03/vector.cpp",
	"th03/exit.cpp",
	"th03/polar.cpp",
	"th02/frmdely1.cpp",
	"th03/input_s.cpp",
	"th02/snd_se_r.cpp",
	"th03/snd_se.cpp",
	"th03/snd_kaja.cpp",
	"th03/initmain.cpp",
	"th03/pi_load.cpp",
	"th03/inp_m_w.cpp",
	"th03/collmap.asm",
	"th03/hfliplut.asm",
	"th03/mrs.cpp",
	"th03/sprite16.cpp",
})
th03:branch(MODEL_LARGE, { cflags = "-DBINARY='L'" }):link("mainl", {
	"th03/cfg_lres.cpp",
	"th03/mainl_sc.cpp",
	{ "th03_mainl.asm", extra_inputs = th03_sprites["flake"] },
	"th03/cutscene.cpp",
	"th03/scoredat.cpp",
	"th03/regist.cpp",
	"th03/staff.cpp",
	"th01/vplanset.cpp",
	"th02/snd_mode.c",
	"th02/snd_pmdr.c",
	"th02/snd_dlyv.c",
	"th02/snd_load.cpp",
	"th03/vector.cpp",
	"th03/exit.cpp",
	"th03/cdg_put.asm",
	"th02/frmdely1.cpp",
	"th03/input_s.cpp",
	"th03/pi_put.cpp",
	"th03/pi_put_i.cpp",
	"th02/snd_se_r.cpp",
	"th03/snd_se.cpp",
	"th03/snd_kaja.cpp",
	"th03/initmain.cpp",
	"th03/cdg_load.cpp",
	"th03/exitmain.cpp",
	"th03/grppsafx.cpp",
	"th03/snd_dlym.cpp",
	"th03/inp_wait.cpp",
	"th03/pi_load.cpp",
	"th03/pi_put_q.cpp",
	"th03/inp_m_w.cpp",
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
	{ "-O", "libs/kaja/ongchk.com" },
	{ "-I", th04:branch(MODEL_ASM):link("zuninit", { "th04_zuninit.asm" }) },
	{ "-S", th04:branch(MODEL_TINY):link("res_huma", {
		"th04/res_huma.cpp",
		"bin/masters.lib",
	}) },
	{ "-M", th04:branch(MODEL_TINY):link("memchk", { "th04_memchk.asm" }) },
})
th04:comcstm("zun.com", "th04/zun.txt", th04_zuncom, 621381155)
th04:branch(MODEL_LARGE, { cflags = "-DBINARY='O'" }):link("op", {
	"th04/op_main.cpp",
	{ "th04_op_master.asm", o = "opm.obj" },
	"th01/vplanset.cpp",
	"th02/frmdely1.cpp",
	"th03/pi_put.cpp",
	"th03/pi_load.cpp",
	"th03/hfliplut.asm",
	"th04/input_w.cpp",
	"th04/vector.cpp",
	"th04/snd_pmdr.c",
	"th04/snd_mmdr.c",
	"th04/snd_kaja.cpp",
	"th04/cdg_p_nc.asm",
	"th04/snd_mode.cpp",
	"th04/snd_dlym.cpp",
	"th02/exit_dos.cpp",
	"th04/snd_load.cpp",
	"th04/grppsafx.asm",
	"th04_op2.asm",
	"th04/cdg_put.asm",
	"th04/exit.cpp",
	"th04/initop.cpp",
	"th04/cdg_p_na.cpp",
	"th04/input_s.asm",
	"th02/snd_se_r.cpp",
	"th04/snd_se.cpp",
	"th04/egcrect.cpp",
	"th04/bgimage.cpp",
	"th04/bgimager.asm",
	"th04/cdg_load.asm",
	"th02/frmdely2.cpp",
	"th04/op_setup.cpp",
	"th04/zunsoft.cpp",
	"th04/op_music.cpp",
	"th04/score_db.cpp",
	"th04/score_e.cpp",
	"th04/hi_view.cpp",
	"th04/op_title.cpp",
	"th04_op.asm",
	"th04/m_char.cpp",
})
th04:branch(MODEL_LARGE, { cflags = "-DBINARY='M'" }):link("main", {
	{ "th04_main.asm", extra_inputs = {
		th02_sprites["pellet"],
		th02_sprites["sparks"],
		th04_sprites["pelletbt"],
		th04_sprites["pointnum"],
	} },
	"th04/slowdown.cpp",
	"th04/demo.cpp",
	"th04/ems.cpp",
	"th04/tile_set.cpp",
	"th04/std.cpp",
	"th04/circle.cpp",
	"th04/tile.cpp",
	"th04/playfld.cpp",
	"th04/midboss4.cpp",
	"th04/f_dialog.cpp",
	"th04/dialog.cpp",
	"th04/boss_exp.cpp",
	"th04/stages.cpp",
	"th04/player_m.cpp",
	"th04/player_p.cpp",
	"th04/scoreupd.asm",
	"th04/hud_ovrl.cpp",
	"th04/cfg_lres.cpp",
	"th04/checkerb.cpp",
	"th04/mb_inv.cpp",
	"th04/boss_bd.cpp",
	"th04/score_rm.cpp",
	"th01/vplanset.cpp",
	"th03/vector.cpp",
	"th02/frmdely1.cpp",
	"th03/hfliplut.asm",
	"th04/mpn_free.cpp",
	"th04/input_w.cpp",
	"th04/mpn_l_i.cpp",
	"th04/vector.cpp",
	"th04/snd_pmdr.c",
	"th04/snd_mmdr.c",
	"th04/snd_kaja.cpp",
	"th04/snd_mode.cpp",
	"th04/snd_load.cpp",
	"th04/cdg_put.asm",
	"th04/exit.cpp",
	"th04/initmain.cpp",
	"th04/cdg_p_na.cpp",
	"th04/cdg_p_pr.asm",
	"th04/input_s.asm",
	"th02/snd_se_r.cpp",
	"th04/snd_se.cpp",
	"th04/cdg_load.asm",
	"th04/gather.cpp",
	"th04/scrolly3.cpp",
	"th04/motion_3.asm",
	"th04/midboss.cpp",
	"th04/hud_hp.cpp",
	"th04/mb_dft.cpp",
	"th04/vector2n.asm",
	"th04/spark_a.asm",
	"th04/grcg_3.cpp",
	"th04/it_spl_u.cpp",
	"th04/boss_4m.cpp",
	"th04/bullet_u.cpp",
	"th04/bullet_a.cpp",
	"th04/boss.cpp",
	"th04/boss_4r.cpp",
	"th04/boss_x2.cpp",
})
th04:branch(MODEL_LARGE, { cflags = "-DBINARY='E'" }):link("maine", {
	"th04/maine_e.cpp",
	{ "th04_maine_master.asm", o = "mainem.obj" },
	"th04/score_d.cpp",
	"th04/score_e.cpp",
	"th04/hi_end.cpp",
	"th01/vplanset.cpp",
	"th02/frmdely1.cpp",
	"th03/pi_put.cpp",
	"th03/pi_load.cpp",
	"th03/pi_put_q.cpp",
	"th03/hfliplut.asm",
	"th04/input_w.cpp",
	"th04/vector.cpp",
	"th04/snd_pmdr.c",
	"th04/snd_mmdr.c",
	"th04/snd_kaja.cpp",
	"th04/snd_mode.cpp",
	"th04/snd_dlym.cpp",
	"th04/cdg_p_pl.asm",
	"th04/snd_load.cpp",
	"th04/grppsafx.asm",
	"th04_maine.asm",
	"th04/cdg_put.asm",
	"th04/exit.cpp",
	"th04/initmain.cpp",
	"th04/input_s.asm",
	"th02/snd_se_r.cpp",
	"th04/snd_se.cpp",
	"th04/bgimage.cpp",
	"th04/bgimager.asm",
	"th04/cdg_load.asm",
	"th04/cutscene.cpp",
	"th04/staff.cpp",
})
-- ----

-- TH05
-- ----

local th05_sprites = Sprites({
	{ "th05/sprites/gaiji.bmp", "asm", "sGAIJI", 16, 16 },
	{ "th05/sprites/piano_l.bmp", "asm", "sPIANO_LABEL_FONT", 8, 8 },
})

local th05_zuncom = th05:zungen("obj/th05/zuncom.bin", {
	{ "-O", "libs/kaja/ongchk.com" },
	{ "-I", th05:branch(MODEL_ASM):link("zuninit", { "th05_zuninit.asm" }) },
	{ "-S", th05:branch(MODEL_TINY):link("res_kso", {
		"th05/res_kso.cpp",
		"bin/masters.lib",
	}) },
	{ "-G", th05:branch(MODEL_ASM):link("gjinit", {
		{ "th05_gjinit.asm", extra_inputs = th05_sprites["gaiji"] },
	}) },
	{ "-M", th05:branch(MODEL_ASM):link("memchk", { "th05_memchk.asm" }) },
})
th05:comcstm("zun.com", "th05/zun.txt", th05_zuncom, 628731748)
th05:branch(MODEL_LARGE, { cflags = "-DBINARY='O'" }):link("op", {
	"th05/op_main.cpp",
	{ "th05_op_master.asm", o = "opm.obj" },
	"th03/hfliplut.asm",
	"th04/snd_pmdr.c",
	"th04/snd_mmdr.c",
	"th04/snd_mode.cpp",
	"th02/exit_dos.cpp",
	"th04/grppsafx.asm",
	{ "th05_op2.asm", extra_inputs = th05_sprites["piano_l"] },
	"th04/cdg_p_na.cpp",
	"th02/snd_se_r.cpp",
	"th04/snd_se.cpp",
	"th04/bgimage.cpp",
	"th05/cdg_put.asm",
	"th04/exit.cpp",
	"th05/vector.cpp",
	"th05/musicp_c.cpp",
	"th05/musicp_a.asm",
	"th05/bgimager.asm",
	"th05/snd_load.cpp",
	"th05/snd_kaja.cpp",
	"th05/pi_cpp_1.cpp",
	"th05/pi_asm_1.asm",
	"th05/pi_cpp_2.cpp",
	"th05/pi_asm_2.asm",
	"th05/initop.cpp",
	"th05/input_s.asm",
	"th05/inp_h_w.cpp",
	"th05/snd_dlym.cpp",
	"th05/cdg_p_nc.cpp",
	"th05/frmdelay.cpp",
	"th04/cdg_load.asm",
	"th05/egcrect.cpp",
	"th05/op_setup.cpp",
	"th04/zunsoft.cpp",
	"th05/cfg.cpp",
	"th05/op_title.cpp",
	"th05/op_music.cpp",
	"th05/score_db.cpp",
	"th05/score_e.cpp",
	"th05/hi_view.cpp",
	"th05_op.asm",
	"th05/m_char.cpp",
})
th05:branch(MODEL_LARGE, { cflags = "-DBINARY='M'" }):link("main", {
	{ "th05_main.asm", extra_inputs = {
		th02_sprites["pellet"],
		th02_sprites["sparks"],
		th04_sprites["pelletbt"],
		th04_sprites["pointnum"],
	} },
	"th04/slowdown.cpp",
	"th05/demo.cpp",
	"th05/ems.cpp",
	"th05/cfg_lres.cpp",
	"th05/std.cpp",
	"th04/tile.cpp",
	"th05/main010.cpp",
	"th05/circle.cpp",
	"th05/f_dialog.cpp",
	"th05/dialog.cpp",
	"th05/boss_exp.cpp",
	"th05/playfld.cpp",
	"th04/mb_inv.cpp",
	"th04/boss_bd.cpp",
	"th05/boss_bg.cpp",
	"th05/laser_rh.cpp",
	"th05/p_common.cpp",
	"th05/p_reimu.cpp",
	"th05/p_marisa.cpp",
	"th05/p_mima.cpp",
	"th05/p_yuuka.cpp",
	"th05/player.asm",
	"th05/hud_bar.asm",
	"th05/scoreupd.asm",
	"th05/midboss5.cpp",
	"th05/hud_ovrl.cpp",
	"th04/player_p.cpp",
	"th04/vector2n.asm",
	"th05/spark_a.asm",
	"th05/bullet_p.cpp",
	"th04/grcg_3.cpp",
	"th05/player_a.cpp",
	"th05/bullet_1.asm",
	"th05/bullet_c.cpp",
	"th05/bullet.asm",
	"th05/bullet_t.cpp",
	"th03/vector.cpp",
	"th03/hfliplut.asm",
	"th04/snd_pmdr.c",
	"th04/snd_mmdr.c",
	"th04/snd_mode.cpp",
	"th04/cdg_p_na.cpp",
	"th02/snd_se_r.cpp",
	"th04/snd_se.cpp",
	"th05/cdg_put.asm",
	"th04/exit.cpp",
	"th05/vector.cpp",
	"th05/snd_load.cpp",
	"th05/snd_kaja.cpp",
	"th05/initmain.cpp",
	"th05/input_s.asm",
	"th05/inp_h_w.cpp",
	"th05/frmdelay.cpp",
	"th04/cdg_load.asm",
	"th04/scrolly3.cpp",
	"th04/motion_3.asm",
	"th05/gather.cpp",
	"th05/main032.cpp",
	"th05/midboss.cpp",
	"th04/hud_hp.cpp",
	"th05/mb_dft.cpp",
	"th05/laser.cpp",
	"th05/cheeto_u.cpp",
	"th04/it_spl_u.cpp",
	"th05/bullet_u.cpp",
	"th05/midboss1.cpp",
	"th05/boss_1.cpp",
	"th05/boss_4.cpp",
	"th05/boss_6.cpp",
	"th05/boss_x.cpp",
	"th05/hud_num.asm",
	"th05/boss.cpp",
	"th05/main014.cpp",
})
th05:branch(MODEL_LARGE, { cflags = "-DBINARY='E'" }):link("maine", {
	"th05/maine_e.cpp",
	{ "th05_maine_master.asm", o = "mainem.obj" },
	"th05/score_d.cpp",
	"th05/score_e.cpp",
	"th05/hi_end.cpp",
	"th03/hfliplut.asm",
	"th04/snd_pmdr.c",
	"th04/snd_mmdr.c",
	"th04/snd_mode.cpp",
	"th04/grppsafx.asm",
	"th05_maine.asm",
	"th04/cdg_p_na.cpp",
	"th02/snd_se_r.cpp",
	"th04/snd_se.cpp",
	"th04/bgimage.cpp",
	"th04/exit.cpp",
	"th05/vector.cpp",
	"th05/bgimager.asm",
	"th05/snd_load.cpp",
	"th05/snd_kaja.cpp",
	"th05/pi_cpp_1.cpp",
	"th05/pi_asm_1.asm",
	"th05/pi_cpp_2.cpp",
	"th05/pi_asm_2.asm",
	"th05/initmain.cpp",
	"th05/input_s.asm",
	"th05/inp_h_w.cpp",
	"th05/snd_dlym.cpp",
	"th05/frmdelay.cpp",
	"th04/cdg_load.asm",
	"th05/egcrect.cpp",
	"th05/cutscene.cpp",
	"th05/regist.cpp",
	"th05/staff.cpp",
})
-- ----

-- Research
-- --------

local research_cfg = optimized_cfg:branch(Subdir("Research/"), MODEL_SMALL)

research_cfg:link("holdkey", {
	"Research/holdkey.c",
	"bin/masters.lib",
})

research_cfg:branch({ cflags = "-DCPU=386" }):link("pi_bench", {
	"Research/pi_bench.cpp",
	research_cfg:build_uncached("platform/x86real/noexcept.cpp"),
	research_cfg:build_uncached("platform/x86real/pc98/blitter.cpp"),
	research_cfg:build_uncached("platform/x86real/pc98/grp_clip.cpp"),
	"platform/x86real/pc98/graph.cpp",
	"bin/masters.lib",
	piloadm,
})

local research_sprites = Sprites({
	{ "Research/blitperf/blitperf.bmp", "cpp", "sBLITPERF", 16, 16 },
	{ "Research/blitperf/wide.bmp", "c", "sWIDE", 640, 40 },
})

-- Must be an ordered table to retain the order for `build_dumb.bat`.
for _, t in pairs({ { 86, " -1-" }, { 286, " -2" }, { 386, "" } }) do
	local cpu_str = string.format("%03d", t[1])
	local cfg = research_cfg:branch({
		obj_root = (cpu_str .. "/"),
		cflags = string.format("-DCPU=%d%s", t[1], t[2]),
	})
	-- Bypass `PreviousOutputForSource` by explicitly building each unit.
	local obj = {
		cfg:build_uncached({ "Research/blitperf/blitperf.cpp", extra_inputs = {
			research_sprites["blitperf"],
		} }),
		cfg:build_uncached("platform/x86real/noexcept.cpp"),
		cfg:build_uncached("platform/x86real/pc98/blitter.cpp"),
		cfg:build_uncached("platform/x86real/pc98/font.cpp"),
		cfg:build_uncached("platform/x86real/pc98/graph.cpp"),
		cfg:build_uncached("platform/x86real/pc98/grcg.cpp"),
		cfg:build_uncached("platform/x86real/pc98/grp_clip.cpp"),
		cfg:build_uncached("platform/x86real/pc98/palette.cpp"),
		cfg:build_uncached("platform/x86real/pc98/vsync.cpp"),
	}

	local if_shift = {
		cfg:build_uncached({ "Research/blitperf/if_shift.cpp", extra_inputs = {
			th01_sprites["pellet"],
		} }),
	}
	cfg:link(("ifshf" .. cpu_str), tup_append_assignment(if_shift, obj))

	local wide = {
		cfg:build_uncached({ "Research/blitperf/wide.cpp", extra_inputs = {
			research_sprites["wide"],
		} }),
		cfg:build_uncached({ "Research/blitperf/wide_b.cpp" }),
	}
	cfg:link(("wide" .. cpu_str), tup_append_assignment(wide, obj))

	local masked = {
		piloadm,
		cfg:build_uncached({ "Research/blitperf/xfade.cpp"}),
		cfg:build_uncached({ "Research/blitperf/xfade_b.cpp"}),
		cfg:build_uncached({ "platform/x86real/pc98/egc.cpp"}),
		cfg:build_uncached({ "platform/x86real/pc98/grp_surf.cpp"}),
		"bin/masters.lib",
	}
	cfg:link(("xfade" .. cpu_str), tup_append_assignment(masked, obj))
end
-- --------

Rules:print()
