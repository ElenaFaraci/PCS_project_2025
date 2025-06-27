#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
	//Cell0D
    unsigned int NumCell0Ds = 0; // numero vertici
    std::vector<unsigned int> Cell0DsId = {}; // id dei vertici [1 x NumCell0Ds]
    Eigen::MatrixXd Cell0DsCoordinates = {}; // coordinate vertici [3 x NumCell0Ds]
    

	//Cell1D
    unsigned int NumCell1Ds = 0; //numero lati
    std::vector<unsigned int> Cell1DsId = {}; // id dei lati [1 x NumCell1Ds]
    Eigen::MatrixXi Cell1DsExtrema = {}; // id di partenza e arrivo dei lati,
	                                     // ordinati sulle colonne per id [2 x NumCell1Ds]
   
	//Cell2D
    unsigned int NumCell2Ds = 0; // numero facce
    std::vector<unsigned int> Cell2DsId = {}; // id delle facce [1 x NumCell2Ds]
	std::vector<unsigned int> Cell2DsNumVert = {}; // vettore di interi positivi, ciascuno si riferisce al numero di vertici del poligono con id pari alla posizione nel vetore in questione
	std::vector<unsigned int> Cell2DsNumEdg = {}; // vettore di interi positivi, ciascuno si riferisce al numero di edges del poligono con id pari alla posizione nel vetore in questione
	std::vector<vector<unsigned int>> Cell2DsVertices = {}; // contiene gli id dei vertici dei poligoni 
    std::vector<vector<unsigned int>> Cell2DsEdges = {}; // contiene gli id dei lati dei poligoni 
	
	//Cell3D
	unsigned int NumCell3Ds = 1; // nel nostro progetto sarà sempre 1
	unsigned int Cell3DsId; 

	unsigned int Cell3DsNumVert =0; // numero vertici del solido
	unsigned int Cell3DsNumEdg =0; // numero lari del solido
	unsigned int Cell3DsNumFaces =0; // numero facce del solido

	vector<unsigned int> Cell3DsVertices = {}; // id vertici
	vector<unsigned int> Cell3DsEdges = {}; // id lati
	vector<unsigned int> Cell3DsFaces = {}; // id facce
	
	// PARAVIEW
	std::vector<int> Cell0DsShortPath; // gli id dei vertici che fanno parte del cammino minimo valgono 1, gli altri zero
    std::vector<int> Cell1DsShortPath; // gli id dei lati che fanno parte del cammino minimo valgono 1, gli altri zero
	
};

}

