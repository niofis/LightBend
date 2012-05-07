local math = require('math')
local string = require("string")
local table = require("table")
local lb=require("lightbend")
local tostring = tostring

local base = _G
local io = require("io")

local prm = require("primitives")

module("threed")
--lua: lb.initScene()
--lua: lb.setGroup(id_group,id_material)
--lua: lb.setMaterial(id_material,color_a,color_r,color_g,color_b,reflexion,refraccion,specular)
--lua: lb.setLight(id_light,color_a,color_r,color_g,color_b,intensidad,x,y,z)
--lua: lb.setCamera(id_camera,eye_x,eye_y,eye_z,lt_x,lt_y,lt_z,rt_x,rt_y,rt_z,lb_x,lb_y,lb_z)
--lua: lb.setSphere(id_object,id_group,radio,x,y,z)
--lua: lb.setTriangle(id_object,id_group,radio,x1,y1,z1,x2,y2,z2,x3,y3,z3)

function sendScene(lb,scene)

lb.initScene()

--lua: lb.setCamera(id_camera,eye_x,eye_y,eye_z,lt_x,lt_y,lt_z,rt_x,rt_y,rt_z,lb_x,lb_y,lb_z)
local c=scene.camera
lb.setCamera(1,c.eye.x,c.eye.y,c.eye.z,
				c.lt.x,c.lt.y,c.lt.z,
				c.rt.x,c.rt.y,c.rt.z,
				c.lb.x,c.lb.y,c.lb.z)

--lua: lb.setLight(id_light,color_a,color_r,color_g,color_b,intensidad,x,y,z)
for i,v in base.pairs(scene.lights) do

	lb.setLight(i,
				v.color.a,v.color.r,v.color.g,v.color.b,
				v.intensity,
				v.position.x,
				v.position.y,
				v.position.z)
end

--lua: lb.setMaterial(id_material,color_a,color_r,color_g,color_b,reflexion,refraccion,specular)
for i,v in base.pairs(scene.materials) do
	v.idx=i
	lb.setMaterial(i,
				v.color.a,v.color.r,v.color.g,v.color.b,
				v.reflection,
				v.refraction,
				v.specular)
end

--lua: lb.setGroup(id_group,id_material)
for i,v in base.pairs(scene.groups) do
	v.idx=i
	lb.setGroup(i,
				v.material.idx)
end

--lua: lb.setSphere(id_object,id_group,radio,x,y,z)
--lua: lb.setTriangle(id_object,id_group,radio,x1,y1,z1,x2,y2,z2,x3,y3,z3)
for i,v in base.pairs(scene.objects) do
	if v.issphere then
		lb.setSphere(i,
					v.group.idx, v.radius,
					v.center.x,v.center.y,v.center.z)
	elseif v.istriangle then

	end
end

for i,v in base.pairs(scene.models) do
    lb.loadModel(v)
end

lb.doneLoading()
end
