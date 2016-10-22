import geometry
import structs_pb2
import socket
import sys

IPAdress = "127.0.0.1"
port = 8383
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
numberOfStructuresToSend = 20
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
    points2DToSend.append(point2D)


def addPoint3D(point3D):
    points3DToSend.append(point3D)


def addVertex(vertex):    
    verticesToSend.append(vertex)


def addEdge(edge):
    edgesToSend.append(edge)


def addTriangleFace(triangleFace):
    triangleFacesToSend.append(triangleFace)


def addBlock(block):
    blocksToSend.append(block)


def mapPoint2d(point2D, pointToSend):
    pointToSend.x = point2D.x
    pointToSend.y = point2D.y
    pointToSend.prop.quality = point2D.quality
    pointToSend.prop.label = point2D.label
    pointToSend.prop.groupId = point2D.groupId


def mapPoint3d(point3D, pointToSend):
    pointToSend.x = point3D.x
    pointToSend.y = point3D.y
    pointToSend.z = point3D.z
    pointToSend.prop.quality = point3D.quality
    pointToSend.prop.label = point3D.label
    pointToSend.prop.groupId = point3D.groupId


def mapVertex(vertex, vertexToSend):
    vertexToSend.point.x = vertex.point.x
    vertexToSend.point.y = vertex.point.y
    vertexToSend.point.z = vertex.point.z
    vertexToSend.number = vertex.number
    vertexToSend.prop.quality = vertex.quality
    vertexToSend.prop.label = vertex.label
    vertexToSend.prop.groupId = vertex.groupId


def mapEdge(edge, edgeToSend):
    edgeToSend.v1.x = edge.v1.x
    edgeToSend.v1.y = edge.v1.y
    edgeToSend.v1.z = edge.v1.z
    edgeToSend.v2.x = edge.v2.x
    edgeToSend.v2.y = edge.v2.y
    edgeToSend.v2.z = edge.v2.z
    edgeToSend.prop.quality = edge.quality
    edgeToSend.prop.label = edge.label
    edgeToSend.prop.groupId = edge.groupId


def mapFace(triangleFace, triangleFaceToSend):
    triangleFaceToSend.v1.x = triangleFace.v1.x
    triangleFaceToSend.v1.y = triangleFace.v1.y
    triangleFaceToSend.v1.z = triangleFace.v1.z
    triangleFaceToSend.v2.x = triangleFace.v2.x
    triangleFaceToSend.v2.y = triangleFace.v2.y
    triangleFaceToSend.v2.z = triangleFace.v2.z
    triangleFaceToSend.v3.x = triangleFace.v3.x
    triangleFaceToSend.v3.y = triangleFace.v3.y
    triangleFaceToSend.v3.z = triangleFace.v3.z
    triangleFaceToSend.prop.quality = triangleFace.quality
    triangleFaceToSend.prop.label = triangleFace.label
    triangleFaceToSend.prop.groupId = triangleFace.groupId


def mapBlock(block, blockToSend):
    blockToSend.v1.x = block.v1.x
    blockToSend.v1.y = block.v1.y
    blockToSend.v1.z = block.v1.z
    blockToSend.v2.x = block.v2.x
    blockToSend.v2.y = block.v2.y
    blockToSend.v2.z = block.v2.z
    blockToSend.v3.x = block.v3.x
    blockToSend.v3.y = block.v3.y
    blockToSend.v3.z = block.v3.z
    blockToSend.v4.x = block.v4.x
    blockToSend.v4.y = block.v4.y
    blockToSend.v4.z = block.v4.z
    blockToSend.prop.quality = block.quality
    blockToSend.prop.label = block.label
    blockToSend.prop.groupId = block.groupId


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

        isSomethingToSend = True

        while reply.type == structs_pb2.MessageInfo.ACK and isSomethingToSend == True:

            dataPackage = structs_pb2.DataPackage()
            counter = numberOfStructuresToSend

            while counter > 0 and len(points2DToSend) > 0:
                point = dataPackage.points2D.add()
                point2D = points2DToSend.pop(0)
                mapPoint2d(point2D, point)
                counter = counter - 1


            while counter > 0 and len(points3DToSend) > 0:
                point = dataPackage.points3D.add()
                point3D = points3DToSend.pop(0)
                mapPoint3d(point3D, point)
                counter = counter - 1


            while counter > 0 and len(verticesToSend) > 0:
                vertexToSend = dataPackage.vertexes.add()
                vertex = verticesToSend.pop(0)
                mapVertex(vertex, vertexToSend)
                counter = counter - 1


            while counter > 0 and len(edgesToSend) > 0:
                edgeToSend = dataPackage.edges.add()
                edge = edgesToSend.pop(0)
                mapEdge(edge, edgeToSend)
                counter = counter - 1


            while counter > 0 and len(triangleFacesToSend) > 0:
                triangleFaceToSend = dataPackage.faces.add()
                triangleFace = triangleFacesToSend.pop(0)
                mapFace(triangleFace, triangleFaceToSend)
                counter = counter - 1

            while counter > 0 and len(blocksToSend) > 0:
                blockToSend = dataPackage.blocks.add()
                block = blocksToSend.pop(0)
                mapBlock(block, blockToSend)
                counter = counter - 1 


            if len(points2DToSend) == 0 and len(points3DToSend) == 0 and len(verticesToSend) == 0 and len(edgesToSend) == 0 and  len(triangleFacesToSend) == 0 and len(blocksToSend) == 0:
                isSomethingToSend = False

           
            dataToSend = dataPackage.SerializeToString()
            header = structs_pb2.Header()
            header.sizeOfData = sys.getsizeof(dataToSend)

            if isSomethingToSend == False:
                header.endOfData = True
            else: 
                header.endOfData = False

            toSendHeader = header.SerializeToString()
            sent = sock.sendto(toSendHeader, (IPAdress, port))
            sent = sock.sendto(dataToSend, (IPAdress, port))
            
            # Receive acknowledge
            print 'waiting to receive2'
            data, addr = sock.recvfrom(10)
            reply.ParseFromString(data)                        

    finally:
        print 'closing socket'
        sock.close()



