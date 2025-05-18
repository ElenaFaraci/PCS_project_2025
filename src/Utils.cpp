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
		
		vector<unsigned int> e1 = {0,3,1};
		vector<unsigned int> e2 = {3,5,4};
		vector<unsigned int> e3 = {1,5,2};
		vector<unsigned int> e4 = {0,4,2};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4};
		
		//Cell3Ds
		mesh.Cell3DsId=0; //caso tetraedro
		
		mesh.Cell3DsNumVert = mesh.NumCell0Ds;
		mesh.Cell3DsNumEdg = mesh.NumCell1Ds;
		mesh.Cell3DsNumFaces = mesh.NumCell2Ds;
		
		mesh.Cell3DsVertices = mesh.Cell0DsId; //costruttore di copia? 
		mesh.Cell3DsEdges = mesh.Cell1DsId;
		mesh.Cell3DsFaces = mesh.Cell2DsId;
		
		
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
		vector<unsigned int> e3 = {2,9,3};
		vector<unsigned int> e4 = {0,5,3};
		vector<unsigned int> e5 = {6,4,8};
		vector<unsigned int> e6 = {8,7,10};
		vector<unsigned int> e7 = {10,9,11};
		vector<unsigned int> e8 = {5,11,6};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4, e5, e6, e7, e8};
		
		//Cell3D
		
		vector<unsigned int> Cell3DsNumVert = {6};
		vector<unsigned int> Cell3DsNumEdg = {12};
		vector<unsigned int> Cell3DsNumFaces = {8};
	
		vector<unsigned int> Cell3DsVertices = {0, 1, 2, 3, 4, 5};
		vector<unsigned int> Cell3DsEdges = {0,1,2,3,4,5,6,7,8,9,10,11};
		vector<unsigned int> Cell3DsFaces = {0, 1 ,2, 3, 4, 5, 6, 7};
		}
		
		
		
	else if (q==5){
		//Cell0Ds
		mesh.NumCell0Ds=12;
		mesh.Cell0DsId = {0,1,2,3,4,5,6,7,8,9,10,11}; // è efficiente? reserve?
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
		double phi = (1+sqrt(5))/2;
		double A = 1/(sqrt(1+pow(phi,2)));
		double B = phi/(sqrt(1+pow(phi,2)));
		
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
		
		vector<unsigned int> e1 = {1,19,3};
		vector<unsigned int> e2 = {0,10,1};
		vector<unsigned int> e3 = {10,20,13};
		vector<unsigned int> e4 = {18,25,20};
		vector<unsigned int> e5 = {18,24,19};
		vector<unsigned int> e6 = {5,15,7};
		vector<unsigned int> e7 = {7,25,9};
		vector<unsigned int> e8 = {15,24,16};
		vector<unsigned int> e9 = {16,28,17};
		vector<unsigned int> e10 = {3,28,4};
		vector<unsigned int> e11 = {2,27,4};
		vector<unsigned int> e12 = {11,26,12};
		vector<unsigned int> e13 = {12,29,13};
		vector<unsigned int> e14 = {8,29,9};
		vector<unsigned int> e15 = {6,22,8};
		vector<unsigned int> e16 = {21,26,22};
		vector<unsigned int> e17 = {5,14,6};
		vector<unsigned int> e18 = {14,23,17};
		vector<unsigned int> e19 = {21,27,23};
		vector<unsigned int> e20 = {0,11,4};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20};
		
		//Cell3D
		
		vector<unsigned int> Cell3DsNumVert = {12};
		vector<unsigned int> Cell3DsNumEdg = {30};
		vector<unsigned int> Cell3DsNumFaces = {20};
	
		vector<unsigned int> Cell3DsVertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
		vector<unsigned int> Cell3DsEdges = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};
		vector<unsigned int> Cell3DsFaces = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
		}
		
		
		
	else{
		cerr<<"valore di q non valido"<<endl;
		return false;
	}
	return true;
	
}


bool controllo_lati_vertici (const PolygonalMesh& mesh){
	for (unsigned int i=0; i<mesh.NumCell2Ds; i++){
		//for (unsigned int j=0; j<(mesh.Cell2DsEdges[i]).size(); j++){
		for (unsigned int j=0; j<3; j++){
			
			unsigned int id_vertice = mesh.Cell2DsVertices[i][j];
			unsigned int id_lato=mesh.Cell2DsEdges[i][j];
			//unsigned int id_lato_succ=mesh.Cell2DsEdges[i][(j+1)%(mesh.Cell2DsEdges[i]).size()];
			unsigned int id_lato_succ=mesh.Cell2DsEdges[i][(j+1)%3];
			unsigned int count =0;
			
			//Controllo Lati
			if (mesh.Cell1DsExtrema(0,id_lato)==mesh.Cell1DsExtrema(0,id_lato_succ))
				count++;
			if (mesh.Cell1DsExtrema(0,id_lato)==mesh.Cell1DsExtrema(1,id_lato_succ))
				count++;
			if (mesh.Cell1DsExtrema(1,id_lato)==mesh.Cell1DsExtrema(0,id_lato_succ))
				count++;
			if (mesh.Cell1DsExtrema(1,id_lato)==mesh.Cell1DsExtrema(1,id_lato_succ))
				count++;
			
			if (count != 1){
				cout<<"lati: "<<count<<" i: "<<i<<" j: "<<j<<endl;
				
				return false;
			}
			
			// Controllo Vertici
			if (id_vertice == mesh.Cell1DsExtrema(0,id_lato))
				count++;
			if (id_vertice == mesh.Cell1DsExtrema(1,id_lato))
				count++;
			
			if (count != 2){
				cout<<"vertici: "<<count<<" i: "<<i<<" j: "<<j<<endl;
				return false;
			}
			
		}
			
	}
	return true;
}





}
