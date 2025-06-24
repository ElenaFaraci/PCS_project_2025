#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

TEST(TestPolygons, TestSalvataggioCell2Ds) {
    PolygonalMesh mesh;
    valorizza_poliedro(3, mesh);

    const std::string filename = "test_Cell2Ds.txt";
    salvataggio_Cell2Ds(mesh, filename);

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "-- Cell2D --");

    std::getline(file, line);
    std::getline(file, line);
    EXPECT_EQ(line, "Numero di Cell2Ds: 4");

    std::getline(file, line);
    std::getline(file, line);
    EXPECT_EQ(line, "Identificativi: ");

    std::getline(file, line);
    EXPECT_EQ(std::stoi(line), 0);

    file.close();
    std::remove(filename.c_str());
}