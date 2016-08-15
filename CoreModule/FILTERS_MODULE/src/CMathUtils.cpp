#include "CMathUtils.h"

Vector::Vector(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(Point3D* begin, Point3D* end) {
    this -> begin = begin;
    this -> end = end;

    x = end -> get_x() - begin -> get_x();
    y = end -> get_y() - begin -> get_y();
    z = end -> get_z() - begin -> get_z();
}

double CMathUtils::computeScalarProduct(Vector* a, Vector* b) {
    return a->x*b->x + a->y*b->y + a->z*b->z;
}

double CMathUtils::computeCosinus(Vector* a, Vector* b) {
    double denominator = a->length() * b->length();

    if (denominator == 0) {
        std::cerr << "Product of vectors length is equal to zero\n";
        return -2;
    }

    double numerator = computeScalarProduct(a, b);
    return numerator/denominator;
}

vector<Point3D*> CMathUtils::sortPoints(vector<Point3D*> points) {
    if (points.size() <= 2) {
        return points;
    }

    vector<Point3D*> result;

    Point3D* p0 = points.back();
    points.pop_back();
    result.push_back(p0);

    vector<Vector*> vectors;
    for (Point3D* point : points) {
        vectors.push_back(new Vector(p0, point));
    }

    Vector* rand = vectors.front();
    Vector* opposite = rand;
    double min = 1;
    for (Vector* v : vectors) {
        double cos = computeCosinus(rand, v);
        if (cos <= min) {
            min = cos;
            opposite = v;
        }
    }

    result.push_back(opposite->getEnd());
    for (unsigned int i=0; i<vectors.size(); i++) {
        if(vectors[i] == opposite) {
            vectors.erase(vectors.begin() + i);
            break;
        }
    }

    while(!vectors.empty()) {
        Vector* maxCos = vectors.front();      //vector with smallest angle
        double max = -1;
        for(Vector* v : vectors) {
            double cos = computeCosinus(opposite, v);
            if (cos >= max) {
                max = cos;
                maxCos = v;
            }
        }

        result.push_back(maxCos->getEnd());
        for (unsigned int i=0; i<vectors.size(); i++) {
            if(vectors[i] == maxCos) {
                vectors.erase(vectors.begin() + i);
                break;
            }
        }
    }

    return result;
}

Vector* CMathUtils::getVector(Point3D* begin, Point3D* end) {
    return new Vector(begin, end);
}

Point3D* Vector::getBegin() {
    return begin;
}

Point3D* Vector::getEnd() {
    return end;
}

double Vector::length() {
    return std::sqrt(x*x + y*y + z*z);
}
