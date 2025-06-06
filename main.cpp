#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


int main(){
	
	PolygonalMesh mesh;
	PolygonalMesh duale;
	int p=3; // per ora non consideriamo altri casi se non 3
	int q=5;
	int b=3; //e se b=0 o 1...vedere
	int c=0;
	unsigned int id1 = 0;
	unsigned int id2 = 0;
	
	// dobbiamo controllare l'input, positività, interi ecc...
	
	bool flag_duale=false;
	if (p==3){
		if (!valorizza_poliedro(q, mesh)){
			cerr<<"errore inserimento di q (secondo valore passato)"<<endl;
			return 1;
		}
	} else if (q==3){
		if (!valorizza_poliedro(p, mesh)){
			cerr<<"errore inserimento di p (primo valore passato)"<<endl;
			return 1;
		}
		int tmp=p;
		p=q;
		q=tmp;
		flag_duale=true;
		
	} else{
		cerr<<"ne p ne q (primi due valori passati) sono idonei"<< endl;
		return 1;
	}
	

	// info_mesh(mesh);
	

	// effettuiamo il controllo di consecutivià
	if (!controllo_lati_vertici (mesh)){
		cerr<<"fallisce controllo su consecutività lati e vertici"<<endl;
		return 1;
	}	
		
	
	// di seguito verifichiamo la correttezza degli indici di triangolazione, 
	// se sono corretti procediamo con la triangolazione
	if ((b+c)!=0 and (b==0 or c==0)){
		if ((b+c)==1){
			cout<<"non c'è bisogno di fare triangolazione, gli indici sono b = "<<b<<" c = "<<c<<endl;
		} else{
			bool f= Triangolazione(mesh, b, c, q);
		}
	} else{
		cout<<"indici di triangolazione non validi per ora..."<<endl;
	}
	
	
	// effettuiamo nuovamente il controllo di consecutivià
	if (!controllo_lati_vertici (mesh)){
		cerr<<"fallisce controllo su consecutività lati e vertici post triangolazione"<<endl;
		return 1;
	}	
	
	// nel caso in cui p!=3, ma q lecito, avevamo scambiato questi due indici 
	// al fine di poter triangolare, ma ora dobbiamo "tornare indietro" per mezzo
	// del duale
	
	info_mesh(mesh);
	
	if (flag_duale){
		cout<<"in questo caso dobbiamo passare al duale"<<endl;
		duale = CostruisciDualeMesh(mesh);
		
		
	}
	info_mesh(duale);
	
	
	//info_mesh(mesh);
	string nome0 = "Cell0Ds.txt";
	salvataggio_Cell0Ds(mesh, nome0);
	string nome1 = "Cell1Ds.txt";
	salvataggio_Cell1Ds(mesh, nome1);
	string nome2 = "Cell2Ds.txt";
	salvataggio_Cell2Ds(mesh, nome2);
	string nome3 = "Cell3Ds.txt";
	salvataggio_Cell3Ds(mesh, nome3);
	
	

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