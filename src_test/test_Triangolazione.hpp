#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"
#include <numeric>

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestTriangolazione, test_Triangolazione)
{
    // in una triangolazione del tetraedro, p=q=3, con b=2, mi aspetto di ottenere
	// nella Cell0DsCoordinates della mesh:
	// - i vertici originali (sono 4)
	// - i punti medi dei lati (sono 6, come i lati)
	// confronterò dunque quello che mi aspetto, con la mesh, post triangolazione
	
	// vertici originali (sono 4)
	Vector3d v0_expected = {1.0/sqrt(3), 1.0/sqrt(3), 1.0/sqrt(3)};
	Vector3d v1_expected = {-1.0/sqrt(3), -1.0/sqrt(3), 1.0/sqrt(3)};
	Vector3d v2_expected = {-1.0/sqrt(3), 1.0/sqrt(3), -1.0/sqrt(3)};
	Vector3d v3_expected = {1.0/sqrt(3), -1.0/sqrt(3), -1.0/sqrt(3)};
	
	// punti medi dei lati (sono 6, come i lati)
	Vector3d v4_expected = {0.0, 0.0, 1.0/sqrt(3)}; // ad es. questo è il punto medio tra v0 e v1
	Vector3d v5_expected = {0.0, 1.0/sqrt(3), 0.0};
	Vector3d v6_expected = {-1.0/sqrt(3), 0.0, 0.0};
	Vector3d v7_expected = {0.0, -1.0/sqrt(3), 0.0};
	Vector3d v8_expected = {0.0, 0.0, -1.0/sqrt(3)};
	Vector3d v9_expected = {1.0/sqrt(3), 0.0, 0.0};
	
	MatrixXd mat(3, 10);

    mat.col(0) = v0_expected;
    mat.col(1) = v1_expected;
    mat.col(2) = v2_expected;
	mat.col(3) = v3_expected;
	mat.col(4) = v4_expected;
	mat.col(5) = v5_expected;
	mat.col(6) = v6_expected;
	mat.col(7) = v7_expected;
	mat.col(8) = v8_expected;
	mat.col(9) = v9_expected;
	
	// creo la mesh e lancio la triangolazione
	PolygonalMesh mesh;
	unsigned int p = 3;
	unsigned int q = 3;
	unsigned int b = 2;
	unsigned int c = 0;
	
	ASSERT_TRUE(valorizza_poliedro(q, mesh));
	ASSERT_TRUE(Triangolazione(mesh, b, c, q));
	
	unsigned int count = 0;
	for (unsigned int i=0;i<mesh.NumCell0Ds;i++){
		for (unsigned int j=0;j<mesh.NumCell0Ds;j++){
			if ((mesh.Cell0DsCoordinates.col(i)-mat.col(j)).norm()<1e-10){
				count++;
			}
		}
	}
	ASSERT_EQ(count, 10);
	
	ASSERT_EQ(mesh.Cell0DsCoordinates.cols(),10);
	ASSERT_EQ(mesh.Cell0DsId.size(),10);
	ASSERT_EQ(mesh.Cell3DsVertices.size(),10);
	
	for (unsigned int i=0;i<10;i++){
		ASSERT_EQ(mesh.Cell0DsId[i],i);
		ASSERT_EQ(mesh.Cell3DsVertices[i],i);
	}
	ASSERT_EQ(mesh.NumCell0Ds,10);
	
	ASSERT_EQ(mesh.Cell3DsNumVert,10);
		
}

}
