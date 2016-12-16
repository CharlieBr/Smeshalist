#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <ctime>
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

	Smeshalist tool = Smeshalist::GetInstance(true);
	srand(time(NULL));

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
	
	tool.Breakpoint();
	cout << "Hard reset now" << endl;

	tool = Smeshalist::GetInstance(true);
	
	cout << "Reset done" << endl;
	for (int i = 0; i < N; i++) {
		Vertex v = Vertex(genPoint());
		v.SetGroupId(1);
		tool.AddGeometry(v);
	}
	tool.FlushBuffer();
	tool.Render();
	tool.Breakpoint();

	google::protobuf::ShutdownProtobufLibrary();
	system("pause");
	return 0;
}
