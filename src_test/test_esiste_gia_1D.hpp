#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestPolygons, test_esiste_gia_1D)
{
    PolygonalMesh mesh;
	mesh.NumCell1Ds=12;
	mesh.Cell1DsId = {0,1,2,3,4,5,6,7,8,9,10,11}; // è efficiente? reserve? Vanno ordinati?
		
	mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
	mesh.Cell1DsExtrema.col(0) << 0, 1;
	mesh.Cell1DsExtrema.col(1) << 0, 2;
	mesh.Cell1DsExtrema.col(2) << 0, 3;
	mesh.Cell1DsExtrema.col(3) << 0, 4;
	mesh.Cell1DsExtrema.col(4) << 1, 2;
	mesh.Cell1DsExtrema.col(5) << 1, 4;
	mesh.Cell1DsExtrema.col(6) << 1, 5;
	mesh.Cell1DsExtrema.col(7) << 2, 3;
	mesh.Cell1DsExtrema.col(8) << 2, 5;
	mesh.Cell1DsExtrema.col(9) << 3, 4;
	mesh.Cell1DsExtrema.col(10) << 3, 5;
	mesh.Cell1DsExtrema.col(11) << 4, 5;
	
	int funzione_lato_esiste=esiste_gia_1D(3, 0, mesh);
	int corretto_lato_esiste=2;
	
	int funzione_lato_non_esiste=esiste_gia_1D(0, 5, mesh);
	int corretto_lato_non_esiste=-1;
	
	EXPECT_EQ(funzione_lato_esiste, corretto_lato_esiste);
	EXPECT_EQ(funzione_lato_non_esiste, corretto_lato_non_esiste);
	
	
}

}
