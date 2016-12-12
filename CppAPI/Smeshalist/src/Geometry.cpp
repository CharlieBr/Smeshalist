#include "Geometry.h"

using namespace std;

//GEOMETRY

void Geometry::SetQuality(double q) {
    Geometry::quality = q;
}

double Geometry::GetQuality() const {
    return Geometry::quality;
}

void Geometry::SetGroupId(int id) {
    Geometry::group_id = id;
}

int Geometry::GetGroupId() const {
	return Geometry::group_id;
}

void Geometry::SetLabel(string l) {
	Geometry::label = l;
}

string Geometry::GetLabel() const {
    return Geometry::label;
}

//POINT3D

Point3D::Point3D() {
	SetGroupId(0);
    SetLabel("");
    SetQuality(0.0);
}

Point3D::Point3D(double x, double y, double z) : Point3D() {
    Point3D::x = x;
    Point3D::y = y;
    Point3D::z = z;
}

Point3D::Point3D(double x, double y) {
	Point3D::x = x;
	Point3D::y = y;
	Point3D::z = 0.0;
}

void Point3D::SetX(double value) {
    Point3D::x = value;
}

void Point3D::SetY(double value) {
    Point3D::y = value;
}

void Point3D::SetZ(double value) {
    Point3D::z = value;
}

double Point3D::GetX() const {
	return Point3D::x;
}

double Point3D::GetY() const {
	return Point3D::y;
}

double Point3D::GetZ() const {
	return Point3D::z;
}

//VERTEX

Vertex::Vertex() {
	SetGroupId(0);
    SetLabel("");
    SetQuality(0.0);
}

Vertex::Vertex(Point3D point3d) : Vertex() {
    Vertex::point = point3d;
}

Vertex::Vertex(double x, double y, double z) : Vertex() {
    Vertex::point = Point3D(x, y, z);
}

void Vertex::SetPoint(Point3D point) {
    Vertex::point = point;
}

Point3D Vertex::GetPoint() const {
	return Vertex::point;
}

//EDGE

Edge::Edge() {
	SetGroupId(0);
    SetLabel("");
    SetQuality(0.0);
}

Edge::Edge(Point3D v1, Point3D v2) : Edge() {
    Edge::v1 = v1;
    Edge::v2 = v2;
}

void Edge::SetV1(Point3D point) {
	Edge::v1 = point;
}

void Edge::SetV2(Point3D point) {
	Edge::v2 = point;
}

Point3D Edge::GetV1() const {
	return Edge::v1;
}

Point3D Edge::GetV2() const {
	return Edge::v2;
}

//FACE

Face::Face() {
	SetGroupId(0);
    SetLabel("");
    SetQuality(0.0);
}

Face::Face(Point3D v1, Point3D v2, Point3D v3) : Face() {
    Face::v1 = v1;
    Face::v2 = v2;
    Face::v3 = v3;
}

void Face::SetV1(Point3D point) {
    Face::v1 = point;
}

void Face::SetV2(Point3D point) {
    Face::v2 = point;
}

void Face::SetV3(Point3D point) {
    Face::v3 = point;
}

Point3D Face::GetV1() const {
	return Face::v1;
}

Point3D Face::GetV2() const {
	return Face::v2;
}

Point3D Face::GetV3() const {
	return Face::v3;
}

//BLOCK

Block::Block() {
	SetGroupId(0);
    SetLabel("");
    SetQuality(0.0);
}

Block::Block(Point3D v1, Point3D v2, Point3D v3, Point3D v4) : Block() {
    Block::v1 = v1;
    Block::v2 = v2;
    Block::v3 = v3;
    Block::v4 = v4;
}

void Block::SetV1(Point3D point) {
	Block::v1 = point;
}

void Block::SetV2(Point3D point) {
	Block::v2 = point;
}

void Block::SetV3(Point3D point) {
	Block::v3 = point;
}

void Block::SetV4(Point3D point) {
	Block::v4 = point;
}

Point3D Block::GetV1() const {
	return Block::v1;
}

Point3D Block::GetV2() const {
	return Block::v2;
}

Point3D Block::GetV3() const {
	return Block::v3;
}

Point3D Block::GetV4() const {
	return Block::v4;
}
