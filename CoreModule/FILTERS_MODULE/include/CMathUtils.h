#ifndef CMATHUTILS_H
#define CMATHUTILS_H

#include<cmath>
#include<iostream>
#include "Structures.h"

class Vector;

class CMathUtils
{
    public:
        static double computeScalarProduct(Vector*, Vector*);
        static double computeCosinus(Vector*, Vector*);
        static Vector* getVector(Point3D*, Point3D*);
        static vector<Point3D*> sortPoints(vector<Point3D*>);
    protected:
    private:
};

class Vector {
    public:
        Vector(double, double, double);
        Vector(Point3D*, Point3D*);

        double x;
        double y;
        double z;

        double length();
        Point3D* getBegin();
        Point3D* getEnd();
    private:
        Point3D* begin;
        Point3D* end;
};

#endif // CMATHUTILS_H
