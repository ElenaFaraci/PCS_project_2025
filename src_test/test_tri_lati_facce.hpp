#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"
#include <numeric>

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestTriangolazione, test_tri_lati_facce)
{
    // dati i vertici delle facce, la funzione in questione carica sulla mesh:
	// - i lati (Cell1DsExtrema)
	// - i lati che compongono le facce (Cell2DsEdges)
	PolygonalMesh mesh;
	
	unsigned int q = 3;
	unsigned int b = 2;
	unsigned int c = 0;
	
	
	ASSERT_TRUE(valorizza_poliedro(3, mesh));
	
	//////////////////////////////////////////////////////////////////////////////////////
	// Copia funzione triangolazione
	unsigned int T = b*b+b*c+c*c;
	unsigned int V = 0;
	if (q==3){
		V=2*T+2;
	} else if (q==4){
		V=4*T+2;
	} else if (q==5){
		V=10*T+2;
	}
	
	if (b==0){
		b=c;
	}
	
	unsigned int k = mesh.NumCell0Ds;	
	unsigned int num_facc_pre =mesh.NumCell2Ds;
	
	//creo un vettore punti_faccia che contenga i vertici, nuovi e vecchi, di ciascuna faccia
	unsigned int num_nuovi_per_faccia=((b+1)*(b+2))/2;
	unsigned int n=num_nuovi_per_faccia*num_facc_pre;
	vector<int> punti_faccia;
	punti_faccia.reserve(n);
	
	// resize della matrice che ospiterà anche i nuovi vertici
	mesh.Cell0DsCoordinates.conservativeResize(3, V);
	
	// iterazione sulle facce
	for(unsigned int j = 0; j < mesh.NumCell2Ds; j ++){
		
		unsigned int x0 = mesh.Cell2DsVertices[j][0];
		unsigned int y0 = mesh.Cell2DsVertices[j][1];
		unsigned int z0 = mesh.Cell2DsVertices[j][2];
		
		//cout << "i vertici della faccia: "<<j<<" sono: "<<x0<<" "<<y0<<" "<<z0<<" "<<endl;
		
		unsigned int x = x0;
		unsigned int y = y0;
		unsigned int z = z0;
		
		// per ogni faccia srotolo i punti su punti_faccia a partire dal primo vertice
		punti_faccia.push_back(x0);  
		
		unsigned int num_suddivisioni = b;
		
		//iterazione sui piani
		for(unsigned int w = 0; w < b-1; w++){
			
			//per ogni piano creo i vertici
			for(unsigned int i = 0; i < num_suddivisioni -1; i++) {
				
				//se un punto che sto creando, esiste già, allora aggiungerò il suo 
				//id al vettore punti_faccia e nulla alla matrice Cell0DsCoordinates
				//se invece il vertice è nuovo, gli assegno l'id successivo all'ultimo creato
				//e poi lo aggiungo a Cell0DsCoordinates (coordinate) e punti_faccia (id)
				
				Eigen::Vector3d nuovo_vertice = Nuovo_Vertice(x, y, num_suddivisioni, i + 1, mesh);
				int id=Esiste_gia(mesh, nuovo_vertice, k);
				if (id==-1){
					mesh.Cell0DsCoordinates.col(k) = nuovo_vertice;
					mesh.Cell0DsId.push_back(k);
					punti_faccia.push_back(k);
					k ++;
				}else{
					punti_faccia.push_back(Esiste_gia(mesh, nuovo_vertice, k));
				}
								
			}
			num_suddivisioni --;
			
			//aggiungo al vettore la fine del piano appena concluso
			punti_faccia.push_back(y);
			
			//creo inizio e fine del piano successivo
			Eigen::Vector3d nuovo_vertice= Nuovo_Vertice(x0, z0, b, w + 1, mesh);
			
			int id = Esiste_gia(mesh, nuovo_vertice, k);
			//se il nuovo vertice non esiste, lo aggiungo, altrimenti uso quello già fatto
			if (id==-1){
					mesh.Cell0DsCoordinates.col(k) = nuovo_vertice;
					mesh.Cell0DsId.push_back(k);
					x=k;
					punti_faccia.push_back(k);
					k ++;
			} else{
				x=id;
				punti_faccia.push_back(id);
			}
			
			// il vertice che aggiungo quì sotto, non va messo nel punti_faccia ora
			// perchè si trova alla fine del suo piano
			nuovo_vertice = Nuovo_Vertice(y0, z0, b, w + 1, mesh);
			id=Esiste_gia(mesh, nuovo_vertice, k);
			if (id==-1){
					mesh.Cell0DsCoordinates.col(k) = nuovo_vertice;
					mesh.Cell0DsId.push_back(k);
					y=k;
					k ++;
			} else{
				y=id;
			}
		}
		
	//ho finito la faccia e sono pronto ad iniziare la successiva, ma macano
	// da aggiungere a punti_faccia l'ultimo punto dell'ultimo strato e il vertice finale (sommità del triangolo)
	punti_faccia.push_back(y);
	punti_faccia.push_back(z0);	
	
	}
	
	// posso aggiornare ora mesh.NumCell0Ds
	mesh.NumCell0Ds=k;
	mesh.Cell3DsNumVert=k;
	mesh.Cell3DsVertices.resize(k);
	iota(mesh.Cell3DsVertices.begin(), mesh.Cell3DsVertices.end(), 0);
	
	tri_vertici_facce(mesh, b, punti_faccia, num_facc_pre, num_nuovi_per_faccia);
	
	//////////////////////////////////////////////////////////////////////////////////////////
	// mi fermo qui con la copia della funzione
	
	tri_lati_facce(mesh, b, num_facc_pre);
	
	// test: il numero di facce è coerente
	ASSERT_EQ(mesh.Cell2DsEdges.size(), mesh.Cell2DsVertices.size() );
	
	// test: ogni faccia deve avere 3 lati
    for (unsigned int i=0;i<mesh.Cell2DsEdges.size();i++) {
        ASSERT_EQ(mesh.Cell2DsEdges[i].size(), 3);
    }
	
	// test: usando la formula "num_lati=num_facc_pre*3*b*(b+1)/2 -b*mesh.NumCell1Ds"
	unsigned int num_lati = 24;
	ASSERT_EQ(mesh.Cell1DsId.size(), num_lati);
	ASSERT_EQ(mesh.Cell3DsEdges.size(), num_lati);
	
	
	// test: gli id lati sono consecutivi
    for (unsigned int i=0;i<num_lati;i++) {
        ASSERT_EQ(mesh.Cell1DsId[i], i);
    }
	
	
	// test: mi aspetto che per ogni faccia i lati facciano riferimento ai vertici opportuni
	for (unsigned int i=0;i<mesh.Cell2DsVertices.size();i++){
		vector<unsigned int> vertici = mesh.Cell2DsVertices[i];
        vector<unsigned int> edges = mesh.Cell2DsEdges[i];
        ASSERT_EQ(vertici.size(), 3);
		for (unsigned int j=0;j<mesh.Cell2DsVertices[i].size();j++){
			unsigned int id_lato = edges[j];
			unsigned int a = mesh.Cell1DsExtrema(0, id_lato);
            unsigned int b = mesh.Cell1DsExtrema(1, id_lato);
			bool a_in = (a == vertici[0] || a == vertici[1] || a == vertici[2]);
            bool b_in = (b == vertici[0] || b == vertici[1] || b == vertici[2]);
            ASSERT_TRUE(a_in && b_in);
		}
	}
	
	
	
}

}
