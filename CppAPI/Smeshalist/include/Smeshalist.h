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

#ifdef __linux__
#include "LinuxCommunication.h"
#else
#include "WindowsCommunication.h"
#endif // __linux__

#define BUFFER_SIZE 1024
#define BATCH_SIZE 300

using namespace std;

class Smeshalist {
	public:
		~Smeshalist();
		static Smeshalist& GetInstance();
		static Smeshalist& GetInstance(int port_number);
		void AddGeometry(Point3D &point);
		void AddGeometry(Vertex &vertex);
        void AddGeometry(Edge &edge);
        void AddGeometry(Face &face);
        void AddGeometry(Block &block);
        void FlushBuffer();
        void Breakpoint();
        void Render() const;
        void Clean();
	protected:
	private:
		AbstractCommuniation *communication;
		list<Point3D> points3d_to_send;
		list<Vertex> vertexes_to_send;
		list<Edge> edges_to_send;
		list<Face> faces_to_send;
		list<Block> blocks_to_send;
		Smeshalist();
		Smeshalist(int port_number);
		structDefinitions::Properties* GetProperties(int group_id, string label, double quality) const;
		structDefinitions::Point3D* GetPoint3D(Point3D &point) const;
		void ProcessGeometry(Point3D &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Vertex &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Edge &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Face &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Block &element, structDefinitions::DataPackage &data_package) const;
		int GetElementsCount() const;
};

#endif // SMESHALIST_H
