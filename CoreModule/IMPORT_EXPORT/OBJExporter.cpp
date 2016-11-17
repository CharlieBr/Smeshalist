#include "OBJExporter.h"

OBJExporter::OBJExporter()
{
    //ctor
}


void OBJExporter::exportToOBJ(Data* dataTree){

    exportedFile.open ("exported.obj");
    treeIteration(dataTree);
    exportedFile.close();

}


void OBJExporter::writeVerticesToFile(Element* element) {
    if(!element -> is_drawable()){
        return;
    }
    
    vector<Point3D> *vertices = element -> get_vertices();

    for(Point3D point : *vertices){
        exportedFile << "v " << point.get_x() << " " << point.get_y() << " " << point.get_z() << endl;
        counter++;
    }


}



void OBJExporter::writeEdgeToFile(int number){
    int startVertice = (elementPosition.find("edge")->second) * number;
    exportedFile << "l " << startVertice << " " << (startVertice + 1)  << endl;
}


void OBJExporter::writeFaceToFile(int number){
    int startVertice = (elementPosition.find("face")->second) * number;
    exportedFile << "f " << startVertice << " " << (startVertice + 1) << " " << (startVertice + 2) << endl;
}

void OBJExporter::writeBlockToFile(int number){

}


void OBJExporter::treeIteration(Data* dataTree) {
    vector<string> types = {"vertex", "edge", "face", "block"};
    vector<int>* groupIDs = dataTree -> get_all_groupIDs();
    

    for(string structureType : types){
        elementPosition.insert(std::pair<string, int>(structureType, counter));
        currentTypeCounter = 0;
        for (int groupID : *groupIDs) {
            ElementsGroup* elementsGroup = dataTree -> get_group(groupID);

            //ommit groups which are not draw
            if (!elementsGroup -> is_drawable()) {
                continue;
            }

            
            ElementsList* elementsList = elementsGroup -> get_list(structureType);
            if(elementList == NULL){
                continue;
            }

            //ommit lists which are not draw
            if (!elementsList -> is_drawable()) {
                continue;
            }

            vector<Element*>* elements = elementsList -> get_elements();

            for(Element* element : *elements) {
                writeVerticesToFile(element);
            }
            
            if(structureType == "edge"){
                for(Element* element : *elements){
                    if(!element -> is_drawable()){
                        continue;
                    }

                    currentTypeCounter++;
                    writeEdgeToFile(currentTypeCounter);
                }
            } else if (structureType == "face"){
                for(Element* element : *elements){
                    if(!element -> is_drawable()){
                        continue;
                    }

                    currentTypeCounter++;
                    writeFaceToFile(currentTypeCounter);
                }

            } else if (structureType == "block"){
                for(Element* element : *elements){
                    if(!element->is_drawable()){
                        continue;
                    } 

                    currentTypeCounter++;
                    writeBlockToFile(currentTypeCounter);
                }
            }
        }

    }

}
