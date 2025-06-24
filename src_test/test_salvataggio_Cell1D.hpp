#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {

	TEST(TestSalvataggio, TestSalvataggioCell1Ds) {
		PolygonalMesh mesh;
		ASSERT_TRUE(valorizza_poliedro(3, mesh));

		const string filename = "test_Cell1Ds.txt";
		salvataggio_Cell1Ds(mesh, filename);

		ifstream file(filename);
		ASSERT_TRUE(file.is_open());

		string line;
		while (getline(file, line)) {
			if (line.rfind("ID Vertici", 0) == 0) break;
		}
		while (getline(file, line) && line.empty());
		
		vector<pair<int, int>> estremi;
		do {
			istringstream iss(line);
			int a, b;
			if (iss >> a >> b) estremi.emplace_back(a, b);
			else break;
		} while (getline(file, line) && !line.empty());

		EXPECT_EQ(estremi.size(), mesh.NumCell1Ds);
		EXPECT_EQ(estremi[0].first, mesh.Cell1DsExtrema(0, 0));

		file.close();
		remove(filename.c_str());
		
}
}