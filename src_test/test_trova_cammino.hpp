#pragma once
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {

TEST(TestCammino, TestCamminoMinimoSimpleCase) {
    PolygonalMesh mesh;

	ASSERT_TRUE(valorizza_poliedro(5, mesh));  

	mesh.Cell0DsCoordinates.col(4) << 10, 10, 10;  

	trova_cammino_minimo(mesh, 0, 10); 
	
	vector<unsigned int> cammino_v_aspettato = {0, 2, 10};
    vector<unsigned int> cammino_v_ottenuto;
    for (unsigned int i = 0; i < mesh.NumCell0Ds; i++) {
        if (mesh.Cell0DsShortPath[i] == 1)
            cammino_v_ottenuto.push_back(i);
    }
    EXPECT_EQ(cammino_v_aspettato, cammino_v_ottenuto);
	
	vector<unsigned int> cammino_e_aspettato = {0, 13}; 
    vector<unsigned int> cammino_e_ottenuto;
    for (unsigned int i = 0; i < mesh.NumCell1Ds; i++) {
        if (mesh.Cell1DsShortPath[i] == 1)
            cammino_e_ottenuto.push_back(i);
    }
    EXPECT_EQ(cammino_e_aspettato, cammino_e_ottenuto);
	
	double lunghezza_attesa =
        (mesh.Cell0DsCoordinates.col(0) - mesh.Cell0DsCoordinates.col(2)).norm() +
        (mesh.Cell0DsCoordinates.col(2) - mesh.Cell0DsCoordinates.col(10)).norm();

    double lunghezza_calcolata = 0.0;
    for (size_t i = 0; i < cammino_v_ottenuto.size() - 1; ++i) {
        lunghezza_calcolata += (mesh.Cell0DsCoordinates.col(cammino_v_ottenuto[i]) -
                                mesh.Cell0DsCoordinates.col(cammino_v_ottenuto[i + 1])).norm();
    }
	
	double tol = 1e-10;
    EXPECT_NEAR(lunghezza_attesa, lunghezza_calcolata, tol);
}

}