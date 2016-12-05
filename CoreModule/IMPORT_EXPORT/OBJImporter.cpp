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
        bool working = true;
        if(working == false) {
            break;
        }
        int res = fscanf(importedFile, "%s[ ]", lineHeader);
        if(res == EOF){
            break;
        }


        if(strcmp(lineHeader, "v") == 0){
            cout<<"Vertex ";
            fscanf(importedFile, "%lf %lf %lf\n", &x, &y, &z);
            cout<<x<<" "<<y<<" "<<z<<endl;
            Point3D* point = new Point3D(x, y, z);
            vertices.push_back(point);

        } else if(strcmp(lineHeader, "l") == 0) {

            int v1, v2;
            fscanf(importedFile, "%d %d\n", &v1, &v2);
            vector<Point3D> points;
            points.push_back(*vertices.at(v1-1));
            points.push_back(*vertices.at(v2-1));
            Edge* edge = new Edge(&points);
            edges.push_back(edge);
            verticesIndexes.push_back(v1);
            verticesIndexes.push_back(v2);

        } else if(strcmp(lineHeader, "f") == 0){

            char line[256];
            int v1, v2, v3;
            fgets(line, sizeof line, importedFile);
            cout<< line;
            string strLine(line);
            size_t found = strLine.find("/");

            if(found == string::npos){
               found = strLine.find(" ", 1);
               string v1String = strLine.substr(1, found);
               v1 = atoi(v1String.c_str());
               strLine = strLine.substr(found+1, strLine.length());
               found = strLine.find(" ");
               string v2String = strLine.substr(0, found);
               v2 = atoi(v2String.c_str());
               strLine = strLine.substr(found+1, strLine.length());
               found = strLine.find(" ");
               string v3String = strLine.substr(0, found);
               v3 = atoi(v3String.c_str());

            } else {
               string v1String = strLine.substr(1, found);
               v1 = atoi(v1String.c_str());
               found = strLine.find(" ", 1);
               strLine = strLine.substr(found+1, strLine.length());
               found = strLine.find("/");
               string v2String = strLine.substr(0, found);
               v2 = atoi(v2String.c_str());
               found = strLine.find(" ", 1);
               strLine = strLine.substr(found+1, strLine.length());
               found = strLine.find("/");
               string v3String = strLine.substr(0, found);
               v3 = atoi(v3String.c_str());

            }

            vector<Point3D> points;
            points.push_back(*vertices.at(v1-1));
            points.push_back(*vertices.at(v2-1));
            points.push_back(*vertices.at(v3-1));
            Face* face = new Face(&points);
            faces.push_back(face);
            verticesIndexes.push_back(v1);
            verticesIndexes.push_back(v2);
            verticesIndexes.push_back(v3);

        } else if(strcmp(lineHeader, "o") == 0){

            object:
                fscanf(importedFile, "%[^\n]\n", lineHeader);
                vector<Point3D*> objectVertices;
                vector<int> objectVerticesIndexes;
                bool isInsideObject = true;
                while(isInsideObject){
                    res = fscanf(importedFile, "%s[ ]", lineHeader);
                    if(res == EOF){
                        working = false;
                        isInsideObject = false;
                    }

                    if(strcmp(lineHeader, "o") == 0){
                        goto addObject;
                    } else if(strcmp(lineHeader, "v") == 0){
                        fscanf(importedFile, "%lf %lf %lf\n", &x, &y, &z);
                        Point3D* point = new Point3D(x, y, z);

                        if(objectVertices.size() == 4) {
                            cerr<<"Error during adding importing object"<<endl;
                            return;
                        }

                        objectVertices.push_back(point);

                    } else if (strcmp(lineHeader, "f") == 0){


                        char line[256];
                        int v1, v2, v3;
                        fgets(line, sizeof line, importedFile);
                        cout<< line;
                        string strLine(line);
                        size_t found = strLine.find("/");

                        if(found == string::npos){
                           found = strLine.find(" ", 1);
                           string v1String = strLine.substr(1, found);
                           v1 = atoi(v1String.c_str());
                           strLine = strLine.substr(found+1, strLine.length());
                           found = strLine.find(" ");
                           string v2String = strLine.substr(0, found);
                           v2 = atoi(v2String.c_str());
                           strLine = strLine.substr(found+1, strLine.length());
                           found = strLine.find(" ");
                           string v3String = strLine.substr(0, found);
                           v3 = atoi(v3String.c_str());

                        } else {
                           string v1String = strLine.substr(1, found);
                           v1 = atoi(v1String.c_str());
                           found = strLine.find(" ", 1);
                           strLine = strLine.substr(found+1, strLine.length());
                           found = strLine.find("/");
                           string v2String = strLine.substr(0, found);
                           v2 = atoi(v2String.c_str());
                           found = strLine.find(" ", 1);
                           strLine = strLine.substr(found+1, strLine.length());
                           found = strLine.find("/");
                           string v3String = strLine.substr(0, found);
                           v3 = atoi(v3String.c_str());

                        }

                        if(std::find(objectVerticesIndexes.begin(), objectVerticesIndexes.end(), v1) == objectVerticesIndexes.end()){
                            objectVerticesIndexes.push_back(v1);
                        }

                        if(std::find(objectVerticesIndexes.begin(), objectVerticesIndexes.end(), v2) == objectVerticesIndexes.end()){
                            objectVerticesIndexes.push_back(v2);
                        }

                        if(std::find(objectVerticesIndexes.begin(), objectVerticesIndexes.end(), v3) == objectVerticesIndexes.end()) {
                            objectVerticesIndexes.push_back(v3);

                        }
                    } else {
                        continue;
                    }
                }

            addObject:
            //dodawanie do listy bloków
            vector<Point3D> points;

            if(objectVertices.size() == 0){
                for(int i=0; i<4; i++){
                    points.push_back(*vertices.at(objectVerticesIndexes.at(i)-1));
                    Point3D* vertex = vertices.at(objectVerticesIndexes.at(i)-1);
                    verticesIndexes.push_back(objectVerticesIndexes.at(i)-1);
                }
            } else {

                points.push_back(*objectVertices.at(0));
                points.push_back(*objectVertices.at(1));
                points.push_back(*objectVertices.at(2));
                points.push_back(*objectVertices.at(3));
            }

            Block* block = new Block(&points);
            blocks.push_back(block);

            if(isInsideObject){
                goto object;
            }

        } else {
            continue;
        }
    }

    int res = fclose(importedFile);
    if(res == EOF){
        cerr<<"Error during closing imported file"<<endl;
        return;
    }

    addToStructuresTree(handler);

}



void OBJImporter::addToStructuresTree(AbstractDataTree* handler){
    for(int i=0; i<vertices.size(); i++){
        if(std::find(verticesIndexes.begin(), verticesIndexes.end(), i) == verticesIndexes.end()){
            Vertex* vertex = new Vertex(*vertices.at(i));
            handler->add(0, vertex);
            cout<<"wchodze tu bez potrzeby znow"<<endl;
        }
    }

    for(Edge* edge : edges){
        handler->add(0, edge);
    }

    for(Face* face : faces){
        handler->add(0, face);
    }


    for(Block* block : blocks){
        handler->add(0, block);
    }

    vertices.clear();
    edges.clear();
    faces.clear();
    blocks.clear();

}

