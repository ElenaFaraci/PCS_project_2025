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



/// Triangolazione: Iterando sulle facce e sui "piani" di ogni faccia,
/// crea i vertici della triangolazione e li aggiunge a Cell0DsCoordinates.
/// Inoltre, crea un vettore punti_faccia che contiene gli ID dei vertici 
/// di ogni faccia, una dopo l'altra, srotolati per piano. 
/// Per completare la triangolazione, chiama altre due funzioni: 
/// tri_vertici_facce e tri_lati_facce
bool Triangolazione(PolygonalMesh& mesh, unsigned int b, unsigned int c, unsigned int q);

Eigen::Vector3d baricentro(const std::vector<unsigned int>& vertici, const PolygonalMesh& mesh); 

PolygonalMesh CostruisciDualeMesh(const PolygonalMesh& mesh);



/// Data la mesh, le coordinate di un punto e il numero di punti presenti 
/// nella mesh, ritorna -1, se le coordinate passate alla funzione non 
/// coincidono con nessun punto già presente. Altrimenti, ritorna l'id del punto 
/// coincidente con quelle coordinate
int Esiste_gia(PolygonalMesh& mesh, const Eigen::Vector3d& nuovo_vertice, unsigned int k);


void tri_vertici_facce(PolygonalMesh& mesh, unsigned int b, vector<int> punti_faccia,
					   unsigned int num_facc_pre, unsigned int num_nuovi_per_faccia);

int esiste_gia_1D(int point_1, int point_2, const PolygonalMesh& mesh);

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

vector<unsigned int> giro_attorno_vertice(const PolygonalMesh& mesh, unsigned int v,
										  const vector<unsigned int>& facce_vicinato_v);
}

