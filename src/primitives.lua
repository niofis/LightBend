local math = require('math')
local string = require("string")
local table = require("table")
local tostring = tostring

local base = _G
module("primitives")

Vector3={}

function Vector3:new(o)
	o=o or {}
	base.setmetatable(o,self)
	self.__index=self

	o.x=o.x or 0
	o.y=o.y or 0
	o.z=o.z or 0

	return o
end

Vector3.__add = function(a,b)
	local res = Vector3:new{}
	res.x=a.x+b.x
	res.y=a.y+b.y
	res.z=a.z+b.z
	return res
end

Vector3.__sub = function(a,b)
	local res = Vector3:new{}
	res.x=a.x-b.x
	res.y=a.y-b.y
	res.z=a.z-b.z
	return res
end

Vector3.__mul = function(a,b) --Dot Prodct or scale depending on parameter b
	local res = 0
	if(base.type(b)=="table") then
		res=a.x*b.x + a.y*b.y + a.z*b.z
	elseif(base.type(b)=="number") then
		res=Vector3:new{x=a.x*b, y=a.y*b, z=a.z*b}
	end
	return res
end

Vector3.__div = function(a,b)
	local res=Vector3:new{x=a.x/b, y=a.y/b, z=a.z/b}
	return res
end

Vector3.__pow = function(a,b) --^ Cross Product
	local res = Vector3:new{}
	res.x=a.y*b.z-a.z*b.y
	res.y=a.z*b.x-a.x*b.z
	res.z=a.x*b.y-a.y*b.x
	return res
end

function Vector3:add(a)
	if(base.type(a)=="table") then
		self.x=self.x+a.x
		self.y=self.y+a.y
		self.z=self.z+a.z
	elseif(base.type(a)=="number") then
		self.x=self.x+a
		self.y=self.y+a
		self.z=self.z+a
	end
end

function Vector3:multiply(a)
	if(base.type(a)=="table") then
		self.x=self.x*a.x
		self.y=self.y*a.y
		self.z=self.z*a.z
	elseif(base.type(a)=="number") then
		self.x=self.x*a
		self.y=self.y*a
		self.z=self.z*a
	end
end

function Vector3:length()--Length/Norm
	local res=0
	local a= self
	res=math.sqrt(a.x*a.x+a.y*a.y+a.z*a.z)
	return res
end

function Vector3:normal()
	local res=Vector3:new{}
	local l=self:length()
	res.x=self.x/l
	res.y=self.y/l
	res.z=self.z/l
	return res
end

function Vector3:normalize()
	local l=self:length()
	self.x=self.x/l
	self.y=self.y/l
	self.z=self.z/l
	return l
end

function Vector3:reciprocal()
	local res=Vector3:new{}
	res.x=1/self.x
	res.y=1/self.y
	res.z=1/self.z
	return res
end

Camera={}

function Camera:new(o)
	o=o or {}
	base.setmetatable(o,self)
	self.__index=self

	o.eye=o.eye or Vector3:new{}
	o.lt=o.lt or Vector3:new{}
	o.rt=o.rt or Vector3:new{}
	o.lb=o.lb or Vector3:new{}

	return o
end

Scene={}
function Scene:new(o)
	o=o or {}
	base.setmetatable(o,self)
	self.__index=self

	o.objects=o.objects or {}
	o.lights=o.lights or {}
	o.camera=o.camera or Camera:new{}
	o.materials=o.materials or {}
	o.groups=o.groups or {}
	return o
end

ColorF={}

function ColorF:new(o)
	o=o or {}
	base.setmetatable(o,self)
	self.__index=self

	o.a=o.a or 0
	o.r=o.r or 0
	o.g=o.g or 0
	o.b=o.b or 0

	return o
end

ColorF.__add = function(a,b)
	local res = ColorF:new{}
	if(base.type(b)=="number") then
		res.a=a.a+b
		res.r=a.r+b
		res.g=a.g+b
		res.b=a.b+b
	elseif (base.type(b)=="table") then
		res.a=a.a+b.a
		res.r=a.r+b.r
		res.g=a.g+b.g
		res.b=a.b+b.b
	end
	return res
end

ColorF.__sub = function(a,b)
	local res = ColorF:new{}
	res.a=a.a-b.a
	res.r=a.r-b.r
	res.g=a.g-b.g
	res.b=a.b-b.b
	return res
end

ColorF.__mul = function(a,b)
	local res = ColorF:new{}
	if(base.type(b)=="table") then
		res.a=a.a*b.a
		res.r=a.r*b.r
		res.g=a.g*b.g
		res.b=a.b*b.b
	elseif(base.type(b)=="number")then
		res.a=a.a*b
		res.r=a.r*b
		res.g=a.g*b
		res.b=a.b*b
	end
	return res
end

ColorF.__div = function(a,b)
	local res = ColorF:new{}
	if(base.type(b)=="table") then
		res.a=a.a/b.a
		res.r=a.r/b.r
		res.g=a.g/b.g
		res.b=a.b/b.b
	elseif(base.type(b)=="number")then
		res.a=a.a/b
		res.r=a.r/b
		res.g=a.g/b
		res.b=a.b/b
	end
	return res
end

function ColorF:to255()
	local res = ColorF:new{}
	res.a=math.min(self.a*255,255)
	res.r=math.min(self.r*255,255)
	res.g=math.min(self.g*255,255)
	res.b=math.min(self.b*255,255)
	return res
end

function ColorF:normalize()
	local m = math.max(self.r,self.g,self.b)
	if(m>1) then
		self.r=self.r/m
		self.g=self.g/m
		self.b=self.b/m
	end
end

Material={}

function Material:new(o)
	o=o or {}
	base.setmetatable(o,self)
	self.__index=self

	o.color=o.color or ColorF:new{}
	o.refraction = o.refraction or 0
	o.reflection = o.reflection or 0
	o.specular = o.specular or 0

	return o
end

Group={}

function Group:new(o)
	o=o or {}
	base.setmetatable(o,self)
	self.__index=self

	o.material=o.material or Material:new{}

	return o
end

Light={}

function Light:new(o)
	o=o or {}
	base.setmetatable(o,self)
	self.__index=self

	o.position=o.position or Vector3:new{}
	o.color=o.color or ColorF:new{}
	o.intensity=o.intensity or 100

	return o
end

Sphere={}
function Sphere:new(o)
	o=o or {}
	base.setmetatable(o,self)
	self.__index=self

	o.issphere=1

	o.radius=o.radius or 0
	o.center=o.center or Vector3:new{}

	o.group=o.group

	return o
end

Triangle={}
function Triangle:new(o)
	o=o or {}
	base.setmetatable(o,self)
	self.__index=self

	o.istriangle=1

	o.p1=o.p1 or Vector3:new{}
	o.p2=o.p2 or Vector3:new{}
	o.p3=o.p3 or Vector3:new{}

	o.group=o.group

	--Initialize
	o:init()
	return o
end

function Triangle:init()
	self.v1=self.p1
	self.v2=self.p2-self.p1
	self.v3=self.p3-self.p1
	self.n=self.v2^self.v3
	self.n:normalize()
end

function Triangle:normal(pt)
	return self.n
end
