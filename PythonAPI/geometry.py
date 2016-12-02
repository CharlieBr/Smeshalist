class Point3D:
    """Class which stores point coordinates. All other structure objects from geometry module use one or more Point3D objects to build the structure."""
    def __init__(self, x, y, z = None):
        """Class constructor for Point3D object. As a param it takes coordinates of the point. If z coordinate is not provided it is set to 0.0 by default"""
        self.x = x
        self.y = y
        if z is None:
            self.z = 0.0
        else:
            self.z = z


class Vertex:
    """Class which provides internal application format for vertex structure. Objects consist of Point3D point and properties: quality, label and groupId"""
    def __init__(self, point):
        """Class constructor for Vertex object. As a param it takes Point3D object point"""
	self.point = point
	self.quality = 0.0
        self.label = ""
        self.groupId = 0 


class Edge:
    """Class which provides internal application format for line structure. Objects consist of two Point3D points and properties: quality, label and groupId."""
    def __init__(self, v1, v2):
        """Class constructor for Edge object. As a param it takes two Point3D objects v1 and v2"""
        self.v1 = v1
        self.v2 = v2
        self.quality = 0.0
        self.label = ""
        self.groupId = 0


class TriangleFace:
    """ Class which provides internal application format for face structure. Objects consist of three Point3D points and properties: quality, label and groupId."""
    def __init__(self, v1, v2, v3):
        """Class constructor for TriangleFace object. As a param it takes three Point3D objects v1, v2 and v3"""
        self.v1 = v1
        self.v2 = v2
        self.v3 = v3
        self.quality = 0.0
        self.label = ""
        self.groupId = 0


class Block:
    """Class which provides internal application format for vertex structure. Objects consist of Point3D point and properties: quality, label and groupId"""
    def __init__(self, v1, v2, v3, v4):
        """Class constructor for Block object. As a param it takes four Point3D objects v1, v2, v3 and v4"""
        self.v1 = v1
        self.v2 = v2 
        self.v3 = v3
        self.v4 = v4
        self.quality = 0.0
        self.label = ""
        self.groupId = 0

