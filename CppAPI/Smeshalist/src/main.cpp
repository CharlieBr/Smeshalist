#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include "Smeshalist.h"
#include "Geometry.h"

using namespace std;

int N = 1000;
double frand(){
	return ((double)((double)rand()/(double)RAND_MAX));
}
int main() {

	GOOGLE_PROTOBUF_VERIFY_VERSION;

	Smeshalist tool = Smeshalist::GetInstance();
	srand(time(NULL));

	Point2D points2D[N];
	Point3D points3D[N];
	Vertex vertexes[N];

	for (int i = 0; i < N; i++){
		points2D[i] = Point2D(frand()*3.0, frand()*3.0);
		points2D[i].SetGroupId(0);
		tool.AddGeometry(points2D[i]);
	}

	for (int i = 0; i < N; i++){
		points3D[i] = Point3D(frand()*3.0, frand()*3.0,frand()*3.0);
		points3D[i].SetGroupId(1);
		tool.AddGeometry(points3D[i]);
	}

	for (int i = 0; i < N; i++){
		vertexes[i] = Point3D(frand()*3.0, frand()*3.0,frand()*3.0);
		vertexes[i].SetGroupId(2);
		tool.AddGeometry(vertexes[i]);
	}

    tool.FlushBuffer();


	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}
