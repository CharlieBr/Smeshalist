class Point2D:
    
    def __init__(self, x, y):
       self.x = x
       self.y = y
       self.quality = 0.0
       self.label = ""
       self.groupId = 0

class Point3D:

    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
        self.quality = 0.0
        self.label = ""
        self.groupId = 0


class Vertex:

    def __init__(self, point,  number):
        self.point = point
        self.number = number
        self.quality = 0.0
        self.label = ""
        self.groupId = 0

class Edge:

    def __init__(self, v1, v2):
        self.v1 = v1
        self.v2 = v2
        self.quality = 0.0
        self.label = ""
        self.groupId = 0


class TriangleFace:

    def __init__(self, v1, v2, v3):
        self.v1 = v1
        self.v2 = v2
        self.v3 = v3
        quality = 0.0
        label = ""
        groupId = 0


class Block:

    def __init__(self, v1, v2, v3, v4):
        self.v1 = v1
        self.v2 = v2 
        self.v3 = v3
        self.v4 = v4
        quality = 0.0
        label = ""
        groupId = 0

