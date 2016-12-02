#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <cstring>

using namespace std;

class Geometry {
	public:
		virtual ~Geometry(){}
		void SetQuality(double q);
        double GetQuality() const;
        void SetGroupId(int id);
        int GetGroupId() const;
        void SetLabel(string l);
        string GetLabel() const;
	private:
		double quality;
		int group_id;
		string label;
};

class Point3D : public Geometry {
	public:
		Point3D();
        Point3D(double x, double y, double z);
		Point3D(double x, double y);
        void SetX(double value);
        void SetY(double value);
        void SetZ(double value);
        double GetX() const;
        double GetY() const;
        double GetZ() const;
	private:
		double x;
		double y;
		double z;
};

class Vertex : public Geometry {
	public:
		Vertex();
        Vertex(Point3D point3d);
		Vertex(double x, double y, double z);
        void SetPoint(Point3D point);
        Point3D GetPoint() const;
	private:
		Point3D point;
};

class Edge : public Geometry {
	public:
		Edge();
        Edge(Point3D v1, Point3D v2);
        void SetV1(Point3D point);
        void SetV2(Point3D point);
        Point3D GetV1() const;
        Point3D GetV2() const;
	private:
		Point3D v1;
		Point3D v2;
};

class Face : public Geometry {
	public:
		Face();
        Face(Point3D v1, Point3D v2, Point3D v3);
		void SetV1(Point3D point);
        void SetV2(Point3D point);
        void SetV3(Point3D point);
        Point3D GetV1() const;
        Point3D GetV2() const;
        Point3D GetV3() const;
	private:
		Point3D v1;
		Point3D v2;
		Point3D v3;
};

class Block : public Geometry {
	public:
		Block();
        Block(Point3D v1, Point3D v2, Point3D v3, Point3D v4);
        void SetV1(Point3D point);
        void SetV2(Point3D point);
        void SetV3(Point3D point);
        void SetV4(Point3D point);
        Point3D GetV1() const;
        Point3D GetV2() const;
        Point3D GetV3() const;
        Point3D GetV4() const;
	private:
		Point3D v1;
		Point3D v2;
		Point3D v3;
		Point3D v4;
};

#endif // GEOMETRY_H
