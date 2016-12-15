#ifndef SMESHALIST_H
#define SMESHALIST_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
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
		/**
		 * Method implements singleton pattern. Returns instance of class Smeshalist.
		 * Tool uses default port number - 8383.
		 * @return instance of Smeshalist
		 */
		static Smeshalist& GetInstance();
		/**
		* Method implements singleton pattern. Returns instance of class Smeshalist.
		* Tool uses given port number.
		* @param port_number port on witch the tool will connect to main window
		* @return instance of Smeshalist
		*/
		static Smeshalist& GetInstance(int port_number);
		/**
		* Method implements singleton pattern. Returns instance of class Smeshalist.
		* Tool uses default port number - 8383. Hard_reset flag indicates if the tool should
		* reset all settings and contents from Core modules.
		* @param hard_reset if set to true, all structures already stored in Core module will be removed and all settings will be reset
		* @return instance of Smeshalist
		*/
		static Smeshalist& GetInstance(bool hard_reset);
		/**
		* Method implements singleton pattern. Returns instance of class Smeshalist.
		* Tool uses given port number. Hard_reset flag indicates if the tool should
		* reset all settings and contents from Core modules.
		* @param port_number port on witch the tool will connect to main window
		* @param hard_reset if set to true, all structures already stored in Core module will be removed and all settings will be reset
		* @return instance of Smeshalist
		*/
		static Smeshalist& GetInstance(int port_number, bool hard_reset);
		/**
		* Method adds Vertex structure to internal data buffer that stores structures to send for visualization.
		* @param vertex Vertex structure
		*/
		void AddGeometry(Vertex &vertex);
		/**
		* Method adds Edge structure to internal data buffer that stores structures to send for visualization.
		* @param edge Edge structure
		*/
        void AddGeometry(Edge &edge);
		/**
		* Method adds Face structure to internal data buffer that stores structures to send for visualization.
		* @param face Face structure
		*/
        void AddGeometry(Face &face);
		/**
		* Method adds Block structure to internal data buffer that stores structures to send for visualization.
		* @param block Block structure
		*/
        void AddGeometry(Block &block);
		/**
		 * Sends all structures stored in buffer to main window.
		 */
        void FlushBuffer();
		/**
		 * Suspends algorithm execution until proper option will be chosen in Smeshalist Manager window.
		 * In case continue option has been chosen algorithm is continued otherwise program is terminated.
		 */
        void Breakpoint();
		/**
		 * Method forces rendering sent structures in main window when 'Dynamic rendering' is turned off in Smeshalist Manager window.
		 */
        void Render() const;
		/**
		 * Method forces deleting all data from data structure tree in main window without affecting taken snapshots.
		 */
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
		void ProcessGeometry(Vertex &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Edge &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Face &element, structDefinitions::DataPackage &data_package) const;
		void ProcessGeometry(Block &element, structDefinitions::DataPackage &data_package) const;
		int GetElementsCount() const;
		void sendMessageInfo(structDefinitions::MessageInfo_Type type) const;
		structDefinitions::MessageInfo receiveMessageInfo() const;
		structDefinitions::MessageInfo receiveMessageInfo(bool with_timeout) const;
};

#endif // SMESHALIST_H
