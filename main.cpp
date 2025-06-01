#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


int main(){
	
	PolygonalMesh mesh;
	int p=3; // per ora non consideriamo altri casi se non 3
	int q=4;
	int b=1; //e se b=0 o 1...vedere
	int c=0;
	
	
	if (!valorizza_poliedro(q, mesh)){
		cout<<"errore valorizzazione"<<endl;
	}
	
	
	if (!controllo_lati_vertici (mesh)){
		cout<<"fallisce controllo"<<endl;
	}	
		
	// dobbiamo controllare l'input, positività, interi ecc...
	
	if ((b+c)!=0 and (b==0 or c==0)){
		if ((b+c)==1){
			cout<<"non c'è bisogno di fare triangolazione, gli indici sono b = "<<b<<" c = "<<c<<endl;
		} else{
			bool f= Triangolazione(mesh, b, c, q);
		}
	} else{
		cout<<"indici di triangolazione non validi per ora..."<<endl;
	}
	
	if (!controllo_lati_vertici (mesh)){
		cout<<"fallisce controllo post triangolazione"<<endl;
	}
	
	info_mesh(mesh);
	

	Gedim::UCDUtilities utilities;
    {   
        utilities.ExportPoints("./Cell0Ds.inp",
                               mesh.Cell0DsCoordinates);
    }

    {
        utilities.ExportSegments("./Cell1Ds.inp",
                                 mesh.Cell0DsCoordinates,
                                 mesh.Cell1DsExtrema,
                                 {});
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