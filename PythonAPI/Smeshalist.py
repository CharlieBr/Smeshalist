import geometry
import structs_pb2
import socket
import sys

IPAdress = "127.0.0.1"
port = 8383
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
numberOfStructuresToSend = 200
structuresRemaining = numberOfStructuresToSend
dataPackages = []

def getInstance(portNumber):
    global port
    port = portNumber
    dataPackage = structs_pb2.DataPackage()
    dataPackages.append(dataPackage)


def addPoint3D(point3D):

    global structuresRemaining
    if structuresRemaining ==  0:
        structuresRemaining = numberOfStructuresToSend 
        dataPackage = structs_pb2.DataPackage()
        dataPackages.append(dataPackage)

    structuresRemaining = structuresRemaining -1
    dataPackage = dataPackages[-1]
    pointToSend = dataPackage.points3D.add()
    pointToSend.x = point3D.x
    pointToSend.y = point3D.y
    pointToSend.z = point3D.z


def addVertex(vertex):
    global structuresRemaining
    if structuresRemaining ==  0:
        structuresRemaining = numberOfStructuresToSend 
        dataPackage = structs_pb2.DataPackage()
        dataPackages.append(dataPackage)

    structuresRemaining = structuresRemaining -1
    dataPackage = dataPackages[-1]
    vertexToSend = dataPackage.vertexes.add()
    vertexToSend.point.x = vertex.point.x
    vertexToSend.point.y = vertex.point.y
    vertexToSend.point.z = vertex.point.z
    vertexToSend.prop.quality = vertex.quality
    vertexToSend.prop.label = vertex.label
    vertexToSend.prop.groupId = vertex.groupId



def addEdge(edge):
    global structuresRemaining
    if structuresRemaining ==  0:
        structuresRemaining = numberOfStructuresToSend 
        dataPackage = structs_pb2.DataPackage()
        dataPackages.append(dataPackage)

    structuresRemaining = structuresRemaining -1
    dataPackage = dataPackages[-1]
    edgeToSend = dataPackage.edges.add()
    edgeToSend.v1.x = edge.v1.x
    edgeToSend.v1.y = edge.v1.y
    edgeToSend.v1.z = edge.v1.z
    edgeToSend.v2.x = edge.v2.x
    edgeToSend.v2.y = edge.v2.y
    edgeToSend.v2.z = edge.v2.z
    edgeToSend.prop.quality = edge.quality
    edgeToSend.prop.label = edge.label
    edgeToSend.prop.groupId = edge.groupId




def addTriangleFace(triangleFace):
    global structuresRemaining
    if structuresRemaining ==  0:
        structuresRemaining = numberOfStructuresToSend 
        dataPackage = structs_pb2.DataPackage()
        dataPackages.append(dataPackage)

    structuresRemaining = structuresRemaining -1
    dataPackage = dataPackages[-1]
    triangleFaceToSend = dataPackage.faces.add()
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


def addBlock(block):
    global structuresRemaining
    if structuresRemaining ==  0:
        structuresRemaining = numberOfStructuresToSend 
        dataPackage = structs_pb2.DataPackage()
        dataPackages.append(dataPackage)

    structuresRemaining = structuresRemaining -1
    dataPackage = dataPackages[-1]
    blockToSend = dataPackage.blocks.add()
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
  

    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
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

        while reply.type == structs_pb2.MessageInfo.ACK and len(dataPackages) > 0:

            dataPackage = dataPackages.pop(0)            
            dataToSend = dataPackage.SerializeToString()
            header = structs_pb2.Header()
            header.sizeOfData = sys.getsizeof(dataToSend)

            if len(dataPackages) == 0:
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
        global structuresRemaining 
        structuresRemaining = numberOfStructuresToSend
        dataPackage = structs_pb2.DataPackage()
        dataPackages.append(dataPackage)
        sock.close()


def breakpoint():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Send 
        message = structs_pb2.MessageInfo()
        message.type = structs_pb2.MessageInfo.BREAKPOINT
        bytesToSend =  message.SerializeToString()
        sent = sock.sendto(bytesToSend, (IPAdress, port))   


        # Receive acknowledge
        print 'waiting to receive'
        data, addr = sock.recvfrom(10)
        reply = structs_pb2.MessageInfo()
        reply.ParseFromString(data)

        if reply.type == structs_pb2.MessageInfo.REJECTED:
            sock.close()
            exit()                    

    finally:
        print 'closing socket'
        sock.close()


def render():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Send 
        message = structs_pb2.MessageInfo()
        message.type = structs_pb2.MessageInfo.RENDER
        bytesToSend =  message.SerializeToString()
        sent = sock.sendto(bytesToSend, (IPAdress, port))                

    finally:
        print 'closing socket'
        sock.close()


def clean():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Send 
        message = structs_pb2.MessageInfo()
        message.type = structs_pb2.MessageInfo.CLEAN
        bytesToSend =  message.SerializeToString()
        sent = sock.sendto(bytesToSend, (IPAdress, port))   


        # Receive acknowledge
        print 'waiting to receive'
        data, addr = sock.recvfrom(10)
        reply = structs_pb2.MessageInfo()
        reply.ParseFromString(data)

        if reply.type != structs_pb2.MessageInfo.ACK:
            sock.close()
            exit()                    

    finally:
        print 'closing socket'
        sock.close()
