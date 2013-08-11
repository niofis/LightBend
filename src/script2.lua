local lb=require("lightbend")
local prm= require("primitives")
local tb=require("table")
local tr=require("threed")

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

local scene=prm.Scene:new{}

scene.camera.eye.x=0
scene.camera.eye.y=0
scene.camera.eye.z=-100
scene.camera.lt.x=-6.4
scene.camera.lt.y=3.6
scene.camera.lt.z=-50.0
scene.camera.rt.x=6.4
scene.camera.rt.y=3.6
scene.camera.rt.z=-50.0
scene.camera.lb.x=-6.4
scene.camera.lb.y=-3.6
scene.camera.lb.z=-50.0

local rm=prm.Material:new{ color=prm.ColorF:new{a=1,r=1,g=0,b=0},reflextion=0,refraction=0,specular=1}
tb.insert(scene.materials,rm)
local gm=prm.Material:new{ color=prm.ColorF:new{a=1,r=0,g=1,b=0},reflextion=0,refraction=0,specular=1}
tb.insert(scene.materials,gm)
local bm=prm.Material:new{ color=prm.ColorF:new{a=1,r=0,g=0,b=1},reflextion=0,refraction=0,specular=1}
tb.insert(scene.materials,bm)

local rg=prm.Group:new{material=rm}
tb.insert(scene.groups,rg)
local gg=prm.Group:new{material=gm}
tb.insert(scene.groups,gg)
local bg=prm.Group:new{material=bm}
tb.insert(scene.groups,bg)

local l=prm.Light:new{intensity=1000,color=prm.ColorF:new{a=1,r=1,g=1,b=1},position=prm.Vector3:new{x=0,y=0,z=-50}}
tb.insert(scene.lights,l)

local slices=200
local resolution=200

local s= prm.Sphere:new{radius=1.0, center=prm.Vector3:new{x=-1.5}, group=rg, slices=slices, resolution=resolution}
tb.insert(scene.objects,s)
local s= prm.Sphere:new{radius=1.0, center=prm.Vector3:new{y=2}, group=gg, slices=slices, resolution=resolution}
tb.insert(scene.objects,s)
local s= prm.Sphere:new{radius=1.0, center=prm.Vector3:new{x=1.5}, group=bg, slices=slices, resolution=resolution}
tb.insert(scene.objects,s)

tr.sendScene(lb,scene)
