#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <cstring>

using namespace std;

/**
 * Base class of all geometry classes. It holds all the geometry's properties.
 */
class Geometry {
	public:
		virtual ~Geometry(){}
		/**
		 * Sets the quality property.
		 * @param q value to be set
		 */
		void SetQuality(double q);
		/**
		 * Returns value of geometry's quality property.
		 * @returns value of quality property
		 */
        double GetQuality() const;
		/**
		* Sets the group_id property.
		* @param id value to be set
		*/
        void SetGroupId(int id);
		/**
		* Returns value of geometry's group_id property.
		* @returns value of group_id property
		*/
        int GetGroupId() const;
		/**
		* Sets the label of geometry.
		* @param l string containing label to be set
		*/
        void SetLabel(string l);
		/**
		* Returns geometry's label.
		* @returns geometry's label
		*/
        string GetLabel() const;
	private:
		double quality;
		int group_id;
		string label;
};

/**
 * Class which stores point coordinates. All other structure objects from Geometry.h use one or more Point3D
 * objects to build the structure. 
 */
class Point3D : public Geometry {
	public:
		/**
		 * Empty class constructor.
		 */
		Point3D();
		/**
		 * Class constructor.
		 * @param x the x coordinate
		 * @param y the y coordinate
		 * @param z the z coordinate
		 * 
		 */
        Point3D(double x, double y, double z);
		/**
		 * Class constructor for point in case of using it as a 2D point structure.
		 * @param x the x coordinate
		 * @param y the y coordinate
		 */
		Point3D(double x, double y);
		/**
		 * Method sets x coordinate of the object.
		 * @param value value to be set
		 */
        void SetX(double value);
		/**
		 * Method sets y coordinate of the object.
		 * @param value value to be set
		 */
        void SetY(double value);
		/**
		 * Method sets z coordinate of the object.
		 * @param value value to be set
		 */
        void SetZ(double value);
		/**
		 * Returns the x coordinate.
		 * @return x coordinate
		 */
        double GetX() const;
		/**
 		 * Returns the y coordinate.
		 * @return y coordinate
		 */
        double GetY() const;
		/**
		 * Returns the z coordinate.
		 * @return z coordinate
		 */
        double GetZ() const;
	private:
		double x;
		double y;
		double z;
};

/**
 * Class which provides internal application format for 'vertex' structure.
 */
class Vertex : public Geometry {
	public:
		/**
		* Empty class constructor.
		*/
		Vertex();
		/**
		* Class constructor with Point3D argument.
		* @param point3d point representing vertex
		*/
        Vertex(Point3D point3d);
		/**
		* Class constructor with coordinates. Creates Point3D with given coordinates.
		* @param x the x coordinate
		* @param y the y coordinate
		* @param z the z coordinate
		*/
		Vertex(double x, double y, double z);
		/**
		* Method sets point field of the object.
		* @param point point representing the vertex
		*/
        void SetPoint(Point3D point);
		/**
		* Returns point representing vertex.
		* @return point representing vertex
		*/
        Point3D GetPoint() const;
	private:
		Point3D point;
};

/**
* Class which provides internal application format for 'edge' structure.
*/
class Edge : public Geometry {
	public:
		/**
		* Empty class constructor.
		*/
		Edge();
		/**
		* Class constructor with Point3D arguments, representing two ends of edge.
		* @param v1 point representing one end of edge
		* @param v2 point representing second end of edge
		*/
        Edge(Point3D v1, Point3D v2);
		/**
		* Method sets v1 field of the object.
		* @param point point representing the one end of edge
		*/
        void SetV1(Point3D point);
		/**
		* Method sets v2 field of the object.
		* @param point point representing the second end of edge
		*/
        void SetV2(Point3D point);
		/**
		* Returns v1.
		* @return point representing one end of edge
		*/
        Point3D GetV1() const;
		/**
		* Returns v2.
		* @return point representing second end of edge
		*/
        Point3D GetV2() const;
	private:
		Point3D v1;
		Point3D v2;
};

/**
* Class which provides internal application format for 'face' structure.
*/
class Face : public Geometry {
	public:
		/**
		* Empty class constructor.
		*/
		Face();
		/**
		* Class constructor with Point3D arguments, representing points creating face.
		* @param v1 first point creating face
		* @param v2 second point creating face
		* @param v3 third point creating face
		*/
        Face(Point3D v1, Point3D v2, Point3D v3);
		/**
		* Method sets v1 field of the object.
		* @param point first point creating face
		*/
		void SetV1(Point3D point);
		/**
		* Method sets v2 field of the object.
		* @param point second point creating face
		*/
		void SetV2(Point3D point);
		/**
		* Method sets v3 field of the object.
		* @param point third point creating face
		*/
        void SetV3(Point3D point);
		/**
		* Returns v1.
		* @return first point creating face
		*/
        Point3D GetV1() const;
		/**
		* Returns v2.
		* @return second point creating face
		*/
		Point3D GetV2() const;
		/**
		* Returns v3.
		* @return third point creating face
		*/
        Point3D GetV3() const;
	private:
		Point3D v1;
		Point3D v2;
		Point3D v3;
};

/**
* Class which provides internal application format for 'block' structure.
*/
class Block : public Geometry {
	public:
		/**
		* Empty class constructor.
		*/
		Block();
		/**
		* Class constructor with Point3D arguments, representing points creating block.
		* @param v1 first point creating block
		* @param v2 second point creating block
		* @param v3 third point creating block
		* @param v3 fourth point creating block
		*/
        Block(Point3D v1, Point3D v2, Point3D v3, Point3D v4);
		/**
		* Method sets v1 field of the object.
		* @param point first point creating block
		*/
        void SetV1(Point3D point);
		/**
		* Method sets v2 field of the object.
		* @param point second point creating block
		*/
        void SetV2(Point3D point);
		/**
		* Method sets v3 field of the object.
		* @param point third point creating block
		*/
        void SetV3(Point3D point);
		/**
		* Method sets v4 field of the object.
		* @param point fourth point creating block
		*/
        void SetV4(Point3D point);
		/**
		* Returns v1.
		* @return first point creating block
		*/
        Point3D GetV1() const;
		/**
		* Returns v2.
		* @return second point creating block
		*/
        Point3D GetV2() const;
		/**
		* Returns v3.
		* @return third point creating block
		*/
        Point3D GetV3() const;
		/**
		* Returns v4.
		* @return fourth point creating block
		*/
        Point3D GetV4() const;
	private:
		Point3D v1;
		Point3D v2;
		Point3D v3;
		Point3D v4;
};

#endif // GEOMETRY_H
