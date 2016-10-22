import geometry
import structs_pb2
import socket
import sys

IPAdress = "127.0.0.1"
port = 8383
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
numberOfStructuresToSend = 500
points2DToSend = []
points3DToSend = []
verticesToSend = []
edgesToSend = []
triangleFacesToSend = []
blocksToSend = []


def getInstance(portNumber):
    global port
    port = portNumber



def addPoint2D(point2D):
    pointToSend = structs_pb2.Point2D()
    pointToSend.x = point2D.x
    pointToSend.y = point2D.y
    pointToSend.prop.quality = pointt2D.quality
    pointToSend.prop.label = point2D.label
    pointToSend.prop.groupId = point2D.groupId
    points2DToSend.append(pointToSend)


def addPoint3D(point3D):
    pointToSend = structs_pb2.Point3D()
    pointToSend.x = point3D.x
    pointToSend.y = point3D.y
    pointToSend.z = point3D.z
    pointToSend.prop.quality = pointt3D.quality
    pointToSend.prop.label = point3D.label
    pointToSend.prop.groupId = point3D.groupId
    points3DToSend.append(pointToSend)


def addVertex(vertex):
    vertexToSend = structs_pb2.Vertex()
    vertexToSend.point = vertex.pointToSend
    vertexToSend.number = vertex.number
    vertexToSend.prop.quality = vertex.quality
    vertexToSend.prop.label = vertex.label
    vertexToSend.prop.groupId = vertex.groupId
    verticesToSend.append(vertexToSend)

def addEdge(edge):
    edgeToSend = structs_pb2.Edge()
    edgeToSend.v1 = edge.v1
    edgeToSend.v2 = edge.v2
    edgeToSend.prop.quality = edge.quality
    edgeToSend.prop.label = edge.label
    edgeToSend.prop.groupId = edge.groupId
    edgesToSend.append(edgeToSend)

def addTriangleFace(triangleFace):
    triangleFaceToSend = structs_pb2.TriangleFace()
    triangleFaceToSend.v1 = triangleFace.v1
    triangleFaceToSend.v2 = triangleFace.v2
    triangleFaceToSend.v3 = triangleFace.v3
    triangleFaceToSend.prop.quality = triangleFace.quality
    triangleFaceToSend.prop.label = triangleFace.label
    triangleFaceToSend.prop.groupId = triangleFace.groupId
    triangleFacesToSend.append(triangleFaceToSend)

def addBlock(block):
    blockToSend = structs_pb2.Block()
    blockToSend.v1 = block.v1
    blockToSend.v2 = block.v2
    blockToSend.v3 = block.v3
    blockToSend.v4 = block.v4
    blockToSend.prop.quality = block.quality
    blockToSend.prop.label = block.label
    blockToSend.prop.groupId = block.groupId
    blocksToSend.append(blockToSend)



def flushBuffer():
    print '{} points2D waiting to be sent when called flushBuffer()'.format(len(points2DToSend))
    print '{} points3D waiting to be sent when called flushBuffer()'.format(len(points3DToSend))
    print '{} vertices waiting to be sent when called flushBuffer()'.format(len(verticesToSend))
    print '{} edges waiting to be sent when called flushBuffer()'.format(len(edgesToSend))
    print '{} triangle faces waiting to be sent when called flushBuffer()'.format(len(triangleFacesToSend))
    print '{} blocks waiting to be sent when called flushBuffer()'.format(len(blocksToSend))

    

    try:

        # Send 
        message = structs_pb2.MessageInfo()
        message.type = structs_pb2.MessageInfo.DATA
        bytesToSend =  message.SerializeToString()
        sent = sock.sendto(bytesToSend, (IPAdress, port))	


        # Receive acknowledge
        print 'waiting to receive'
        data, addr = sock.recvfrom(10)
        reply = structs_pb2.MessageInfo()
        reply.ParseFromString(data)

        if reply.type == structs_pb2.MessageInfo.ACK:

            dataPackage = structs_pb2.DataPackage()
            point = dataPackage.points3D.add()
            # prop = structs_pb2.Properties()
            # prop.quality = 1.0
            # prop.label = "trallalala"
            # prop.groupId = 1
            point.x = 10
            point.y = 10
            point.z = 10
            point.prop.quality = 1.0
            point.prop.label = "trallalala"
            point.prop.groupId = 1


            pointToSend = dataPackage.SerializeToString()
            header = structs_pb2.Header()
            header.sizeOfData = sys.getsizeof(pointToSend)
            header.endOfData = True
            toSendHeader = header.SerializeToString()
            sent = sock.sendto(toSendHeader, (IPAdress, port))

            # Receive acknowledge
            print 'waiting to receive2'
            data, addr = sock.recvfrom(10)
            reply = structs_pb2.MessageInfo()
            reply.ParseFromString(data)
            if reply.type == structs_pb2.MessageInfo.ACK:
                sent = sock.sendto(pointToSend, (IPAdress, port))        

    finally:
        print 'closing socket'
        sock.close()



