#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestDuale, test_CostruisciDualeMesh)
{
    
	
	// Approccio: costruisco il duale aspettato dell'ottaedro e verifico che sia 
	// ciò che mi aspetto
	
	PolygonalMesh mesh;
	PolygonalMesh duale;
	PolygonalMesh duale_exp;
			
	//Cell0Ds
	duale_exp.NumCell0Ds=8;
	duale_exp.Cell0DsId = {0,1,2,3,4,5,6,7}; 
	duale_exp.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, duale_exp.NumCell0Ds);
		
	duale_exp.Cell0DsCoordinates.col(0) << 1.0/3.0, -1.0/3.0, 1.0/3.0;
	duale_exp.Cell0DsCoordinates.col(1) << 1.0/3.0, 1.0/3.0, 1.0/3.0;
	duale_exp.Cell0DsCoordinates.col(2) << -1.0/3.0, 1.0/3.0, 1.0/3.0;
	duale_exp.Cell0DsCoordinates.col(3) << -1.0/3.0, -1.0/3.0, 1.0/3.0;
	duale_exp.Cell0DsCoordinates.col(4) << 1.0/3.0, -1.0/3.0, -1.0/3.0;
	duale_exp.Cell0DsCoordinates.col(5) << 1.0/3.0, 1.0/3.0, -1.0/3.0;
	duale_exp.Cell0DsCoordinates.col(6) << -1.0/3.0, 1.0/3.0, -1.0/3.0;
	duale_exp.Cell0DsCoordinates.col(7) << -1.0/3.0, -1.0/3.0, -1.0/3.0;
	
	//Cell1Ds
	duale_exp.NumCell1Ds=12;
	duale_exp.Cell1DsId = {0,1,2,3,4,5,6,7,8,9,10,11};
		
	duale_exp.Cell1DsExtrema = Eigen::MatrixXi(2, duale_exp.NumCell1Ds);
	duale_exp.Cell1DsExtrema.col(0) << 0, 1 ;
	duale_exp.Cell1DsExtrema.col(1) << 0, 3 ;
	duale_exp.Cell1DsExtrema.col(2) << 0, 4 ;
	duale_exp.Cell1DsExtrema.col(3) << 1, 2 ;
	duale_exp.Cell1DsExtrema.col(4) << 1, 5 ;
	duale_exp.Cell1DsExtrema.col(5) << 2, 3 ;
	duale_exp.Cell1DsExtrema.col(6) << 2, 6 ;
	duale_exp.Cell1DsExtrema.col(7) << 3, 7 ;
	duale_exp.Cell1DsExtrema.col(8) << 4, 5 ;
	duale_exp.Cell1DsExtrema.col(9) << 4, 7 ;
	duale_exp.Cell1DsExtrema.col(10) << 5, 6 ;
	duale_exp.Cell1DsExtrema.col(11) << 6, 7 ;
		
		
	//Cell2Ds
	duale_exp.NumCell2Ds = 6;
	duale_exp.Cell2DsId = {0, 1 ,2, 3, 4, 5};
	duale_exp.Cell2DsNumVert = {4,4,4,4,4,4};
	duale_exp.Cell2DsNumEdg = {4,4,4,4,4,4};
		
		
	duale_exp.Cell2DsVertices.reserve(duale_exp.NumCell2Ds); 
		
	vector<unsigned int> v0 = {0,1,2,3};
	vector<unsigned int> v1 = {0,3,7,4};
	vector<unsigned int> v2 = {0,1,5,4};
	vector<unsigned int> v3 = {1,2,6,5};
	vector<unsigned int> v4 = {2,3,7,6};
	vector<unsigned int> v5 = {4,5,6,7};
		
	duale_exp.Cell2DsVertices= {v0, v1, v2, v3, v4, v5};
		
	duale_exp.Cell2DsEdges.reserve(duale_exp.NumCell2Ds);
		
	vector<unsigned int> e0 = {0,3,5,1};
	vector<unsigned int> e1 = {1,7,9,2};
	vector<unsigned int> e2 = {0,4,8,2};
	vector<unsigned int> e3 = {3,6,10,4};
	vector<unsigned int> e4 = {5,7,11,6};
	vector<unsigned int> e5 = {8,10,11,9};
		
	duale_exp.Cell2DsEdges = {e0, e1, e2, e3, e4, e5};
		
	//Cell3Ds
	duale_exp.Cell3DsId=0; 
		
	duale_exp.Cell3DsNumVert = duale_exp.NumCell0Ds;
	duale_exp.Cell3DsNumEdg = duale_exp.NumCell1Ds;
	duale_exp.Cell3DsNumFaces = duale_exp.NumCell2Ds;
		
	duale_exp.Cell3DsVertices = duale_exp.Cell0DsId; 
	duale_exp.Cell3DsEdges = duale_exp.Cell1DsId;
	duale_exp.Cell3DsFaces = duale_exp.Cell2DsId;
		
	// costruisco il duale con la funzione
	if (valorizza_poliedro(4, mesh)){
		duale = CostruisciDualeMesh(mesh);
		}
	
	//Cell0Ds
	ASSERT_EQ(duale.NumCell0Ds,duale_exp.NumCell0Ds);
	ASSERT_EQ(duale.Cell0DsId,duale_exp.Cell0DsId);
	
	for (unsigned int j=0;j<duale.NumCell0Ds;j++){
			ASSERT_TRUE((duale.Cell0DsCoordinates.col(j)-duale_exp.Cell0DsCoordinates.col(j)).norm()<1e-10);
		}
	
	//Cell1Ds
	ASSERT_EQ(duale.NumCell1Ds,duale_exp.NumCell1Ds);
	ASSERT_EQ(duale.Cell1DsId,duale_exp.Cell1DsId);
	
	for (unsigned int j=0;j<duale.NumCell1Ds;j++){
			ASSERT_EQ(duale.Cell1DsExtrema(1,j),duale_exp.Cell1DsExtrema(1,j));
			ASSERT_EQ(duale.Cell1DsExtrema(0,j),duale_exp.Cell1DsExtrema(0,j));
		}
	
	//Cell2Ds
	ASSERT_EQ(duale.NumCell2Ds,duale_exp.NumCell2Ds);
	ASSERT_EQ(duale.Cell2DsId,duale_exp.Cell2DsId);
	ASSERT_EQ(duale.Cell2DsNumVert,duale_exp.Cell2DsNumVert);
	ASSERT_EQ(duale.Cell2DsNumEdg,duale_exp.Cell2DsNumEdg);
	
	for (unsigned int j=0;j<duale.NumCell2Ds;j++){
			ASSERT_EQ(duale.Cell2DsVertices[j],duale_exp.Cell2DsVertices[j]);
			ASSERT_EQ(duale.Cell2DsEdges[j],duale_exp.Cell2DsEdges[j]);
		}
	
	// Cell3Ds è determinato dalle precedenti
	
	
	
}

}
