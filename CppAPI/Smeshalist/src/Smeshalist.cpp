#include "Smeshalist.h"

using namespace std;

Smeshalist::Smeshalist() {
    #ifdef __linux__
	communication = new LinuxCommunication();
	#else
	communication = new WindowsCommunication();
    #endif // __linux__
	communication->SetupSocket();
}

Smeshalist::Smeshalist(int port_number) {
	#ifdef __linux__
	communication = new LinuxCommunication(port_number);
	#else
	communication = new WindowsCommunication(port_number);
    #endif // __linux__
	communication->SetupSocket();
}

Smeshalist::~Smeshalist(){
    communication->CleanupSocket();
}

Smeshalist& Smeshalist::GetInstance() {
	static Smeshalist INSTANCE;
	return INSTANCE;
}

Smeshalist& Smeshalist::GetInstance(int port_number){
	static Smeshalist INSTANCE(port_number);
	return INSTANCE;
}

structDefinitions::Properties* Smeshalist::GetProperties(int group_id, string label, double quality) const {
	structDefinitions::Properties *properties = new structDefinitions::Properties();
	properties->set_label(label);
	properties->set_groupid(group_id);
	properties->set_quality(quality);
	return properties;
}

structDefinitions::Point3D* Smeshalist::GetPoint3D(Point3D &point) const {
	structDefinitions::Point3D* point3d = new structDefinitions::Point3D();
    point3d->set_x(point.GetX());
    point3d->set_y(point.GetY());
    point3d->set_z(point.GetZ());
    return point3d;

}

void Smeshalist::AddGeometry(Point3D &point) {
	Smeshalist::points3d_to_send.push_front(point);
}

void Smeshalist::AddGeometry(Vertex &vertex) {
	Smeshalist::vertexes_to_send.push_front(vertex);
}

void Smeshalist::AddGeometry(Edge &edge) {
	Smeshalist::edges_to_send.push_front(edge);
}

void Smeshalist::AddGeometry(Face &face) {
	Smeshalist::faces_to_send.push_front(face);
}

void Smeshalist::AddGeometry(Block &block) {
	Smeshalist::blocks_to_send.push_front(block);
}

void Smeshalist::ProcessGeometry(Point3D &element, structDefinitions::DataPackage &data_package) const {
	structDefinitions::Point3D* point3d = data_package.add_points3d();
    point3d->set_x(element.GetX());
    point3d->set_y(element.GetY());
    point3d->set_z(element.GetZ());
}

void Smeshalist::ProcessGeometry(Vertex &element, structDefinitions::DataPackage &data_package) const {
    structDefinitions::Vertex* vertex = data_package.add_vertexes();
    Point3D point = element.GetPoint();
    vertex->set_allocated_point(Smeshalist::GetPoint3D(point));
    vertex->set_number(0.0);
    vertex->set_allocated_prop(GetProperties(element.GetGroupId(), element.GetLabel(), element.GetQuality()));
}

void Smeshalist::ProcessGeometry(Edge &element, structDefinitions::DataPackage &data_package) const {
    structDefinitions::Edge* edge = data_package.add_edges();
    Point3D v1 = element.GetV1();
    Point3D v2 = element.GetV2();
    edge->set_allocated_v1(GetPoint3D(v1));
    edge->set_allocated_v2(GetPoint3D(v2));
    edge->set_allocated_prop(GetProperties(element.GetGroupId(), element.GetLabel(), element.GetQuality()));
}
void Smeshalist::ProcessGeometry(Face &element, structDefinitions::DataPackage &data_package) const {
    structDefinitions::TriangleFace* face = data_package.add_faces();
    Point3D v1 = element.GetV1();
    Point3D v2 = element.GetV2();
    Point3D v3 = element.GetV3();
    face->set_allocated_v1(GetPoint3D(v1));
    face->set_allocated_v2(GetPoint3D(v2));
    face->set_allocated_v3(GetPoint3D(v3));
    face->set_allocated_prop(GetProperties(element.GetGroupId(), element.GetLabel(), element.GetQuality()));
}
void Smeshalist::ProcessGeometry(Block &element, structDefinitions::DataPackage &data_package) const {
	structDefinitions::Block* block = data_package.add_blocks();
	Point3D v1 = element.GetV1();
    Point3D v2 = element.GetV2();
    Point3D v3 = element.GetV3();
    Point3D v4 = element.GetV4();
	block->set_allocated_v1(GetPoint3D(v1));
	block->set_allocated_v2(GetPoint3D(v2));
	block->set_allocated_v3(GetPoint3D(v3));
	block->set_allocated_v4(GetPoint3D(v4));
	block->set_allocated_prop(GetProperties(element.GetGroupId(), element.GetLabel(), element.GetQuality()));
}

int Smeshalist::GetElementsCount() const {
    return Smeshalist::points3d_to_send.size() +
    Smeshalist::vertexes_to_send.size() + Smeshalist::edges_to_send.size() +
    Smeshalist::faces_to_send.size() + Smeshalist::blocks_to_send.size();
}

void Smeshalist::FlushBuffer() {
	cout<<Smeshalist::GetElementsCount()<<" elements waiting to be sent"<<endl;
	char *out_buffer;
	char in_buffer[BUFFER_SIZE];
	int n_bytes, size;

	structDefinitions::MessageInfo message_info;
	message_info.set_type(structDefinitions::MessageInfo_Type_DATA);
	size = message_info.ByteSize();
	out_buffer = new char[size];

	message_info.SerializeToArray(out_buffer, size);
	communication->SendBytesToCore(out_buffer, size);

	n_bytes = communication->GetBytesFromCore(in_buffer, BUFFER_SIZE);

	if (n_bytes < 0) {
		cout<<"Error when receiving bytes from core"<<endl;
	}

	structDefinitions::MessageInfo ack_message_info;
	if (!ack_message_info.ParseFromArray(in_buffer, n_bytes)) {
		cout<<"Error when parsing message from core"<<endl;
	}

	bool end_of_data = false;
	while (Smeshalist::GetElementsCount() > 0 && ack_message_info.type() == structDefinitions::MessageInfo_Type_ACK) {

		structDefinitions::DataPackage data_package;
		int n_elements_in_package;


		if (Smeshalist::GetElementsCount() > BATCH_SIZE) {
			n_elements_in_package = BATCH_SIZE;

		} else {
			n_elements_in_package = Smeshalist::GetElementsCount();
            cout<<"--------------------------------endofdata"<<endl;
			end_of_data = true;
		}

		for (int i = 0; i < n_elements_in_package; i++) {

			if (!Smeshalist::points3d_to_send.empty()) {
				Point3D element = Smeshalist::points3d_to_send.front();
				Smeshalist::ProcessGeometry(element, data_package);
				Smeshalist::points3d_to_send.pop_front();
			} else if (!Smeshalist::vertexes_to_send.empty()) {
				Vertex element = Smeshalist::vertexes_to_send.front();
				Smeshalist::ProcessGeometry(element, data_package);
				Smeshalist::vertexes_to_send.pop_front();
			} else if (!Smeshalist::edges_to_send.empty()) {
				Edge element = Smeshalist::edges_to_send.front();
				Smeshalist::ProcessGeometry(element, data_package);
				Smeshalist::edges_to_send.pop_front();
			} else if (!Smeshalist::faces_to_send.empty()) {
				Face element = Smeshalist::faces_to_send.front();
				Smeshalist::ProcessGeometry(element, data_package);
				Smeshalist::faces_to_send.pop_front();
			} else if (!Smeshalist::blocks_to_send.empty()) {
				Block element = Smeshalist::blocks_to_send.front();
				Smeshalist::ProcessGeometry(element, data_package);
				Smeshalist::blocks_to_send.pop_front();
			}

		}

		//create header
		structDefinitions::Header header;
		header.set_endofdata(end_of_data);
		header.set_sizeofdata(data_package.ByteSize());

		size = header.ByteSize();
		out_buffer = new char[size];

		header.SerializeToArray(out_buffer, size);
		communication->SendBytesToCore(out_buffer, size);

		size = data_package.ByteSize();
		out_buffer = new char[size];

		data_package.SerializeToArray(out_buffer, size);
		communication->SendBytesToCore(out_buffer, size);

		n_bytes = communication->GetBytesFromCore(in_buffer, BUFFER_SIZE);

		if (n_bytes < 0) {
			cout<<"Error when receiving bytes from core"<<endl;
		}

		if (!ack_message_info.ParseFromArray(in_buffer, n_bytes)) {
			cout<<"Error when parsing message from core"<<endl;
		}
	}
}
void Smeshalist::Render() const {
	char *out_buffer;
	int size;

	structDefinitions::MessageInfo message_info;
	message_info.set_type(structDefinitions::MessageInfo_Type_RENDER);
	size = message_info.ByteSize();
	out_buffer = new char[size];

	message_info.SerializeToArray(out_buffer, size);
	communication->SendBytesToCore(out_buffer, size);
}

void Smeshalist::Breakpoint() {
	char *out_buffer;
	char in_buffer[BUFFER_SIZE];
	int size, n_bytes;

	structDefinitions::MessageInfo message_info;
	message_info.set_type(structDefinitions::MessageInfo_Type_BREAKPOINT);
	size = message_info.ByteSize();
	out_buffer = new char[size];

	message_info.SerializeToArray(out_buffer, size);
	communication->SendBytesToCore(out_buffer, size);

	n_bytes = communication->GetBytesFromCore(in_buffer, BUFFER_SIZE);

	if (n_bytes < 0) {
		cout<<"Error when receiving bytes from core"<<endl;
	}

	structDefinitions::MessageInfo ack_message_info;
	if (!ack_message_info.ParseFromArray(in_buffer, n_bytes)) {
		cout<<"Error when parsing message from core"<<endl;
	}
	if (ack_message_info.type() == structDefinitions::MessageInfo_Type_REJECTED) {
        cout<<"ABORT from SmeshalistManager"<<endl;
        exit(0);
	}
}

void Smeshalist::Clean() {
	char *out_buffer;
	char in_buffer[BUFFER_SIZE];
	int size, n_bytes;

	structDefinitions::MessageInfo message_info;
	message_info.set_type(structDefinitions::MessageInfo_Type_CLEAN);
	size = message_info.ByteSize();
	out_buffer = new char[size];

	message_info.SerializeToArray(out_buffer, size);
	communication->SendBytesToCore(out_buffer, size);

	n_bytes = communication->GetBytesFromCore(in_buffer, BUFFER_SIZE);

	if (n_bytes < 0) {
		cout<<"Error when receiving bytes from core"<<endl;
	}

	structDefinitions::MessageInfo ack_message_info;
	if (!ack_message_info.ParseFromArray(in_buffer, n_bytes)) {
		cout<<"Error when parsing message from core"<<endl;
	}
	if (ack_message_info.type() != structDefinitions::MessageInfo_Type_ACK) {
        cout<<"Error after sending CLEAN request"<<endl;
        exit(0);
	}
}
