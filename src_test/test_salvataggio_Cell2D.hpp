#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {
	TEST(TestSalvataggio, TestSalvataggioCell2Ds) {
		PolygonalMesh mesh;
		ASSERT_TRUE(valorizza_poliedro(3, mesh));

		const string filename = "test_Cell2Ds.txt";
		salvataggio_Cell2Ds(mesh, filename);

		ifstream file(filename);
		ASSERT_TRUE(file.is_open());

		string line;
		while (getline(file, line)) {
        if (line.rfind("Vertici", 0) == 0) break;
		}
		while (getline(file, line) && line.empty());


		vector<vector<int>> facce;
		do {
			istringstream iss(line);
			vector<int> faccia;
			int v;
			while (iss >> v) faccia.push_back(v);
			if (!faccia.empty()) facce.push_back(faccia);
			else break;
		} while (getline(file, line) && !line.empty());

		EXPECT_EQ(facce.size(), mesh.NumCell2Ds);
		EXPECT_EQ(facce[0][0], mesh.Cell2DsVertices[0][0]);

		file.close();
		remove(filename.c_str());
}
}