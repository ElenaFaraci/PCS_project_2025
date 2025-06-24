#pragma once
#include <vector>
#include "Eigen/Eigen"
#include <gtest/gtest.h>
#include <cmath>
#include "Utils.hpp"  

using namespace std;

namespace PolygonalLibrary{

	TEST(TestGrafo, CostruisciGrafoPesato) {
		int n = 3;
		Eigen::MatrixXi Cell1DsExtrema(2, 3);
		Cell1DsExtrema << 0, 1, 2,
						  1, 2, 0;
		std::vector<Eigen::Vector3d> coords = {
			{0.0, 0.0, 0.0},
			{1.0, 0.0, 0.0},
			{0.0, 1.0, 0.0}
		};

		Grafo grafo = costruisci_grafo_pesato(n, Cell1DsExtrema, coords);

		ASSERT_EQ(grafo.size(), 3);
		
		ASSERT_EQ(grafo[0].size(), 2);
		EXPECT_EQ(grafo[0][0].first, 1);
		EXPECT_DOUBLE_EQ(grafo[0][0].second, 1.0);
		EXPECT_EQ(grafo[0][1].first, 2);
		EXPECT_DOUBLE_EQ(grafo[0][1].second, 1.0);

		ASSERT_EQ(grafo[1].size(), 2);
		EXPECT_EQ(grafo[1][0].first, 0);
		EXPECT_DOUBLE_EQ(grafo[1][0].second, 1.0);
		EXPECT_EQ(grafo[1][1].first, 2);
		EXPECT_DOUBLE_EQ(grafo[1][1].second, std::sqrt(2.0));

		ASSERT_EQ(grafo[2].size(), 2);
		EXPECT_EQ(grafo[2][0].first, 1);
		EXPECT_DOUBLE_EQ(grafo[2][0].second, std::sqrt(2.0));
		EXPECT_EQ(grafo[2][1].first, 0);
		EXPECT_DOUBLE_EQ(grafo[2][1].second, 1.0);
	}
}