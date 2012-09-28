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
scene.camera.eye.z=-7
scene.camera.lt.x=-0.64
scene.camera.lt.y=0.52
scene.camera.lt.z=-5.0
scene.camera.rt.x=0.64
scene.camera.rt.y=0.52
scene.camera.rt.z=-5.0
scene.camera.lb.x=-0.64
scene.camera.lb.y=-0.21
scene.camera.lb.z=-5.0

local l=prm.Light:new{intensity=1000,color=prm.ColorF:new{a=1,r=1,g=1,b=1},position=prm.Vector3:new{x=0,y=0,z=-50}}
tb.insert(scene.lights,l)

tb.insert(scene.models, "/Users/niofis/Personal/Raytracing/Models/TeknolWorldM.3ds")

tr.sendScene(lb,scene)
