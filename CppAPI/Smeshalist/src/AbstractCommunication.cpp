#include "AbstractCommunication.h"

AbstractCommuniation::AbstractCommuniation() {
	AbstractCommuniation::core_port = CORE_PORT;
}

AbstractCommuniation::AbstractCommuniation(int port_number) {
	AbstractCommuniation::core_port = port_number;
}
