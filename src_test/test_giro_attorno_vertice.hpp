#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestDuale, test_giro_attorno_vertice)
{
	// l'idea è di costruirmi una mesh ad hoc, scelgo di testare su un "esagono"
	// composto da 6 triangoli. (in generale la funzione può essere che non lavori sul 
	// piano, ma qui non è rilevante.)
	
	PolygonalMesh mesh;
	
	//Cell0Ds
	mesh.NumCell0Ds=7;
	mesh.Cell0DsId = {0,1,2,3,4,5,6}; // è efficiente? reserve?
	mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
	mesh.Cell0DsCoordinates.col(0) << 0.0, 0.0, 0.0;
	mesh.Cell0DsCoordinates.col(1) << 1.0, 0.0, 0.0;
	mesh.Cell0DsCoordinates.col(2) << 1.0, 1.0, 0.0;
	mesh.Cell0DsCoordinates.col(3) << 0.0, 1.0, 0.0;
	mesh.Cell0DsCoordinates.col(4) << -1.0, 0.0, 0.0;
	mesh.Cell0DsCoordinates.col(5) << -1.0, -1.0, 0.0;
	mesh.Cell0DsCoordinates.col(6) << 0.0, -1.0, 0.0;
	

	//Cell1Ds
	mesh.NumCell1Ds=12;
	mesh.Cell1DsId = {0,1,2,3,4,5,6,7,8,9,10,11}; 
		
	mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
	mesh.Cell1DsExtrema.col(0) << 1, 2 ;
	mesh.Cell1DsExtrema.col(1) << 2, 3 ;
	mesh.Cell1DsExtrema.col(2) << 3, 4 ;
	mesh.Cell1DsExtrema.col(3) << 4, 5 ;
	mesh.Cell1DsExtrema.col(4) << 5, 6 ;
	mesh.Cell1DsExtrema.col(5) << 6, 1 ;
	mesh.Cell1DsExtrema.col(6) << 0, 2 ;
	mesh.Cell1DsExtrema.col(7) << 0, 3 ;
	mesh.Cell1DsExtrema.col(8) << 0, 4 ;
	mesh.Cell1DsExtrema.col(9) << 0, 5 ;
	mesh.Cell1DsExtrema.col(10) << 0, 6 ;
	mesh.Cell1DsExtrema.col(11) << 0, 1 ;
	
	
	
	
	
		
	//Cell2Ds
	mesh.NumCell2Ds = 6;
	mesh.Cell2DsId = {0, 1 ,2, 3,4,5,6};
	mesh.Cell2DsNumVert = {3, 3, 3, 3,3,3};
	mesh.Cell2DsNumEdg = {3, 3, 3, 3,3,3};
		
		
	mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds); 
		
	vector<unsigned int> v0 = {0,1,2};
	vector<unsigned int> v1 = {0,2,3};
	vector<unsigned int> v2 = {0,3,4};
	vector<unsigned int> v3 = {0,4,5};
	vector<unsigned int> v4 = {0,5,6};
	vector<unsigned int> v5 = {0,6,1};
		
	mesh.Cell2DsVertices= {v0, v1, v2, v3, v4, v5};
		
	mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
	vector<unsigned int> e0 = {11,0,6};
	vector<unsigned int> e1 = {6,1,7};
	vector<unsigned int> e2 = {7,2,8};
	vector<unsigned int> e3 = {8,3,9};
	vector<unsigned int> e4 = {9,4,10};
	vector<unsigned int> e5 = {10,5,11};
		
	mesh.Cell2DsEdges = {e0, e1, e2, e3, e4, e5};
		
	//Cell3Ds
	mesh.Cell3DsId=0; //caso tetraedro
		
	mesh.Cell3DsNumVert = mesh.NumCell0Ds;
	mesh.Cell3DsNumEdg = mesh.NumCell1Ds;
	mesh.Cell3DsNumFaces = mesh.NumCell2Ds;
		
	mesh.Cell3DsVertices = mesh.Cell0DsId; //costruttore di copia? 
	mesh.Cell3DsEdges = mesh.Cell1DsId;
	mesh.Cell3DsFaces = mesh.Cell2DsId;
	/*
	if (!controllo_lati_vertici (mesh)){
		cout<<"fallisce controllo su consecutività lati e vertici"<<endl;
	}else{
		cout<<"ho costruito bene l'esagono"<<endl;
	}
	*/
	vector<unsigned int> ordinamento_funz = giro_attorno_vertice(mesh, 0, {4,2,5,1,3,0});
	// siccome la funzione ordina ciclicamente le facce partendo dalla prima mi posso aspettare:
	vector<unsigned int> expected_1 = {4,5,0,1,2,3};
	vector<unsigned int> expected_2 = {4,3,2,1,0,5};
	// ed una delle due deve essere il risultato
	//(in realtà so già che l'uguaglianza si ha con expected_1, perchè 
	// nel vettore passato alla funzione, la faccia adiacente alla 4 e ad essa piu
	// vicina è la 5)
	
	EXPECT_TRUE(ordinamento_funz==expected_1 || ordinamento_funz==expected_2);
}
}