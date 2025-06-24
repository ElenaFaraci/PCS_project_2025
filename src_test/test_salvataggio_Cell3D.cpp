#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {

	TEST(TestPolygons, TestSalvataggioCell3Ds) {
		PolygonalMesh mesh;
		valorizza_poliedro(3, mesh);

		const string filename = "test_Cell3Ds.txt";
		salvataggio_Cell3Ds(mesh, filename);

		ifstream file(filename);
		ASSERT_TRUE(file.is_open());

		string line;
		getline(file, line);
		EXPECT_EQ(line, "-- Cell3D --");

		getline(file, line);
		getline(file, line);
		EXPECT_EQ(line, "Numero di Cell3Ds: 1");

		getline(file, line);
		getline(file, line);
		EXPECT_EQ(line, "Numero Vertici:  4");

		file.close();
		remove(filename.c_str());
	}
}
