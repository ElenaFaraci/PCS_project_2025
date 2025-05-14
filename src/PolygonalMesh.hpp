#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
	// Cell0D
    unsigned int NumCell0Ds = 0; ///< number of Cell0D
    std::vector<unsigned int> Cell0DsId = {}; ///< Cell0D id, size 1 x NumberCell0D
    Eigen::MatrixXd Cell0DsCoordinates = {}; ///< Cell0D coordinates
    // I marker servono?
	// std::map<unsigned int, list<unsigned int>> MarkerCell0Ds = {}; ///< Cell0D markers

	//Cell1D
    unsigned int NumCell1Ds = 0; ///< number of Cell1D
    std::vector<unsigned int> Cell1DsId = {}; ///< Cell1D id, size 1 x NumberCell1D
    Eigen::MatrixXi Cell1DsExtrema = {}; ///< Cell1D vertices indices, size 2 x NumberCell1D (fromId,toId)
    // I marker servono?
	// std::map<unsigned int, list<unsigned int>> MarkerCell1Ds = {}; ///< Cell1D properties

	//Cell2D
    unsigned int NumCell2Ds = 0; ///< number of Cell2D
    std::vector<unsigned int> Cell2DsId = {}; ///< Cell2D id, size 1 x NumberCell2D
	std::vector<unsigned int> Cell2DsNumVert = {}; // vettore di interi positivi, ciascuno si riferisce al numero di vertici del poligono con id pari alla posizione nel vetore in questione
	std::vector<unsigned int> Cell2DsNumEdg = {}; // vettore di interi positivi, ciascuno si riferisce al numero di edges del poligono con id pari alla posizione nel vetore in questione
	std::vector<vector<unsigned int>> Cell2DsVertices = {}; // contiene gli id dei vertici dei poligoni, ordinatamente rispetto a come compaiono nel file csv
    std::vector<vector<unsigned int>> Cell2DsEdges = {}; 
	// I marker servono?
	// std::map<unsigned int, list<unsigned int>> MarkerCell2Ds = {};
	
	//Cell3D
	unsigned int NumCell3Ds = 1;
	unsigned int Cell3DsId; //(0=tetraedro, 1= ...)
	/* alternativa, con id specifico per ogni poliedro 
	std::vector<unsigned int> Cell3DsNumVert = {}; // indica il numero di vertici del poliedro identificato dalla posizione in questo vettore
	std::vector<unsigned int> Cell3DsNumEdg = {};
	std::vector<unsigned int> Cell3DsNumFaces = {};
	*/
	unsigned int Cell3DsNumVert =0;
	unsigned int Cell3DsNumEdg =0;
	unsigned int Cell3DsNumFaces =0;
	
	/*
	std::vector<vector<unsigned int>> Cell3DsVertices = {}; 
    std::vector<vector<unsigned int>> Cell3DsEdges = {}; 
	std::vector<vector<unsigned int>> Cell3DsFaces = {}; 
	*/
	vector<unsigned int> Cell3DsVertices = {};
	vector<unsigned int> Cell3DsEdges = {};
	vector<unsigned int> Cell3DsFaces = {};
	
	
};

}

