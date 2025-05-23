#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{

bool valorizza_poliedro(int q, PolygonalMesh& mesh);

bool controllo_lati_vertici (const PolygonalMesh& mesh);

string ArrayToString(const size_t& n, const double* const& v);

Eigen::VectorXd crea_vertice(unsigned int id_1, unsigned int id_2, 
				  unsigned int step, unsigned int id_start,
				  unsigned int b, const PolygonalMesh& mesh);



}

