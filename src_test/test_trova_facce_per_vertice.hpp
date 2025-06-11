#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestDuale, test_trova_facce_per_vertice)
{
    PolygonalMesh mesh;
	
	// Cell0Ds
	mesh.NumCell0Ds=4;
	mesh.Cell0DsId = {0,1,2,3};
	mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
	mesh.Cell0DsCoordinates.col(0) << 1.0/sqrt(3), 1.0/sqrt(3), 1.0/sqrt(3);
	mesh.Cell0DsCoordinates.col(1) << -1.0/sqrt(3), -1.0/sqrt(3), 1.0/sqrt(3);
	mesh.Cell0DsCoordinates.col(2) << -1.0/sqrt(3), 1.0/sqrt(3), -1.0/sqrt(3);
	mesh.Cell0DsCoordinates.col(3) << 1.0/sqrt(3), -1.0/sqrt(3), -1.0/sqrt(3);
		
	//Cell2Ds
	mesh.NumCell2Ds = 4;
	mesh.Cell2DsId = {0, 1 ,2, 3};
	mesh.Cell2DsNumVert = {3, 3, 3, 3};
	mesh.Cell2DsNumEdg = {3, 3, 3, 3};
		
	mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
		
	vector<unsigned int> v1 = {0,1,2};
	vector<unsigned int> v2 = {1,2,3};
	vector<unsigned int> v3 = {0,2,3};
	vector<unsigned int> v4 = {0,1,3};
		
	mesh.Cell2DsVertices= {v1, v2, v3, v4};
	/// inizio test 
	vector<vector<unsigned int>> facce= trova_facce_per_vertice(mesh);
	
	vector<unsigned int> expected_0 ={0, 2, 3};
	vector<unsigned int> expected_1 ={0, 1, 3};
	vector<unsigned int> expected_2 ={0, 1, 2};
	vector<unsigned int> expected_3 ={1, 2, 3};
	
	EXPECT_EQ(facce[0], expected_0);
	EXPECT_EQ(facce[1], expected_1);
	EXPECT_EQ(facce[2], expected_2);
	EXPECT_EQ(facce[3], expected_3);

	
	
}

}
