#pragma once
#include <gtest/gtest.h>
#include <vector>
#include <limits>
#include <cmath>
#include "Utils.hpp" 

using namespace std;

namespace PolygonalLibrary {

TEST(TestCammino, CamminoMinimoSemplice) {
    Grafo grafo(3);
    grafo[0].push_back({1, 1.0});
    grafo[1].push_back({0, 1.0});
    grafo[1].push_back({2, 1.0});
    grafo[2].push_back({1, 1.0});

    vector<double> dist;
    vector<int> pred;

    vector<int> cammino = dijkstra(grafo, 0, 2, dist, pred);

    vector<int> cammino_atteso = {0, 1, 2};
    EXPECT_EQ(cammino, cammino_atteso);

    EXPECT_DOUBLE_EQ(dist[0], 0.0);
    EXPECT_DOUBLE_EQ(dist[1], 1.0);
    EXPECT_DOUBLE_EQ(dist[2], 2.0);

    EXPECT_EQ(pred[0], 0);
    EXPECT_EQ(pred[1], 0);
    EXPECT_EQ(pred[2], 1);
}
}