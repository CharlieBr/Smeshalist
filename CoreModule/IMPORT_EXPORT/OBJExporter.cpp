#include "OBJExporter.h"

OBJExporter::OBJExporter()
{
    //ctor
}


void OBJExporter::exportToOBJ(Data* dataTree, string fileName){

    exportedFile.open (fileName);
    treeIteration(dataTree);
    exportedFile.close();

}


void OBJExporter::writeVerticesToFile(Element* element) {
    if(!element -> is_drawable()){
        return;
    }

    currentTypeCounter++;
    vector<Point3D> *vertices = element -> get_vertices();

    for(Point3D point : *vertices){
        exportedFile << "v " << point.get_x() << " " << point.get_y() << " " << point.get_z() << endl;
    }


}



void OBJExporter::writeEdgeToFile(){
    int numberOfEdges = elementPosition.find("edge")->second;
    int startVertice = (elementPosition.find("vertex")->second) + 1;
    for(int i=1; i<=numberOfEdges; i++){
        exportedFile << "l " << startVertice << " " << (startVertice + 1)  << endl;
        startVertice += 2;
    }
}


void OBJExporter::writeFaceToFile(){
    int numberOfFaces = elementPosition.find("face")->second;
    int startVertice = (elementPosition.find("vertex")->second)+2*(elementPosition.find("edge")->second)+1;
    for(int i=1; i<= numberOfFaces; i++){
        exportedFile << "f " << startVertice << " " << (startVertice + 1) << " " << (startVertice + 2) << endl;
        startVertice += 3;
    }

}

void OBJExporter::writeBlockToFile(){
    int numberOfBlocks = elementPosition.find("block")->second;
    int startVertice = (elementPosition.find("vertex")->second)+2*(elementPosition.find("edge")->second)+3*(elementPosition.find("face")->second) + 1;

    for(int i=1; i<= numberOfBlocks; i++){
        exportedFile<<"o block"<<i<<endl;
        exportedFile << "f " << startVertice << " " << (startVertice + 1) << " " << (startVertice + 2) << endl;
        exportedFile << "f " << startVertice << " " << (startVertice + 1) << " " << (startVertice + 3) << endl;
        exportedFile << "f " << startVertice << " " << (startVertice + 3) << " " << (startVertice + 2) << endl;
        exportedFile << "f " << (startVertice + 3)<< " " << (startVertice + 1) << " " << (startVertice + 2) << endl;

        startVertice += 4;
    }
}


void OBJExporter::treeIteration(Data* dataTree) {
    vector<string> types = {"vertex", "edge", "face", "block"};
    vector<int>* groupIDs = dataTree -> get_all_groupIDs();


    for(string structureType : types){

        currentTypeCounter = 0;
        for (int groupID : *groupIDs) {
            ElementsGroup* elementsGroup = dataTree -> get_group(groupID);

            //ommit groups which are not draw
            if (!elementsGroup -> is_drawable()) {
                continue;
            }


            ElementsList* elementsList = elementsGroup -> get_list(structureType);
            if(elementsList == NULL){
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
        }

        elementPosition.insert(std::pair<string, int>(structureType, currentTypeCounter));
    }

    writeEdgeToFile();
    writeFaceToFile();
    writeBlockToFile();

}


