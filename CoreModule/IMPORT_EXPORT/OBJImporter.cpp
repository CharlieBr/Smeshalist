#include "OBJImporter.h"

OBJImporter::OBJImporter()
{
    //ctor
}


void OBJImporter::loadOBJFile(const char* path, AbstractDataTree* handler){

    FILE* importedFile = fopen(path, "r");
    if(importedFile == NULL){
        cerr<<"Error opening imported OBJ file !"<<endl;
        return;
    }

    while (1){
        char lineHeader[128];
        double x, y, z;
        int res = fscanf(importedFile, "%s", lineHeader);
        if(res == EOF){
            break;
        }

        if(strcmp(lineHeader, "v") == 0){

            fscanf(importedFile, "%lf %lf %lf\n", &x, &y, &z);
            cout<<x<<" "<<y<<" "<<z<<endl;
            Point3D* point = new Point3D(x, y, z);
            vertices.push_back(point);

        } else if(strcmp(lineHeader, "l") == 0) {

            int v1, v2;
            fscanf(importedFile, "%d %d\n", &v1, &v2);
            cout<<v1<<" "<<v2<<endl;
            vector<Point3D> points;
            points.push_back(*vertices.at(v1-1));
            points.push_back(*vertices.at(v2-1));
            Edge* edge = new Edge(&points);
            edges.push_back(edge);
            verticesIndexes.push_back(v1);
            verticesIndexes.push_back(v2);

        } else if(strcmp(lineHeader, "f") == 0){

            int v1, v2, v3;
            fscanf(importedFile, "%d %d %d\n", &v1, &v2, &v3);
            cout<<v1<<" "<<v2<<" "<<v3<<endl;
            vector<Point3D> points;
            points.push_back(*vertices.at(v1-1));
            points.push_back(*vertices.at(v2-1));
            points.push_back(*vertices.at(v3-1));
            Face* face = new Face(&points);
            faces.push_back(face);
            verticesIndexes.push_back(v1);
            verticesIndexes.push_back(v2);
            verticesIndexes.push_back(v3);
        }
    }

    cout<<"po petli"<<endl;

    int res = fclose(importedFile);
    if(res == EOF){
        cerr<<"Error during closing imported file"<<endl;
        return;
    }
    addToStructuresTree(handler);

    cout<<"dodalo"<<endl;

}



void OBJImporter::addToStructuresTree(AbstractDataTree* handler){
    for(int i=0; i<vertices.size(); i++){
        if(std::find(verticesIndexes.begin(), verticesIndexes.end(), i) == verticesIndexes.end()){
            Vertex* vertex = new Vertex(*vertices.at(i));
            handler->add(0, vertex);
        }
    }

    for(Edge* edge : edges){
        handler->add(0, edge);
    }

    for(Face* face : faces){
        handler->add(0, face);
    }

}

