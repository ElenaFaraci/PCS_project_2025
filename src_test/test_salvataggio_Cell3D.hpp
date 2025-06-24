#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {

	TEST(TestSalvataggio, TestSalvataggioCell3Ds) {
		PolygonalMesh mesh;
		ASSERT_TRUE(valorizza_poliedro(3, mesh));

		const string filename = "test_Cell3Ds.txt";
		salvataggio_Cell3Ds(mesh, filename);

		ifstream file(filename);
		ASSERT_TRUE(file.is_open());

		string line;
		while (getline(file, line)) {
        if (line.rfind("Vertici", 0) == 0) break;
		}
		while (getline(file, line) && line.empty());

		vector<int> vertici;
		do {
			istringstream iss(line);
			int id;
			if (iss >> id) vertici.push_back(id);
			else break;
		} while (getline(file, line) && !line.empty());

		EXPECT_EQ(vertici.size(), mesh.Cell3DsNumVert);
		EXPECT_EQ(vertici[0], mesh.Cell3DsVertices[0]);

		file.close();
		remove(filename.c_str());
	}
}
