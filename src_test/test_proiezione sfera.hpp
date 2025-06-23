#pragma once
#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"  

using namespace std;

namespace PolygonalLibrary{
	TEST(TestPolygons, TestProiezioneSfera){
	PolygonalMesh mesh;
	mesh.NumCell0Ds = 3;
    mesh.Cell0DsId = {0, 1, 2};
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
	
	mesh.Cell0DsCoordinates.col(0) << 5.0, 1.0, 0.0;
	mesh.Cell0DsCoordinates.col(1) << -2.0, 4.0, 3.0;
	mesh.Cell0DsCoordinates.col(2) << 0.1, 0.2, 0.3;
	
	proiezione_su_sfera_unitaria(mesh);
	
	double tol = 1e-10;
        for (unsigned int i = 0; i < mesh.NumCell0Ds; i++){
            double norma = mesh.Cell0DsCoordinates.col(i).norm();
            EXPECT_NEAR(norma, 1.0, tol) << "Vertice " << i << " non è stato normalizzato correttamente.";
        }
    }
	TEST(TestPolygons, TestProiezioneSferaDirezioneInvariata){
        PolygonalMesh mesh;
		
        mesh.NumCell0Ds = 1;
        mesh.Cell0DsId = {0};
        mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		mesh.Cell0DsCoordinates.col(0) << 1.0, 0.0, 0.0;
		
		Eigen::Vector3d originale = mesh.Cell0DsCoordinates.col(0).normalized();
		proiezione_su_sfera_unitaria(mesh);
		
		Eigen::Vector3d proiettato = mesh.Cell0DsCoordinates.col(0);
		
		EXPECT_TRUE((originale - proiettato).norm() < 1e-10)
            << "La direzione del vertice è cambiata dopo la normalizzazione.";
    }
	TEST(TestPolygons, TestProiezioneSferaGiaNormalizzato){
        PolygonalMesh mesh;
		
        mesh.NumCell0Ds = 1;
        mesh.Cell0DsId = {0};
        mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);

        mesh.Cell0DsCoordinates.col(0) << 1.0, 0.0, 0.0;


        Eigen::Vector3d prima = mesh.Cell0DsCoordinates.col(0);

        proiezione_su_sfera_unitaria(mesh);
		
        Eigen::Vector3d dopo = mesh.Cell0DsCoordinates.col(0);
        EXPECT_TRUE((prima - dopo).norm() < 1e-10)
            << "Il punto già normalizzato è stato modificato dalla funzione.";
    }
}