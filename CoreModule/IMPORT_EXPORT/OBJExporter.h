#ifndef OBJEXPORTER_H
#define OBJEXPORTER_H

#include <iostream>
#include <fstream>
#include "AbstractDataTree.h"

class OBJExporter
{
    public:
        OBJExporter();
        void exportToOBJ(Data* dataTree);
    protected:
    private:
        ofstream exportedFile;
        void writeToFile(Element* element);
        void treeIteration(Data* dataTree);

};

#endif // OBJEXPORTER_H
