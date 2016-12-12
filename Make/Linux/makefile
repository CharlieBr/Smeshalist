SMESHALIST_PATH = ../..
CPPAPI_PATH = $(SMESHALIST_PATH)/CppAPI/Smeshalist
CORE_PATH = $(SMESHALIST_PATH)/CoreModule
STRUCTURES_PATH = $(CORE_PATH)/STRUCTURES
COMMUNICATION_PATH = $(CORE_PATH)/COMMUNICATION_MODULE
FILTERS_PATH = $(CORE_PATH)/FILTERS_MODULE
XML_PARSER_PATH = $(CORE_PATH)/XML_PARSER
IMPORT_EXPORT_PATH = $(CORE_PATH)/IMPORT_EXPORT
GLEW_PATH = $(CORE_PATH)/GLEWlib

CC = g++
FLAGS = -std=c++11 -Wall
INCLUDES = -I$(CORE_PATH) -I$(GLEW_PATH) -I$(IMPORT_EXPORT_PATH) -I$(STRUCTURES_PATH)/include -I$(COMMUNICATION_PATH)/include -I$(FILTERS_PATH)/include -I$(XML_PARSER_PATH)/include -I$(CPPAPI_PATH)/include -I$(CORE_PATH)/SmeshalistManager/proto
LIBS = lib/*.a -lGL -lglut

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
	#COMPILING XML PARSER MODULE FROM CORE
	$(CC) $(FLAGS) $(INCLUDES) -c $(XML_PARSER_PATH)/src/UserPreferencesManager.cpp -o obj/UserPreferencesManager.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(XML_PARSER_PATH)/src/XMLNode.cpp -o obj/XMLNode.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(XML_PARSER_PATH)/src/XMLParser.cpp -o obj/XMLParser.o
	#COMPILING IMPORT EXPORT MODULE
	$(CC) $(FLAGS) $(INCLUDES) -c $(IMPORT_EXPORT_PATH)/OBJExporter.cpp -o obj/OBJExporter.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(IMPORT_EXPORT_PATH)/OBJImporter.cpp -o obj/OBJImporter.o
	#COMPILING STRUCTS FROM CPP API
	$(CC) $(FLAGS) $(INCLUDES) -c $(CPPAPI_PATH)/src/structs.pb.cc -o obj/structs.o
	#COMPILING COMMUNICATION PROTO FILE FROM SMESHALIST MANAGER
	$(CC) $(FLAGS) $(INCLUDES) -c $(CORE_PATH)/SmeshalistManager/proto/communication.pb.cc -o obj/communication.o
	#COMPILING MAIN FILES
	$(CC) $(FLAGS) $(INCLUDES) -c $(CORE_PATH)/print.cpp -o obj/print.o
	$(CC) $(FLAGS) $(INCLUDES) -c $(CORE_PATH)/rotateCamera.cpp -o obj/rotateCamera.o
	#
build:
	#BUILDING
	ar rvs lib/CORE.a obj/*.o
	$(CC) -o CoreModule $(LIBS)
	rm -r obj
all: compile build
