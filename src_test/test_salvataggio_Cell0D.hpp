#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {

	TEST(TestSalvataggio, TestSalvataggioCell0Ds) {
		PolygonalMesh mesh;
		ASSERT_TRUE(valorizza_poliedro(3, mesh));

		const string filename = "test_Cell0Ds.txt";
		salvataggio_Cell0Ds(mesh, filename);

		ifstream file(filename);
		ASSERT_TRUE(file.is_open());

		string line;
		while (getline(file, line)) {
			if (line.rfind("Identificativi", 0) == 0) break;
		}
		while (getline(file, line) && line.empty());
		
		vector<int> ids;
		do {
			istringstream iss(line);
			int val;
			if (iss >> val) ids.push_back(val);
			else break;
		} 
		while (getline(file, line) && !line.empty());

		EXPECT_EQ(ids.size(), mesh.NumCell0Ds);
		EXPECT_EQ(ids.front(), mesh.Cell0DsId.front());

		file.close();
		remove(filename.c_str());
	}
}