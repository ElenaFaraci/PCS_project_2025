#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

TEST(TestPolygons, TestSalvataggioCell0Ds) {
    PolygonalMesh mesh;
    valorizza_poliedro(3, mesh);

    const std::string filename = "test_Cell0Ds.txt";
    salvataggio_Cell0Ds(mesh, filename);

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "-- Cell0D --");

    std::getline(file, line); 
    std::getline(file, line);
    EXPECT_EQ(line, "Numero di Cell0Ds: 4");

    std::getline(file, line); 
    std::getline(file, line);
    EXPECT_EQ(line, "Identificativi: ");

    std::getline(file, line);
    EXPECT_EQ(std::stoi(line), 0);

    file.close();
    std::remove(filename.c_str());
}
