#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include "Smeshalist.h"
#include "Geometry.h"

using namespace std;

int N = 10;
double frand(){
	return ((double)((double)rand()/(double)RAND_MAX));
}
Point3D genPoint() {
	return Point3D(frand()*3.0, frand()*3.0,frand()*3.0);
}
int main() {

	GOOGLE_PROTOBUF_VERIFY_VERSION;

	Smeshalist tool = Smeshalist::GetInstance();
	srand(time(NULL));

//	for (int i = 0; i < N; i++){
//		Vertex vertex = Point3D(frand()*3.0, frand()*3.0,frand()*3.0);
//		vertex.SetGroupId(2);
//		tool.AddGeometry(vertex);
//	}
//
//	for (int i = 0; i < N; i++){
//		Edge edge = Edge(genPoint(),genPoint());
//		edge.SetGroupId(3);
//		tool.AddGeometry(edge);
//	}

	for (int i = 0; i < N; i++){
		Face face = Face(genPoint(),genPoint(), genPoint());
		face.SetGroupId(4);
		tool.AddGeometry(face);
	}
    tool.FlushBuffer();
    tool.Render();
    tool.Breakpoint();

	for (int i = 0; i < N; i++){
		Block block= Block(genPoint(),genPoint(), genPoint(), genPoint());
		block.SetGroupId(5);
		tool.AddGeometry(block);
	}

    tool.FlushBuffer();
    tool.Render();


	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}
