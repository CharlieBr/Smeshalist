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
        void exportToOBJ(Data* dataTree);
    protected:
    private:
        ofstream exportedFile;
        std::map<string, int> elementPosition;
        int counter = 1;
        void writeVerticesToFile(Element* element);
        void treeIteration(Data* dataTree);

};

#endif // OBJEXPORTER_H
