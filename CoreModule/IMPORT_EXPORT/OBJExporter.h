#ifndef OBJEXPORTER_H
#define OBJEXPORTER_H

#include <iostream>
#include <fstream>
#include <string>
#include "AbstractDataTree.h"

class OBJExporter
{
    public:
        OBJExporter();
        void exportToOBJ(Data* dataTree, string fileName);
    protected:
    private:
        ofstream exportedFile;
        std::map<string, int> elementPosition;
        int currentTypeCounter = 0;
        void writeVerticesToFile(Element* element);
        void writeEdgeToFile();
        void writeFaceToFile();
        void writeBlockToFile();
        void treeIteration(Data* dataTree);

};

#endif // OBJEXPORTER_H
