#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {

	TEST(TestPolygons, TestSalvataggioCell0Ds) {
		PolygonalMesh mesh;
		valorizza_poliedro(3, mesh);

		const std::string filename = "test_Cell0Ds.txt";
		salvataggio_Cell0Ds(mesh, filename);

		ifstream file(filename);
		ASSERT_TRUE(file.is_open());

		string line;
		getline(file, line);
		EXPECT_EQ(line, "-- Cell0D --");

		getline(file, line); 
		getline(file, line);
		EXPECT_EQ(line, "Numero di Cell0Ds: 4");

		getline(file, line); 
		getline(file, line);
		EXPECT_EQ(line, "Identificativi: ");

		getline(file, line);
		EXPECT_EQ(stoi(line), 0);

		file.close();
		remove(filename.c_str());
	}
}