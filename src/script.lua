local lb=require("lightbend")

--[[
for i,v in pairs(lb) do
    print(i,v)
end
]]

--lb.initScene()

--lb.loadModel("/home/niofis/Raytracing/models/tree.ms3d")
--lb.loadModel("D:/Enrique/Raytracing/models/testplatonicsolids.nff")
--lb.loadModel("D:/Enrique/Raytracing/models/Arbor/Arbor/Arbor.3DS")

--lua: lb.setGroup(id_group,id_material)
--lua: lb.setMaterial(id_material,color_a,color_r,color_g,color_b,reflexion,refraccion,specular)
--lua: lb.setLight(id_light,color_a,color_r,color_g,color_b,intensidad,x,y,z)
--lua: lb.setCamera(id_camera,eye_x,eye_y,eye_z,lt_x,lt_y,lt_z,rt_x,rt_y,rt_z,lb_x,lb_y,lb_z)
--lua: lb.setSphere(id_object,id_group,radio,x,y,z)
--lua: lb.setTriangle(id_object,id_group,radio,x1,y1,z1,x2,y2,z2,x3,y3,z3)
--lua: lb.initScene(num_camaras,num_luces,num_materiales,num_grupos,num_objetos)

local prm= require("primitives")
local tb=require("table")
local tr=require("threed")



local scene=prm.Scene:new{}

--[[
scene.camera=prm.Camera:new{eye=prm.Vector3:new{0,0,-10},
lt=prm.Vector3:new{-3.2,2.4,-5.0},
rt=prm.Vector3:new{3.2,2.4,-5.0},
lb=prm.Vector3:new{-3.2,-2.4,-5.0}}
]]
scene.camera.eye.x=0
scene.camera.eye.y=0
scene.camera.eye.z=-100
scene.camera.lt.x=-3.2
scene.camera.lt.y=2.4
scene.camera.lt.z=-50.0
scene.camera.rt.x=3.2
scene.camera.rt.y=2.4
scene.camera.rt.z=-50.0
scene.camera.lb.x=-3.2
scene.camera.lb.y=-2.4
scene.camera.lb.z=-50.0

local m=prm.Material:new{ color=prm.ColorF:new{a=1,r=0.811764,g=0.709803,b=0.231372},reflextion=0,refraction=0,specular=1}
tb.insert(scene.materials,m)

local g=prm.Group:new{material=m}
tb.insert(scene.groups,g)


function addLevel(parent,level)

	if level>3 or parent==nil then return end

	local n_radius=parent.radius/2.5

	local pc=parent.center;
	local nr=parent.radius+n_radius;

	local c1=pc+prm.Vector3:new{x=-nr}
	local s1=prm.Sphere:new{radius=n_radius, center=c1, group=g}
	s1.left=1

	local c2=pc+prm.Vector3:new{x=nr}
	local s2=prm.Sphere:new{radius=n_radius, center=c2, group=g}
	s2.right=1

	local c3=pc+prm.Vector3:new{y=-nr}
	local s3=prm.Sphere:new{radius=n_radius, center=c3, group=g}
	s3.top=1

	local c4=pc+prm.Vector3:new{y=nr}
	local s4=prm.Sphere:new{radius=n_radius, center=c4, group=g}
	s4.bottom=1

	local c5=pc+prm.Vector3:new{z=nr}
	local s5=prm.Sphere:new{radius=n_radius, center=c5, group=g}
	s5.front=1

	local c6=pc+prm.Vector3:new{z=-nr}
	local s6=prm.Sphere:new{radius=n_radius, center=c6, group=g}
	s6.back=1

	if parent.right==1 then s1=nil end
	if parent.left==1 then s2=nil end
	if parent.top==1 then s4=nil end
	if parent.bottom==1 then s3=nil end
	if parent.front==1 then s6=nil end
	if parent.back==1 then s5=nil end

	if s1 then
		tb.insert(scene.objects,s1)
		addLevel(s1,level+1)
	end

	if s2 then
		tb.insert(scene.objects,s2)
		addLevel(s2,level+1)
	end

	if s3 then
		tb.insert(scene.objects,s3)
		addLevel(s3,level+1)
	end

	if s4 then
		tb.insert(scene.objects,s4)
		addLevel(s4,level+1)
	end

	if s5 then
		tb.insert(scene.objects,s5)
		addLevel(s5,level+1)
	end

	if s6 then
		tb.insert(scene.objects,s6)
		addLevel(s6,level+1)
	end

end

--[[
local o=prm.Sphere:new{radius=2, center=prm.Vector3:new{x=0,y=0,z=0}, group=g}
o.bottom=1
tb.insert(scene.objects,o)
addLevel(o,1)
]]

local l=prm.Light:new{intensity=100,color=prm.ColorF:new{a=1,r=1,g=1,b=1},position=prm.Vector3:new{x=0,y=2,z=-50}}
tb.insert(scene.lights,l)

l=prm.Light:new{intensity=100,color=prm.ColorF:new{a=1,r=1,g=1,b=1},position=prm.Vector3:new{x=0,y=2,z=50}}
tb.insert(scene.lights,l)

tb.insert(scene.models,"/home/niofis/Raytracing/models/tree.ms3d")


tr.sendScene(lb,scene)

