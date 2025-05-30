#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{

bool valorizza_poliedro(int q, PolygonalMesh& mesh);

bool controllo_lati_vertici (const PolygonalMesh& mesh);

string ArrayToString(const size_t& n, const double* const& v);

Eigen::VectorXd Nuovo_Vertice(unsigned int id1, unsigned int id2, unsigned int b, unsigned int step, const PolygonalMesh& mesh);

bool Triangolazione(PolygonalMesh& mesh, unsigned int b, unsigned int c, unsigned int q);

Eigen::Vector3d baricentro(const std::vector<size_t>& vertici, const Eigen::MatrixXd& coords);

PolygonalMesh CostruisciDualeMesh(const PolygonalMesh& mesh);

int Esiste_gia(PolygonalMesh& mesh, const Eigen::Vector3d& nuovo_vertice, unsigned int k);



}

