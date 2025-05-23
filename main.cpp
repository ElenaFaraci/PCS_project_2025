#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
//#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


int main(){
	
	PolygonalMesh mesh;
	int q=3;
	bool a= valorizza_poliedro(q, mesh);
	
	if (!a){
		cout<<"errore valorizzazione"<<endl;
	}
	
	bool b=controllo_lati_vertici (mesh);
	
	if (!b){
		cout<<"fallisce controllo"<<endl;
	}
	//////////////////////////////////////////////////////////
	// stampe prova triangolazione
	//mesh.Cell2DsVertices[0][0]
	/*
	Eigen::VectorXd col = mesh.Cell0DsCoordinates.col(2); // È un VectorXd con 3 elementi

    // verifico che la colonna abbia esattamente 3 righe
    if (col.size() != 3) {
        std::cerr << "Errore: la colonna non ha 3 elementi.\n";
        return 1;
    }

    std::array<double, 3> arr;
    for (int i = 0; i < 3; ++i) {
        arr[i] = col(i);
    }
	
		
	cout<<ArrayToString(3,&arr[0])<<endl;
	
	Eigen::VectorXd aaa=crea_vertice(1, 2, 1, 1, 3, mesh);
	*/
	return 0;
}