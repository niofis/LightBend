local math = require('math')
local string = require("string")
local table = require("table")
local tostring = tostring

local base = _G
local io = require("io")

local prm = require("primitives")

module("threed")
--lua: cRT.initScene(num_camaras,num_luces,num_materiales,num_grupos,num_objetos)
--lua: cRT.setGroup(id_group,id_material)
--lua: cRT.setMaterial(id_material,color_a,color_r,color_g,color_b,reflexion,refraccion,specular)
--lua: cRT.setLight(id_light,color_a,color_r,color_g,color_b,intensidad,x,y,z)
--lua: cRT.setCamera(id_camera,eye_x,eye_y,eye_z,lt_x,lt_y,lt_z,rt_x,rt_y,rt_z,lb_x,lb_y,lb_z)
--lua: cRT.setSphere(id_object,id_group,radio,x,y,z)
--lua: cRT.setTriangle(id_object,id_group,radio,x1,y1,z1,x2,y2,z2,x3,y3,z3)

function sendScene(cRT,scene)

cRT.initScene(1,#scene.lights,#scene.materials,#scene.groups,#scene.objects)

--lua: cRT.setCamera(id_camera,eye_x,eye_y,eye_z,lt_x,lt_y,lt_z,rt_x,rt_y,rt_z,lb_x,lb_y,lb_z)
local c=scene.camera
cRT.setCamera(1,c.eye.x,c.eye.y,c.eye.z,
				c.lt.x,c.lt.y,c.lt.z,
				c.rt.x,c.rt.y,c.rt.z,
				c.lb.x,c.lb.y,c.lb.z)

--lua: cRT.setLight(id_light,color_a,color_r,color_g,color_b,intensidad,x,y,z)
for i,v in base.pairs(scene.lights) do
	cRT.setLight(i,
				v.color.a,v.color.r,v.color.g,v.color.b,
				v.intensity,
				v.position.x,
				v.position.y,
				v.position.z)
end

--lua: cRT.setMaterial(id_material,color_a,color_r,color_g,color_b,reflexion,refraccion,specular)
for i,v in base.pairs(scene.materials) do
	v.idx=i
	cRT.setMaterial(i,
				v.color.a,v.color.r,v.color.g,v.color.b,
				v.reflection,
				v.refraction,
				v.specular)
end

--lua: cRT.setGroup(id_group,id_material)
for i,v in base.pairs(scene.groups) do
	v.idx=i
	cRT.setGroup(i,
				v.material.idx)
end

--lua: cRT.setSphere(id_object,id_group,radio,x,y,z)
--lua: cRT.setTriangle(id_object,id_group,radio,x1,y1,z1,x2,y2,z2,x3,y3,z3)
for i,v in base.pairs(scene.objects) do
	if v.issphere then
		cRT.setSphere(i,
					v.group.idx, v.radius,
					v.center.x,v.center.y,v.center.z)
	elseif v.istriangle then

	end
end

cRT.doneLoading()
end
