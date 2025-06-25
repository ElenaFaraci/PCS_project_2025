#include <iostream>
#include <sstream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;



int main(int argc, char *argv[]){
	
	
	/*
	 int p=3; 
	 int q=3;
	 int b=2; 
	 int c=0;
	unsigned int id1=0;
	unsigned int id2=2;
	*/
	unsigned int p; 
	unsigned int q;
	unsigned int b; 
	unsigned int c;
	unsigned int id1;
	unsigned int id2;
	
	bool flag_cammino = false;
	
	if (argc == 5){
		array<unsigned int*, 4> punt_var = { &p, &q, &b, &c };
		for (unsigned int i =0;i<punt_var.size();i++){
			if (!converti_uns_int(argv[i+1],*punt_var[i])){
				cerr<<"è stato inserito un valore non valido: "<<argv[i+1]<<endl;
				return 1;
			}
		}
		
	}else if (argc == 7){
		array<unsigned int*, 6> punt_var = { &p, &q, &b, &c, &id1, &id2 };
		for (unsigned int i =0;i<punt_var.size();i++){
			if (!converti_uns_int(argv[i+1],*punt_var[i])){
				cerr<<"è stato inserito un valore non valido: "<<argv[i+1]<<endl;
				return 1;
			}
		}
		
		flag_cammino = true;
	} else{
		cerr<<"Il numero di argomenti passati non è contemplato"<<endl;
		return 1;
	}
	cout << "Valori letti:"<<endl;
    cout << "p = " << p << ", q = " << q << ", b = " << b << ", c = " << c << endl;
	if (flag_cammino){
		cout<<"id1: "<<id1<<" id2: "<<id2<<endl;
	}
	
	PolygonalMesh mesh;
	PolygonalMesh duale;
	
	
	
	
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
		
		unsigned int tmp=p;
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
		bool f= triangolazione_2(mesh, b, q);
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
		if (flag_cammino){
			trova_cammino_minimo(duale, id1, id2);
		}
		
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
		if (flag_cammino){
			trova_cammino_minimo(mesh, id1, id2);
		}
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