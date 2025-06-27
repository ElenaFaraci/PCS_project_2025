#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{

bool valorizza_poliedro(unsigned int q, PolygonalMesh& mesh); 

bool controllo_lati_vertici (const PolygonalMesh& mesh);

Eigen::VectorXd Nuovo_Vertice(unsigned int id1, unsigned int id2, unsigned int b, unsigned int step, const PolygonalMesh& mesh);




bool Triangolazione(PolygonalMesh& mesh, unsigned int b, unsigned int c, unsigned int q);

bool triangolazione_2(PolygonalMesh& mesh, unsigned int b, unsigned int q);

Eigen::Vector3d baricentro(const std::vector<unsigned int>& vertici, const PolygonalMesh& mesh); 

PolygonalMesh CostruisciDualeMesh(const PolygonalMesh& mesh);




int Esiste_gia(PolygonalMesh& mesh, const Eigen::Vector3d& nuovo_vertice, unsigned int k);


void tri_vertici_facce(PolygonalMesh& mesh, unsigned int b, const vector<unsigned int>& punti_faccia,
					   unsigned int num_facc_pre, unsigned int num_nuovi_per_faccia);

int esiste_gia_1D(unsigned int point_1, unsigned int point_2, const PolygonalMesh& mesh);

void tri_lati_facce(PolygonalMesh& mesh, unsigned int b,unsigned int num_facc_pre);

void proiezione_su_sfera_unitaria(PolygonalMesh& mesh);

void info_mesh(const PolygonalMesh& mesh);

void salvataggio_Cell0Ds(const PolygonalMesh& mesh, const std::string& filename);

void salvataggio_Cell1Ds(const PolygonalMesh& mesh, const std::string& filename);

void salvataggio_Cell2Ds(const PolygonalMesh& mesh, const std::string& filename);

void salvataggio_Cell3Ds(const PolygonalMesh& mesh, const std::string& filename);

double distanza(const Vector3d& p1, const Vector3d& p2);

void trova_cammino_minimo(PolygonalMesh& mesh, int id1, int id2);

vector<vector<unsigned int>> trova_facce_per_vertice(const PolygonalMesh& mesh);



using Grafo = std::vector<std::vector<std::pair<int, double>>>;
std::vector<int> dijkstra(const Grafo& la, int s, int w, std::vector<double>& dist, std::vector<int>& pred);
Grafo costruisci_grafo_pesato(int n, const Eigen::MatrixXi& Cell1DsExtrema, const std::vector<Eigen::Vector3d>& coords);


vector<unsigned int> giro_attorno_vertice(const PolygonalMesh& mesh, unsigned int v,
										  const vector<unsigned int>& facce_vicinato_v);

bool converti_uns_int(const char* str, unsigned int& out);

void stampa_para_cammino(PolygonalMesh& mesh);

}

