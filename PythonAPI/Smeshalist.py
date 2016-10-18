import geometry
import structs_pb2
import socket

IPAdress = "127.0.0.1"
port = 8383
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
numberOfStructuresToSend = 500
structuresToSend = []


def getInstance(portNumber):
    global sock
    global port
    port = portNumber



def addPoint2D(point2D):
    prop = structs_pb2.Properties()
    prop.quality = point2D.quality
    prop.label = point2D.label
    prop.groupId = point2D.groupId
    pointToSend = structs_pb2.Point2D()
    pointToSend.x = point2D.x
    pointToSend.y = point2D.y
    pointToSend.prop = prop
    structuresToSend.append(pointToSend)


def addPoint3D(point3D):
    prop = structs_pb2.Properties()
    prop.quality = point3D.quality
    prop.label = point3D.label
    prop.groupId = point3D.groupId
    pointToSend = structs_pb2.Point3D()
    pointToSend.x = point3D.x
    pointToSend.y = point3D.y
    pointToSend.z = point3D.z
    pointToSend.prop = prop
    structuresToSend.append(pointToSend)


def addVertex(vertex):
    prop = structs_pb2.Properties()
    prop.quality = vertex.quality
    prop.label = vertex.label
    prop.groupId = vertex.groupId
    vertexToSend = structs_pb2.Vertex()
    vertexToSend.point = vertex.pointToSend
    vertexToSend.number = vertex.number
    vertexToSend.prop = prop
    structuresToSend.append(vertexToSend)

def addEdge(edge):
    prop = structs_pb2.Properties()
    prop.quality = edge.quality
    prop.label = edge.label
    prop.groupId = edge.groupId
    edgeToSend = structs_pb2.Edge()
    edgeToSend.v1 = edge.v1
    edgeToSend.v2 = edge.v2
    edgeToSend.prop = prop
    structuresToSend.append(edgeToSend)

def addTriangleFace(triangleFace):
    prop = structs_pb2.Properties()
    prop.quality = triangleFace.quality
    prop.label = triangleFace.label
    prop.groupId = triangleFace.groupId
    triangleFaceToSend = structs_pb2.TriangleFace()
    triangleFaceToSend.v1 = triangleFace.v1
    triangleFaceToSend.v2 = triangleFace.v2
    triangleFaceToSend.v2 = triangleFace.v3
    triangleFaceToSend.prop = prop
    structuresToSend.append(triangleFaceToSend)



def addTriangleFace(triangleFace):
    prop = structs_pb2.Properties()
    prop.quality = triangleFace.quality
    prop.label = triangleFace.label
    prop.groupId = triangleFace.groupId
    triangleFaceToSend = structs_pb2.TriangleFace()
    triangleFaceToSend.v1 = triangleFace.v1
    triangleFaceToSend.v2 = triangleFace.v2
    triangleFaceToSend.v3 = triangleFace.v3
    triangleFaceToSend.prop = prop
    structuresToSend.append(triangleFaceToSend)

def addBlock(block):
    prop = structs_pb2.Properties()
    prop.quality = block.quality
    prop.label = block.label
    prop.groupId = block.groupId
    blockToSend = structs_pb2.Block()
    blockToSend.v1 = block.v1
    blockToSend.v2 = block.v2
    blockToSend.v3 = block.v3
    blockToSend.v4 = block.v4
    blockToSend.prop = prop
    structuresToSend.append(blockToSend)

