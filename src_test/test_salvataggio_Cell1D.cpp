#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {

	TEST(TestPolygons, TestSalvataggioCell1Ds) {
		PolygonalMesh mesh;
		valorizza_poliedro(3, mesh);

		const string filename = "test_Cell1Ds.txt";
		salvataggio_Cell1Ds(mesh, filename);

		ifstream file(filename);
		ASSERT_TRUE(file.is_open());

		string line;
		getline(file, line);
		EXPECT_EQ(line, "-- Cell1D --");

		getline(file, line);
		getline(file, line);
		EXPECT_EQ(line, "Numero di Cell1Ds: 6");

		getline(file, line);
		getline(file, line);
		EXPECT_EQ(line, "Identificativi: ");

		getline(file, line);
		EXPECT_EQ(stoi(line), 0);

		file.close();
		remove(filename.c_str());
	}
}