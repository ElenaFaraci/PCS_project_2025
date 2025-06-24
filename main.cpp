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
	int p=4; 
	int q=3;
	int b=1; //e se b=0 o 1...vedere
	int c=0;
	unsigned int id1 = 0;
	unsigned int id2 = 2;
	
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
		info_mesh(duale);
		
		if (!controllo_lati_vertici (duale)){
		cerr<<"fallisce controllo su consecutività lati e vertici del DUALE"<<endl;
		return 1;
		}	
		proiezione_su_sfera_unitaria(duale);
		trova_cammino_minimo(duale, id1, id2);
		
		Gedim::UCDUtilities utilities;
    {   
        utilities.ExportPoints("./Cell0Ds_duale.inp",
                               duale.Cell0DsCoordinates);
    }

    {
        utilities.ExportSegments("./Cell1Ds_duale.inp",
                                 duale.Cell0DsCoordinates,
                                 duale.Cell1DsExtrema,
                                 {});
    }
	}
	else {
		proiezione_su_sfera_unitaria(mesh);
		trova_cammino_minimo(mesh, id1, id2);
	}
	
	
	
	
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}