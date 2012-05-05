local lb=require("lightbend")

for i,v in pairs(lb) do
    print(i,v)
end

--lb.loadModel("/home/niofis/Raytracing/models/testplatonicsolids.nff")
--lb.loadModel("D:/Enrique/Raytracing/models/testplatonicsolids.nff")
lb.loadModel("D:/Enrique/Raytracing/models/Arbor/Arbor/Arbor.3DS")
