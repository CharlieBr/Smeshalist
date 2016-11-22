#ifndef OBJIMPORTER_H
#define OBJIMPORTER_H


#include <iostream>
#include <fstream>
#include <string.h>
#include "AbstractDataTree.h"
#include "Structures.h"

using namespace std;

class OBJImporter
{
    public:
        OBJImporter();
        void loadOBJFile(const char* path, AbstractDataTree* handler);
    protected:
    private:
        vector<Point3D*> vertices;
        vector<Edge*> edges;
        vector<Face*> faces;
        vector<int> verticesIndexes;
        void addToStructuresTree(AbstractDataTree* handler);


};

#endif // OBJIMPORTER_H
