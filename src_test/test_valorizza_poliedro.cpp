#pragma once
#include <gtest/gtest.h>
#include "Utils.hpp"

using namespace std;

TEST(TestPolygons, TestValorizzaPoliedroTetraedro) {
    PolygonalMesh mesh;

    bool success = valorizza_poliedro(3, mesh);

    ASSERT_TRUE(success);

    EXPECT_EQ(mesh.NumCell0Ds, 4);
    ASSERT_EQ(mesh.Cell0DsId.size(), 4);
    ASSERT_EQ(mesh.Cell0DsCoordinates.cols(), 4);
    ASSERT_EQ(mesh.Cell0DsCoordinates.rows(), 3);

    EXPECT_EQ(mesh.NumCell1Ds, 6);
    ASSERT_EQ(mesh.Cell1DsId.size(), 6);
    ASSERT_EQ(mesh.Cell1DsExtrema.cols(), 6);
    ASSERT_EQ(mesh.Cell1DsExtrema.rows(), 2);

    EXPECT_EQ(mesh.NumCell2Ds, 4);
    ASSERT_EQ(mesh.Cell2DsId.size(), 4);
    ASSERT_EQ(mesh.Cell2DsVertices.size(), 4);
    ASSERT_EQ(mesh.Cell2DsEdges.size(), 4);

    for (size_t i = 0; i < mesh.Cell2DsVertices.size(); ++i) {
        EXPECT_EQ(mesh.Cell2DsVertices[i].size(), 3); 
        EXPECT_EQ(mesh.Cell2DsEdges[i].size(), 3);
    }

    EXPECT_EQ(mesh.Cell3DsId, 0);
    EXPECT_EQ(mesh.Cell3DsNumVert, 4);
    EXPECT_EQ(mesh.Cell3DsNumEdg, 6);
    EXPECT_EQ(mesh.Cell3DsNumFaces, 4);
    ASSERT_EQ(mesh.Cell3DsVertices.size(), 4);
    ASSERT_EQ(mesh.Cell3DsEdges.size(), 6);
    ASSERT_EQ(mesh.Cell3DsFaces.size(), 4);
}

TEST(TestPolygons, TestValorizzaPoliedroOttaedro) {
    PolygonalMesh mesh;

    bool success = valorizza_poliedro(4, mesh);

    ASSERT_TRUE(success);

    EXPECT_EQ(mesh.NumCell0Ds, 6);
    ASSERT_EQ(mesh.Cell0DsId.size(), 6);
    ASSERT_EQ(mesh.Cell0DsCoordinates.cols(), 6);
    ASSERT_EQ(mesh.Cell0DsCoordinates.rows(), 3);

    EXPECT_EQ(mesh.NumCell1Ds, 12);
    ASSERT_EQ(mesh.Cell1DsId.size(), 12);
    ASSERT_EQ(mesh.Cell1DsExtrema.cols(), 12);
    ASSERT_EQ(mesh.Cell1DsExtrema.rows(), 2);

    EXPECT_EQ(mesh.NumCell2Ds, 8);
    ASSERT_EQ(mesh.Cell2DsId.size(), 8);
    ASSERT_EQ(mesh.Cell2DsVertices.size(), 8);
    ASSERT_EQ(mesh.Cell2DsEdges.size(), 8);

    for (size_t i = 0; i < mesh.Cell2DsVertices.size(); ++i) {
        EXPECT_EQ(mesh.Cell2DsVertices[i].size(), 3);
        EXPECT_EQ(mesh.Cell2DsEdges[i].size(), 3);
    }

    EXPECT_EQ(mesh.Cell3DsId, 0);
    EXPECT_EQ(mesh.Cell3DsNumVert, 6);
    EXPECT_EQ(mesh.Cell3DsNumEdg, 12);
    EXPECT_EQ(mesh.Cell3DsNumFaces, 8);
    ASSERT_EQ(mesh.Cell3DsVertices.size(), 6);
    ASSERT_EQ(mesh.Cell3DsEdges.size(), 12);
    ASSERT_EQ(mesh.Cell3DsFaces.size(), 8);
}

TEST(TestPolygons, TestValorizzaPoliedroIcosaedro) {
    PolygonalMesh mesh;

    bool success = valorizza_poliedro(5, mesh);

    ASSERT_TRUE(success);

    EXPECT_EQ(mesh.NumCell0Ds, 12);
    ASSERT_EQ(mesh.Cell0DsId.size(), 12);
    ASSERT_EQ(mesh.Cell0DsCoordinates.cols(), 12);
    ASSERT_EQ(mesh.Cell0DsCoordinates.rows(), 3);

    EXPECT_EQ(mesh.NumCell1Ds, 30);
    ASSERT_EQ(mesh.Cell1DsId.size(), 30);
    ASSERT_EQ(mesh.Cell1DsExtrema.cols(), 30);
    ASSERT_EQ(mesh.Cell1DsExtrema.rows(), 2);

    EXPECT_EQ(mesh.NumCell2Ds, 20);
    ASSERT_EQ(mesh.Cell2DsId.size(), 20);
    ASSERT_EQ(mesh.Cell2DsVertices.size(), 20);
    ASSERT_EQ(mesh.Cell2DsEdges.size(), 20);

    for (size_t i = 0; i < mesh.Cell2DsVertices.size(); ++i) {
        EXPECT_EQ(mesh.Cell2DsVertices[i].size(), 3);
        EXPECT_EQ(mesh.Cell2DsEdges[i].size(), 3);
    }

    EXPECT_EQ(mesh.Cell3DsId, 0);
    EXPECT_EQ(mesh.Cell3DsNumVert, 12);
    EXPECT_EQ(mesh.Cell3DsNumEdg, 30);
    EXPECT_EQ(mesh.Cell3DsNumFaces, 20);
    ASSERT_EQ(mesh.Cell3DsVertices.size(), 12);
    ASSERT_EQ(mesh.Cell3DsEdges.size(), 30);
    ASSERT_EQ(mesh.Cell3DsFaces.size(), 20);
}
