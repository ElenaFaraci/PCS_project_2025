#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestPolygons, test_Esiste_gia)
{
    PolygonalMesh mesh;
	mesh.NumCell0Ds=6;
	mesh.Cell0DsId = {0,1,2,3,4,5}; 
	mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
	mesh.Cell0DsCoordinates.col(0) << 0.0, 0.0, 1.0;
	mesh.Cell0DsCoordinates.col(1) << 0.0, -1.0, 0.0;
	mesh.Cell0DsCoordinates.col(2) << 1.0, 0.0, 0.0;
	mesh.Cell0DsCoordinates.col(3) << 0.0, 1.0, 0.0;
	mesh.Cell0DsCoordinates.col(4) << -1.0, 0.0, 0.0;
	mesh.Cell0DsCoordinates.col(5) << 0.0, 0.0, -1.0;
	
	// test con vertice esistente
	Eigen::Vector3d nuovo_vertice;
	nuovo_vertice << 0.0, -1.0, 0.0;

	int funzione_vert_esiste=Esiste_gia(mesh, nuovo_vertice, 6);
	int corretto_vert_esiste=1;
	
	// test con vertice nuovo
	Eigen::Vector3d nuovo_vertice_2;
	nuovo_vertice_2 << 5.0, -1.0, 0.0;
	
	int funzione_vert_non_esiste=Esiste_gia(mesh, nuovo_vertice_2, 6);
	int corretto_vert_non_esiste=-1;
	
	EXPECT_EQ(funzione_vert_esiste, corretto_vert_esiste);
	EXPECT_EQ(funzione_vert_non_esiste, corretto_vert_non_esiste);
	
	
	
}

}
