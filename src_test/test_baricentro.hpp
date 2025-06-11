#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestDuale, test_baricentro)
{
    PolygonalMesh mesh;

	mesh.NumCell0Ds=3;
	mesh.Cell0DsId = {0,1,2}; 
	mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
			
	mesh.Cell0DsCoordinates.col(0) << 1.0, 0.0, 0.0;
	mesh.Cell0DsCoordinates.col(1) << 0.0, 1.0, 0.0;
	mesh.Cell0DsCoordinates.col(2) << 0.0, 0.0, 1.0;
	
	vector<unsigned int> vertici={0,1,2};
	Eigen::Vector3d baricentro_funzione = baricentro(vertici, mesh);
	Eigen::Vector3d baricentro_esatto= {1.0/3.0, 1.0/3.0, 1.0/3.0};
	double tol =1e-10;
	EXPECT_TRUE((baricentro_funzione-baricentro_esatto).norm()<tol);
}

}
