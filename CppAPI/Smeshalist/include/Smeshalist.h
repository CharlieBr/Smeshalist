#ifndef SMESHALIST_H
#define SMESHALIST_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <list>
#include "structs.pb.h"
#include "Geometry.h"

#define CORE_PORT 8383
#define BUFFER_SIZE 1024
#define BATCH_SIZE 200

using namespace std;

class Smeshalist {
	public:
		~Smeshalist();
		static Smeshalist& GetInstance();
		void TestSmeshalist();
		void AddGeometry(Point2D &point);
		void AddGeometry(Point3D &point);
		void AddGeometry(Vertex &vertex);
        void AddGeometry(Edge &edge);
        void AddGeometry(Face &face);
        void AddGeometry(Block &block);
        void FlushBuffer();
        void Breakpoint() const;
        void Render() const;
	protected:
	private:
		int core_port;
		struct sockaddr_in core_addr;
		socklen_t core_addr_size;
		int core_socket;
		list<Point2D> points2d_to_send;
		list<Point3D> points3d_to_send;
		list<Vertex> vertexes_to_send;
		list<Edge> edges_to_send;
		list<Face> faces_to_send;
		list<Block> blocks_to_send;
		Smeshalist();
		void SetupSocket();
		int SendBytesToCore(const void* buffer, int buffer_size) const;
		int GetBytesFromCore(char* buffer, int buffer_size);
		structDefinitions::Properties* GetProperties(int group_id, string label, double quality) const;
		structDefinitions::Point3D* GetPoint3D(Point3D &point) const;
		void ProcessGeometry(Point2D &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Point3D &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Vertex &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Edge &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Face &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Block &element, structDefinitions::DataPackage &data_package) const;
		int GetElementsCount() const;
};

#endif // SMESHALIST_H
