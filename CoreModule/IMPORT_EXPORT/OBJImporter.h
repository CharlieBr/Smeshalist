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
        void loadOBJFile(Data* handler, string path);
    protected:
    private:
        vector<Point3D*> vertices;
        vector<Edge*> edges;
        vector<Face*> faces;
        vector<Block*> blocks;
        vector<int> verticesIndexes;
        void addToStructuresTree(Data* handler);


};

#endif // OBJIMPORTER_H
