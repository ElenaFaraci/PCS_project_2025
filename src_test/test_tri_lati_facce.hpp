#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestTriangolazione, test_tri_lati_facce)
{
    PolygonalMesh mesh;
	// Cell0Ds
	mesh.NumCell0Ds = 4;
    mesh.Cell0DsId = {0, 1, 2, 3};
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates.col(0) << 1.0 / sqrt(3), 1.0 / sqrt(3), 1.0 / sqrt(3);
    mesh.Cell0DsCoordinates.col(1) << -1.0 / sqrt(3), -1.0 / sqrt(3), 1.0 / sqrt(3);
    mesh.Cell0DsCoordinates.col(2) << -1.0 / sqrt(3), 1.0 / sqrt(3), -1.0 / sqrt(3);
    mesh.Cell0DsCoordinates.col(3) << 1.0 / sqrt(3), -1.0 / sqrt(3), -1.0 / sqrt(3);

    // Cell2Ds
    mesh.NumCell2Ds = 4;
    mesh.Cell2DsId = {0, 1, 2, 3};
    mesh.Cell2DsNumVert = {3, 3, 3, 3};
    mesh.Cell2DsNumEdg = {3, 3, 3, 3};

    vector<unsigned int> v1 = {0, 1, 2};
    vector<unsigned int> v2 = {1, 2, 3};
    vector<unsigned int> v3 = {0, 2, 3};
    vector<unsigned int> v4 = {0, 1, 3};

    mesh.Cell2DsVertices = {v1, v2, v3, v4};

    mesh.Cell3DsId=0; //caso tetraedro
	mesh.Cell3DsNumVert = mesh.NumCell0Ds;
	mesh.Cell3DsNumFaces = mesh.NumCell2Ds;
	mesh.Cell3DsVertices = mesh.Cell0DsId;
	mesh.Cell3DsFaces = mesh.Cell2DsId;
	
	tri_lati_facce(mesh, 1, 4);
	
	//info_mesh(mesh);

	
	
}

}

///////////////////////////////////////////////////////////////////
/*
void tri_lati_facce(PolygonalMesh& mesh, unsigned int b,unsigned int num_facc_pre){
	
	unsigned int num_lati=num_facc_pre*3*b*(b+1)/2 -b*mesh.NumCell1Ds; 
	
	mesh.Cell2DsEdges = {};
	mesh.Cell2DsEdges.reserve(mesh.Cell2DsVertices.size());
	
	mesh.Cell1DsId ={};
	mesh.Cell1DsId.reserve(num_lati);
	
	mesh.Cell1DsExtrema.resize(2, num_lati);
	unsigned int k=0;
	for (unsigned int j=0;j<mesh.Cell2DsVertices.size();j++){
		vector<unsigned int> v={};
		v.reserve(3);
		for (unsigned int i=0;i<3;i++){
			unsigned int point_1 = mesh.Cell2DsVertices[j][i];
			unsigned int point_2 = mesh.Cell2DsVertices[j][(i+1)%3];
			
			int id_l=esiste_gia_1D(point_1, point_2, mesh);
			if (id_l==-1){
				// il lato è nuovo
				Vector2i new_l(point_1,point_2);
				mesh.Cell1DsExtrema.col(k)=new_l;
				mesh.Cell1DsId.push_back(k);
				v.push_back(k);
				k++;
				// ma devo aggiungere anche gli id dei lati
			} else{
				// il lato esiste già 
				v.push_back(id_l);
			}
			
		}
		mesh.Cell2DsEdges.push_back(v);
	}
	
	mesh.NumCell1Ds=num_lati;
	mesh.Cell3DsNumEdg=num_lati;
	
	mesh.Cell3DsEdges.resize(num_lati);
	iota(mesh.Cell3DsEdges.begin(), mesh.Cell3DsEdges.end(), 0);
	
	
}
*/