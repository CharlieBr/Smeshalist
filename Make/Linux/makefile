SMESHALIST_PATH = ../..
CPPAPI_PATH = $(SMESHALIST_PATH)/CppAPI
CORE_PATH = $(SMESHALIST_PATH)/CoreModule
STRUCTURES_PATH = $(CORE_PATH)/STRUCTURES
COMMUNICATION_PATH = $(CORE_PATH)/COMMUNICATION_MODULE
FILTERS_PATH = $(CORE_PATH)/FILTERS_MODULE

CC = g++
FLAGS = -std=c++11 -Wall
INCLUDES = -I$(STRUCTURES_PATH)/include -I$(COMMUNICATION_PATH)/include -I$(FILTERS_PATH)/include -I$(CPPAPI_PATH) -I$(CORE_PATH)/SmeshalistManager/proto
LIBS = lib/libGLU.a lib/libprotobuf.a -lGL -lglut

compile:
	mkdir obj
	#COMPILING STRUCTURES MODULE FROM CORE
	$(CC) $(FLAGS) $(INCLUDES) -c $(STRUCTURES_PATH)/src/AbstractDataTree.cpp -o obj/AbstractDataTree.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(STRUCTURES_PATH)/src/Color.cpp -o obj/Color.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(STRUCTURES_PATH)/src/Data.cpp -o obj/Data.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(STRUCTURES_PATH)/src/LinuxDataTree.cpp -o obj/LinuxDataTree.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(STRUCTURES_PATH)/src/Statistics.cpp -o obj/Statistics.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(STRUCTURES_PATH)/src/Structures.cpp -o obj/Structures.o
	#COMPILING COMMUNICATION MODULE FROM CORE
	$(CC) $(FLAGS) $(INCLUDES) -c $(COMMUNICATION_PATH)/src/AbstractServer.cpp -o obj/AbstractServer.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(COMMUNICATION_PATH)/src/LinuxServer.cpp -o obj/LinuxServer.o
	#COMPILING FILTERS MODULE FROM CORE
	$(CC) $(FLAGS) $(INCLUDES) -c $(FILTERS_PATH)/src/CoordinatesFilter.cpp -o obj/CoordinatesFilter.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(FILTERS_PATH)/src/GroupsFilter.cpp -o obj/GroupsFilter.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(FILTERS_PATH)/src/QualityFilter.cpp -o obj/QualityFilter.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(FILTERS_PATH)/src/TypesFilter.cpp -o obj/TypesFilter.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(FILTERS_PATH)/src/CMathUtils.cpp -o obj/CMathUtils.o
	#COMPILING STRUCTS FROM CPP API
	$(CC) $(FLAGS) $(INCLUDES) -c $(CPPAPI_PATH)/structs.pb.cc -o obj/structs.o
	#COMPILING COMMUNICATION PROTO FILE FROM SMESHALIST MANAGER
	$(CC) $(FLAGS) $(INCLUDES) -c $(CORE_PATH)/SmeshalistManager/proto/communication.pb.cc -o obj/communication.o
	#COMPILING MAIN FILE
	$(CC) $(FLAGS) $(INCLUDES) -c $(CORE_PATH)/rotateCamera.cpp -o obj/rotateCamera.o
	#
build:
	#BUILDING
	$(CC) -o CoreModule obj/structs.o obj/communication.o obj/AbstractServer.o obj/LinuxServer.o obj/CoordinatesFilter.o obj/GroupsFilter.o obj/QualityFilter.o obj/TypesFilter.o obj/CMathUtils.o obj/rotateCamera.o obj/AbstractDataTree.o obj/Color.o obj/Data.o obj/LinuxDataTree.o obj/Statistics.o obj/Structures.o $(LIBS)
	rm -r obj
all: compile build
