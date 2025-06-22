#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "Eigen/Eigen"
#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {
	TEST(TestPolygons, TestSalvataggioCelle) {
    PolygonalMesh mesh;
    mesh.NumCell0Ds = 1;
    mesh.Cell0DsId = {0};
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates.col(0) << 1.0, 2.0, 3.0;

    mesh.NumCell1Ds = 1;
    mesh.Cell1DsId = {0};
    mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
    mesh.Cell1DsExtrema.col(0) << 0, 0;

    mesh.NumCell2Ds = 1;
    mesh.Cell2DsId = {0};
    mesh.Cell2DsNumVert = {3};
    mesh.Cell2DsNumEdg = {3};
    mesh.Cell2DsVertices = {{0, 0, 0}};
    mesh.Cell2DsEdges = {{0, 0, 0}};

    mesh.NumCell3Ds = 1;
    mesh.Cell3DsId = 0;
    mesh.Cell3DsNumVert = 1;
    mesh.Cell3DsNumEdg = 1;
    mesh.Cell3DsNumFaces = 1;
    mesh.Cell3DsVertices = {0};
    mesh.Cell3DsEdges = {0};
    mesh.Cell3DsFaces = {0};
	