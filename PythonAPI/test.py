import Smeshalist
import geometry
import random 

Smeshalist.getInstance(8383)

counter = 0

while counter < 1000:
    counter = counter + 1
    point = geometry.Point2D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))
    point.groupId = 1
    Smeshalist.addPoint2D(point)


counter = 0

while counter < 1000:
    counter = counter + 1
    point = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))
    point.groupId = 1
    Smeshalist.addPoint3D(point)


counter = 0

while counter < 1000:
    counter = counter + 1
    point = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))
    vertex = geometry.Vertex(point, random.random())
    vertex.groupId = 1
    Smeshalist.addVertex(vertex)

counter = 0
while counter < 1000:
    counter = counter + 1
    point1 = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))
    point2 = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))

    edge = geometry.Edge(point1, point2)
    edge.groupId = 1
    Smeshalist.addEdge(edge)


counter = 0
while counter < 1000:
    counter = counter + 1
    point1 = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))
    point2 = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))
    point3 = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))

    triangleFace = geometry.TriangleFace(point1, point2, point3)
    triangleFace.groupId = 1
    Smeshalist.addTriangleFace(triangleFace)



counter = 0
while counter < 1000:
    counter = counter + 1
    point1 = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))
    point2 = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))
    point3 = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))
    point4 = geometry.Point3D(random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0), random.uniform(-10.0, 10.0))

    block = geometry.Block(point1, point2, point3, point4)
    block.groupId = 1
    Smeshalist.addBlock(block)


Smeshalist.flushBuffer()