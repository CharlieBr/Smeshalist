class Point3D:

    def __init__(self, x, y, z = None):
        self.x = x
        self.y = y
        if z is None:
            self.z = 0.0
        else:
            self.z = z


class Vertex:

    def __init__(self, point):
	self.point = point
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
        self.quality = 0.0
        self.label = ""
        self.groupId = 0


class Block:

    def __init__(self, v1, v2, v3, v4):
        self.v1 = v1
        self.v2 = v2 
        self.v3 = v3
        self.v4 = v4
        self.quality = 0.0
        self.label = ""
        self.groupId = 0

