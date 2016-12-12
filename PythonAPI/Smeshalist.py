"""Smeshalist module - Main API module which provide methods to add geometries for visualization algorithm"""
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
    """Return instance of Smeshalist class. Tool is using port of given number to connect to main window"""
    global port
    port = portNumber
    dataPackage = structs_pb2.DataPackage()
    dataPackages.append(dataPackage)


def addPoint3D(point3D):
    """Method adds Point3D object point3D to internal data buffer that stores structures to send for visualization"""
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
    """Method adds Vertex object vertex to internal data buffer that stores structures to send for visualization"""
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
    """Method adds Edge object edge to internal data buffer that stores structures to send for visualization"""
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
    """Method adds TriangleFace object triangleFace to internal data buffer that stores structures to send for visualization"""
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
    """Method adds Block object block to internal data buffer that stores structures to send for visualization"""
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
    """Send all structures stored in buffer to main window"""
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Send 
        message = structs_pb2.MessageInfo()
        message.type = structs_pb2.MessageInfo.DATA
        bytesToSend =  message.SerializeToString()
        sent = sock.sendto(bytesToSend, (IPAdress, port))	


        # Receive acknowledge
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
            data, addr = sock.recvfrom(10)
            reply.ParseFromString(data)                        

    finally:
        global structuresRemaining 
        structuresRemaining = numberOfStructuresToSend
        dataPackage = structs_pb2.DataPackage()
        dataPackages.append(dataPackage)
        sock.close()


def breakpoint():
    """Interrupts algorithm execution until proper option will be chosen in Smeshalist Manager window.
    In case continue option has been chosen algorithm is continued otherwise program is terminated."""    
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Send 
        message = structs_pb2.MessageInfo()
        message.type = structs_pb2.MessageInfo.BREAKPOINT
        bytesToSend =  message.SerializeToString()
        sent = sock.sendto(bytesToSend, (IPAdress, port))   


        # Receive acknowledge
        data, addr = sock.recvfrom(10)
        reply = structs_pb2.MessageInfo()
        reply.ParseFromString(data)

        if reply.type == structs_pb2.MessageInfo.REJECTED:
            sock.close()
            exit()                    

    finally:
        sock.close()


def render():
    """Method forces rendering sent structures in main window in case Dynamic rendering is turned off in Smeshalist Manager window."""
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Send 
        message = structs_pb2.MessageInfo()
        message.type = structs_pb2.MessageInfo.RENDER
        bytesToSend =  message.SerializeToString()
        sent = sock.sendto(bytesToSend, (IPAdress, port))                

    finally:
        sock.close()


def clean():
    """Method forces deleting all data from data structure tree in main window without affecting taken snapshots."""
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Send 
        message = structs_pb2.MessageInfo()
        message.type = structs_pb2.MessageInfo.CLEAN
        bytesToSend =  message.SerializeToString()
        sent = sock.sendto(bytesToSend, (IPAdress, port))   


        # Receive acknowledge
        data, addr = sock.recvfrom(10)
        reply = structs_pb2.MessageInfo()
        reply.ParseFromString(data)

        if reply.type != structs_pb2.MessageInfo.ACK:
            sock.close()
            exit()                    

    finally:
        sock.close()
