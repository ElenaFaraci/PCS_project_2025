#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestFunzionalità, test_Nuovo_Vertice)
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
	
	
	// test per il punto medio tra due punti
	Vector3d p_funzione = Nuovo_Vertice(0, 1, 2, 1, mesh);
	
	Vector3d p_esatto;
	p_esatto << 0.0, 0.0, 1.0/sqrt(3);
	
	double tol =1e-10;
	EXPECT_TRUE((p_funzione-p_esatto).norm()<tol);
	
	// test caso interpolazione di un punto con se stesso
	Vector3d p_funzione_2 = Nuovo_Vertice(0, 0, 2, 1, mesh);
	
	Vector3d p_esatto_2;
	p_esatto_2 = mesh.Cell0DsCoordinates.col(0);
	
	
	EXPECT_TRUE((p_funzione_2-p_esatto_2).norm()<tol);

	// test interpolazione, lo step vale 0 quindi deve ridare il punto di partenza
	Vector3d p_funzione_3 = Nuovo_Vertice(0, 1, 2, 0, mesh);
	
	Vector3d p_esatto_3;
	p_esatto_3 = mesh.Cell0DsCoordinates.col(0);
	
	EXPECT_TRUE((p_funzione_3-p_esatto_3).norm()<tol);
	
	
	// test come sopra, ma step = b, allora deva ritornare il secondo punto passato alla funzione
	Vector3d p_funzione_4 = Nuovo_Vertice(0, 1, 2, 2, mesh);
	
	Vector3d p_esatto_4;
	p_esatto_4 = mesh.Cell0DsCoordinates.col(1);
	
	
	EXPECT_TRUE((p_funzione_4-p_esatto_4).norm()<tol);
	
	
	
	
}

}

