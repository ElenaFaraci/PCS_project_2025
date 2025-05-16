#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
/*
SCALETTA:
main, cmake, gitignore, finire poliedri (questa settimana)
triangolazione
duale proiezione
punto 2
*/




namespace PolygonalLibrary
{
	
	
	
	
// TODO controllo su p, dentro la finzione o fuori?
bool valorizza_poliedro(int q, PolygonalMesh& mesh){
	
	if (q==3){
		//Cell0Ds
		mesh.NumCell0Ds=4;
		mesh.Cell0DsId = {0,1,2,3}; // è efficiente? reserve?
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		mesh.Cell0DsCoordinates.col(0) << 1.0/sqrt(3), 1.0/sqrt(3), 1.0/sqrt(3);
		mesh.Cell0DsCoordinates.col(1) << -1.0/sqrt(3), -1.0/sqrt(3), 1.0/sqrt(3);
		mesh.Cell0DsCoordinates.col(2) << -1.0/sqrt(3), 1.0/sqrt(3), -1.0/sqrt(3);
		mesh.Cell0DsCoordinates.col(3) << 1.0/sqrt(3), -1.0/sqrt(3), -1.0/sqrt(3);

		//Cell1Ds
		mesh.NumCell1Ds=6;
		mesh.Cell1DsId = {0,1,2,3,4,5}; // è efficiente? reserve? Vanno ordinati?
		
		mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
		mesh.Cell1DsExtrema.col(0) << 0, 1 ;
		mesh.Cell1DsExtrema.col(1) << 0, 2 ;
		mesh.Cell1DsExtrema.col(2) << 0, 3 ;
		mesh.Cell1DsExtrema.col(3) << 1, 2 ;
		mesh.Cell1DsExtrema.col(4) << 1, 3 ;
		mesh.Cell1DsExtrema.col(5) << 2, 3 ;
		
		//Cell2Ds
		mesh.NumCell2Ds = 4;
		mesh.Cell2DsId = {0, 1 ,2, 3};
		mesh.Cell2DsNumVert = {3, 3, 3, 3};
		mesh.Cell2DsNumEdg = {3, 3, 3, 3};
		
		
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds); // serve davvero?
		
		vector<unsigned int> v1 = {0,1,2};
		vector<unsigned int> v2 = {1,2,3};
		vector<unsigned int> v3 = {0,2,3};
		vector<unsigned int> v4 = {0,1,3};
		
		mesh.Cell2DsVertices= {v1, v2, v3, v4};
		
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> v1 = {0,3,1};
		vector<unsigned int> v2 = {3,5,4};
		vector<unsigned int> v3 = {1,5,2};
		vector<unsigned int> v4 = {0,4,2};
		
		mesh.Cell2DsEdges = {v1, v2, v3, v4};
		
		//Cell3Ds
		mesh.Cell3DsId=0; //caso tetraedro
		
		mesh.Cell3DsNumVert = mesh.NumCell0Ds;
		mesh.Cell3DsNumEdg = mesh.NumCell1Ds;
		mesh.Cell3DsNumFaces = mesh.NumCell2Ds;
		
		Cell3DsVertices = mesh.Cell0DsId; //costruttore di copia? 
		Cell3DsEdges = mesh.Cell1DsId;
		Cell3DsFaces = mesh.Cell2DsId
		
		
		}

	else if (q==4){
		//Cell0Ds
		mesh.NumCell0Ds=6;
		mesh.Cell0DsId = {0,1,2,3,4,5}; // è efficiente? reserve?
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		mesh.Cell0DsCoordinates.col(0) << 0.0, 0.0, 1.0;
		mesh.Cell0DsCoordinates.col(1) << 0.0, -1.0, 0.0;
		mesh.Cell0DsCoordinates.col(2) << 1.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(3) << 0.0, 1.0, 0.0;
		mesh.Cell0DsCoordinates.col(4) << -1.0, 0.0, 0.0;
		mesh.Cell0DsCoordinates.col(5) << 0.0, 0.0, -1.0;
		
		//Cell1Ds
		mesh.NumCell1Ds=12;
		mesh.Cell1DsId = {0,1,2,3,4,5,6,7,8,9,10,11}; // è efficiente? reserve? Vanno ordinati?
		
		mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
		mesh.Cell1DsExtrema.col(0) << 0, 1;
		mesh.Cell1DsExtrema.col(1) << 0, 2;
		mesh.Cell1DsExtrema.col(2) << 0, 3;
		mesh.Cell1DsExtrema.col(3) << 0, 4;
		mesh.Cell1DsExtrema.col(4) << 1, 2;
		mesh.Cell1DsExtrema.col(5) << 1, 4;
		mesh.Cell1DsExtrema.col(6) << 1, 5;
		mesh.Cell1DsExtrema.col(7) << 2, 3;
		mesh.Cell1DsExtrema.col(8) << 2, 5;
		mesh.Cell1DsExtrema.col(9) << 3, 4;
		mesh.Cell1DsExtrema.col(10) << 3, 5;
		mesh.Cell1DsExtrema.col(11) << 4, 5;
		
		//Cell2Ds
		mesh.NumCell2Ds = 8;
		mesh.Cell2DsId = {0, 1 ,2, 3, 4, 5, 6, 7};
		mesh.Cell2DsNumVert = {3, 3, 3, 3, 3, 3, 3, 3};
		mesh.Cell2DsNumEdg = {3, 3, 3, 3, 3, 3, 3, 3};
		
		
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds); // serve davvero?
		
		vector<unsigned int> v1 = {0,1,2};
		vector<unsigned int> v2 = {0,2,3};
		vector<unsigned int> v3 = {0,3,4};
		vector<unsigned int> v4 = {0,1,4};
		vector<unsigned int> v5 = {1,2,5};
		vector<unsigned int> v6 = {2,3,5};
		vector<unsigned int> v7 = {3,4,5};
		vector<unsigned int> v8 = {1,4,5};

		
		mesh.Cell2DsVertices= {v1, v2, v3, v4, v5, v6, v7, v8};
		
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> e1 = {0,4,1};
		vector<unsigned int> e2 = {1,7,2};
		vector<unsigned int> e3 = {2,3,9};
		vector<unsigned int> e4 = {0,5,3};
		vector<unsigned int> e5 = {6,5,11};
		vector<unsigned int> e6 = {10,9,11};
		vector<unsigned int> e7 = {8,7,10};
		vector<unsigned int> e8 = {6,4,8};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4, e5, e6, e7, e8};
		
		//Cell3D
		
		vector<unsigned int> Cell3DsNumVert = {6};
		vector<unsigned int> Cell3DsNumEdg = {12};
		vector<unsigned int> Cell3DsNumFaces = {8};
	
		vector<vector<unsigned int>> Cell3DsVertices = {0, 1, 2, 3, 4, 5};
		vector<vector<unsigned int>> Cell3DsEdges = {0,1,2,3,4,5,6,7,8,9,10,11};
		vector<vector<unsigned int>> Cell3DsFaces = {0, 1 ,2, 3, 4, 5, 6, 7};
		}
		
		
		
	else if (q==5){
		//Cell0Ds
		mesh.NumCell0Ds=12;
		mesh.Cell0DsId = {0,1,2,3,4,5,6,7,8,9,10,11}; // è efficiente? reserve?
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		double phi = (1+sqrt(5))/2;
		double A = 1/(sqrt(1+phi^2));
		double B = phi/(sqrt(1+phi^2));
		
		mesh.Cell0DsCoordinates.col(0) << A, B, 0.0;
		mesh.Cell0DsCoordinates.col(1) << -A, -B, 0.0;
		mesh.Cell0DsCoordinates.col(2) << -A, B, 0.0;
		mesh.Cell0DsCoordinates.col(3) << A, -B, 0.0;
		mesh.Cell0DsCoordinates.col(4) << 0.0, A, B;
		mesh.Cell0DsCoordinates.col(5) << 0.0, -A, -B;
		mesh.Cell0DsCoordinates.col(6) << 0.0, -A, B;
		mesh.Cell0DsCoordinates.col(7) << 0.0, A, -B;
		mesh.Cell0DsCoordinates.col(8) << B, 0.0, A;
		mesh.Cell0DsCoordinates.col(9) << -B, 0.0, -A;
		mesh.Cell0DsCoordinates.col(10) << -B, 0.0, A;
		mesh.Cell0DsCoordinates.col(11) << B, 0.0, -A;

		
		//Cell1Ds
		mesh.NumCell1Ds=30;
		mesh.Cell1DsId = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29}; // è efficiente? reserve? Vanno ordinati?
		
		mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
		mesh.Cell1DsExtrema.col(0) << 0, 2;
		mesh.Cell1DsExtrema.col(1) << 0, 4;
		mesh.Cell1DsExtrema.col(2) << 0, 7;
		mesh.Cell1DsExtrema.col(3) << 0, 8;
		mesh.Cell1DsExtrema.col(4) << 0, 11;
		mesh.Cell1DsExtrema.col(5) << 1, 3;
		mesh.Cell1DsExtrema.col(6) << 1, 5;
		mesh.Cell1DsExtrema.col(7) << 1, 6;
		mesh.Cell1DsExtrema.col(8) << 1, 9;
		mesh.Cell1DsExtrema.col(9) << 1, 10;
		mesh.Cell1DsExtrema.col(10) << 2, 4;
		mesh.Cell1DsExtrema.col(11) << 2, 7;
		mesh.Cell1DsExtrema.col(12) << 2, 9;
		mesh.Cell1DsExtrema.col(13) << 2, 10;
		mesh.Cell1DsExtrema.col(14) << 3, 5;
		mesh.Cell1DsExtrema.col(15) << 3, 6;
		mesh.Cell1DsExtrema.col(16) << 3, 8;
		mesh.Cell1DsExtrema.col(17) << 3, 11;
		mesh.Cell1DsExtrema.col(18) << 4, 6;
		mesh.Cell1DsExtrema.col(19) << 4, 8;
		mesh.Cell1DsExtrema.col(20) << 4, 10;
		mesh.Cell1DsExtrema.col(21) << 5, 7;
		mesh.Cell1DsExtrema.col(22) << 5, 9;
		mesh.Cell1DsExtrema.col(23) << 5, 11;
		mesh.Cell1DsExtrema.col(24) << 6, 8;
		mesh.Cell1DsExtrema.col(25) << 6, 10;
		mesh.Cell1DsExtrema.col(26) << 7, 9;
		mesh.Cell1DsExtrema.col(27) << 7, 11;
		mesh.Cell1DsExtrema.col(28) << 8, 11;
		mesh.Cell1DsExtrema.col(29) << 9, 10;


		
		//Cell2Ds
		mesh.NumCell2Ds = 20;
		mesh.Cell2DsId = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
		mesh.Cell2DsNumVert = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
		mesh.Cell2DsNumEdg = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
		
		
		mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds); // serve davvero?
		
		vector<unsigned int> v1 = {0,4,8};
		vector<unsigned int> v2 = {0,2,4};
		vector<unsigned int> v3 = {2,4,10};
		vector<unsigned int> v4 = {4,6,10};
		vector<unsigned int> v5 = {4,6,8};
		vector<unsigned int> v6 = {1,3,6};
		vector<unsigned int> v7 = {1,6,10};
		vector<unsigned int> v8 = {3,6,8};
		vector<unsigned int> v9 = {3,8,11};
		vector<unsigned int> v10 = {0,8,11};
		vector<unsigned int> v11 = {0,7,11};
		vector<unsigned int> v12 = {2,7,9};
		vector<unsigned int> v13 = {2,9,10};
		vector<unsigned int> v14 = {1,9,10};
		vector<unsigned int> v15 = {1,5,9};
		vector<unsigned int> v16 = {5,7,9};
		vector<unsigned int> v17 = {1,3,5};
		vector<unsigned int> v18 = {3,5,11};
		vector<unsigned int> v19 = {5,7,11};
		vector<unsigned int> v20 = {0,2,7};

		
		mesh.Cell2DsVertices= {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v20};
		
		mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
		
		vector<unsigned int> e1 = {19,1,3};
		vector<unsigned int> e2 = {0,1,10};
		vector<unsigned int> e3 = {10,20,13};
		vector<unsigned int> e4 = {25,20,18};
		vector<unsigned int> e5 = {24,18,19};
		vector<unsigned int> e6 = {15,7,5};
		vector<unsigned int> e7 = {9,7,25};
		vector<unsigned int> e8 = {24,15,16};
		vector<unsigned int> e9 = {17,16,28};
		vector<unsigned int> e10 = {3,4,28};
		vector<unsigned int> e11 = {4,2,27};
		vector<unsigned int> e12 = {11,12,26};
		vector<unsigned int> e13 = {12,13,29};
		vector<unsigned int> e14 = {8,9,29};
		vector<unsigned int> e15 = {6,8,22};
		vector<unsigned int> e16 = {21,22,26};
		vector<unsigned int> e17 = {5,6,14};
		vector<unsigned int> e18 = {14,17,23};
		vector<unsigned int> e19 = {21,23,27};
		vector<unsigned int> e20 = {0,2,11};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20};
		
		//Cell3D
		
		vector<unsigned int> Cell3DsNumVert = {12};
		vector<unsigned int> Cell3DsNumEdg = {30};
		vector<unsigned int> Cell3DsNumFaces = {20};
	
		vector<vector<unsigned int>> Cell3DsVertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
		vector<vector<unsigned int>> Cell3DsEdges = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};
		vector<vector<unsigned int>> Cell3DsFaces = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
		}
		
		
		
	else{
		cerr<<"valore di q non valido"<<endl;
		return false;
	}
	
	
}


bool controllo_lati_vertici (const PolygonalMesh& mesh){
	for (unsigned int i=0; i<mesh.NumCell2Ds; i++){
		for (unsigned int j=0; j<(mesh.Cell2DsEdges[i]).size(); j++){
			
			unsigned int id_vertice = mesh.Cell2DsVertices[i][j];
			unsigned int id_lato=mesh.Cell2DsEdges[i][j];
			unsigned int id_lato_succ=mesh.Cell2DsEdges[i][(j+1)%(mesh.Cell2DsEdges[i]).size()];
			unsigned int count =0;
			
			//Controllo Lati
			if (mesh.Cell1DsExtrema(0,id_lato)=mesh.Cell1DsExtrema(0,id_lato_succ))
				count++;
			if (mesh.Cell1DsExtrema(0,id_lato)=mesh.Cell1DsExtrema(1,id_lato_succ))
				count++;
			if (mesh.Cell1DsExtrema(1,id_lato)=mesh.Cell1DsExtrema(0,id_lato_succ))
				count++;
			if (mesh.Cell1DsExtrema(1,id_lato)=mesh.Cell1DsExtrema(1,id_lato_succ))
				count++;
			
			if (count != 1){
				return false;
			}
			
			// Controllo Vertici
			if (id_vertice == mesh.Cell1DsExtrema(0,id_lato))
				count++;
			if (id_vertice == mesh.Cell1DsExtrema(1,id_lato))
				count++;
			
			if (count != 2)
				return false;
			
			
		}
			
	}
	return true;
}



/*
bool ImportMesh(PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;

    return true;

}
// ***************************************************************************
bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;

    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell0Ds = listLines.size();

    if (mesh.NumCell0Ds == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;
		char delim;

        converter >>  id >> delim
		>> marker >> delim
		>>mesh.Cell0DsCoordinates(0, id) >> delim
		>> mesh.Cell0DsCoordinates(1, id);

        mesh.Cell0DsId.push_back(id);

        /// Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell0Ds.find(marker);
            if(it == mesh.MarkerCell0Ds.end())
            {
                mesh.MarkerCell0Ds.insert({marker, {id}});
            }
            else
            {
                // mesh.MarkerCell0Ds[marker].push_back(id);
                it->second.push_back(id);
            }
        }

    }

    return true;
}
// ***************************************************************************

bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell1Ds = listLines.size();

    if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
	// OSS gli estremi sono gli id delle cell0D

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;
		char delim;

        converter >>  id >> delim
		>> marker >> delim 
		>>  mesh.Cell1DsExtrema(0, id) >> delim
		>>  mesh.Cell1DsExtrema(1, id);
        mesh.Cell1DsId.push_back(id);

        /// Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell1Ds.find(marker);
            if(it == mesh.MarkerCell1Ds.end())
            {
                mesh.MarkerCell1Ds.insert({marker, {id}});
            }
            else
            {
                // mesh.MarkerCell1Ds[marker].push_back(id);
                it->second.push_back(id);
            }
        }
    }

    return true;
}
// ***************************************************************************


bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell2Ds = listLines.size();

    if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
	
	mesh.Cell2DsNumVert.reserve(mesh.NumCell2Ds);
	mesh.Cell2DsNumEdg.reserve(mesh.NumCell2Ds);
	
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
		unsigned int marker;
		unsigned int NumVert;
		unsigned int NumEdg;
		char delim;
		unsigned int Vert;
		

        converter >>  id >> delim >> marker >> delim >> NumVert >> delim;
		
		vector<unsigned int> v = {};
		v.reserve(NumVert);
		
        for(unsigned int i = 0; i < NumVert; i++){
            converter >> Vert >> delim;
			v.push_back(Vert);
		}
		converter >> NumEdg >> delim;
		
		vector<unsigned int> e = {};
		e.reserve(NumEdg);
		
        for(unsigned int i = 0; i < NumEdg; i++){
            converter >> Vert;
			
			e.push_back(Vert);
			if (i < NumEdg - 1) converter >> delim;

		}
		
        mesh.Cell2DsId.push_back(id);
		mesh.Cell2DsNumVert.push_back(NumVert);
		mesh.Cell2DsNumEdg.push_back(NumEdg);
		mesh.Cell2DsVertices.push_back(v);
		mesh.Cell2DsEdges.push_back(e);
		
		
        
		if(marker != 0)
        {
            const auto it = mesh.MarkerCell2Ds.find(marker);
            if(it == mesh.MarkerCell2Ds.end())
            {
                mesh.MarkerCell2Ds.insert({marker, {id}});
            }
            else
            {
                // mesh.MarkerCell1Ds[marker].push_back(id);
                it->second.push_back(id);
            }
        }
		
    }

    return true;
}
//**************************************************************************************
bool test_edges(const PolygonalMesh& mesh){
	const double eps_1 = 10e-8;
	for (unsigned int i=0;i<mesh.NumCell1Ds;i++){
		
		unsigned int idInizio= mesh.Cell1DsExtrema(0,i);
		unsigned int idFine = mesh.Cell1DsExtrema(1,i);
		
		double x1 =mesh.Cell0DsCoordinates(0,idInizio);
		double y1 =mesh.Cell0DsCoordinates(1,idInizio);
		double x2 =mesh.Cell0DsCoordinates(0,idFine);
		double y2 =mesh.Cell0DsCoordinates(1,idFine);
		
		double dist = sqrt(pow((x2-x1),2)+pow((y2-y1),2));
		//cout<<dist<<endl;
		if (dist <= eps_1)
		return false;	
	}
		return true;
}
//nota: è lecito assumere nell'ambito della geometria che i vertici siano ordinati.
// l'ordinamento può essere orario o antiorario, ma grazie al valore assoluto nella formula, è lo stesso
bool test_aree(const PolygonalMesh& mesh){
	const double eps_2 = 10e-16;
	for (unsigned int i=0;i<mesh.NumCell2Ds;i++){
		
		double area =0.0;
		
		for (unsigned int j=0; j<mesh.Cell2DsNumVert[i]; j++){
			unsigned int idPoint=(mesh.Cell2DsVertices[i])[j];
			unsigned int idPointSucc=(mesh.Cell2DsVertices[i])[(j+1)%mesh.Cell2DsNumVert[i]];
			//cout<<j<<" "<<idPoint<<" "<<idPointSucc<<endl;
			double x1 = mesh.Cell0DsCoordinates(0, idPoint);
            double y1 = mesh.Cell0DsCoordinates(1, idPoint);
            double x2 = mesh.Cell0DsCoordinates(0, idPointSucc);
            double y2 = mesh.Cell0DsCoordinates(1, idPointSucc);

            area += x1 * y2 - x2 * y1;
		}
		area = abs(area)/2.0;
		if (area<= eps_2)
			return false;
	}
	return true;
}

bool test_marker(const PolygonalMesh& mesh){
	map<unsigned int, list<unsigned int>> marker_0_corretto = {
		{1,{0}},
		{2,{1}},
		{3,{2}},
		{4,{3}},
		{5,{6,16,24}},
		{6,{7,17,22,78}},
		{7,{8,20,23,52,59}},
		{8,{5,15,21,26,92}},	
	};
	map<unsigned int, list<unsigned int>> marker_1_corretto = {
		{5,{8,19,22,28}},
		{6,{6,23,26,126,127}},
		{7,{14,17,24,79,92,93}},
		{8,{11,25,29,30,159,160}},	
	};
	map<unsigned int, list<unsigned int>> marker_2_corretto = {};
	if (!(mesh.MarkerCell0Ds==marker_0_corretto)){
		cout<<"errore marker 0Ds"<<endl;
		return false;
	}
	if (!(mesh.MarkerCell1Ds==marker_1_corretto)){
		cout<<"errore marker 1Ds"<<endl;
		return false;
	}
	if (!(mesh.MarkerCell2Ds==marker_2_corretto)){
		cout<<"errore marker 2Ds"<<endl;
		return false;
	}
	return true;
}
*/

}
