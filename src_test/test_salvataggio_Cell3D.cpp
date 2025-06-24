#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

TEST(TestPolygons, TestSalvataggioCell3Ds) {
    PolygonalMesh mesh;
    valorizza_poliedro(3, mesh);

    const std::string filename = "test_Cell3Ds.txt";
    salvataggio_Cell3Ds(mesh, filename);

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "-- Cell3D --");

    std::getline(file, line);
    std::getline(file, line);
    EXPECT_EQ(line, "Numero di Cell3Ds: 1");

    std::getline(file, line);
    std::getline(file, line);
    EXPECT_EQ(line, "Numero Vertici:  4");

    file.close();
    std::remove(filename.c_str());
}
