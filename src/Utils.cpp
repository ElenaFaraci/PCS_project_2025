#include "Utils.hpp"
#include "PolygonalMesh.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Eigen/Eigen"
#include <numeric>
#include <queue>
#include <unordered_set>

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
bool valorizza_poliedro(unsigned int q, PolygonalMesh& mesh){
	
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
		
		mesh.Cell3DsId=0;
		mesh.Cell3DsNumVert = 6;
		mesh.Cell3DsNumEdg = 12;
		mesh.Cell3DsNumFaces = 8;
	
		mesh.Cell3DsVertices = {0, 1, 2, 3, 4, 5};
		mesh.Cell3DsEdges = {0,1,2,3,4,5,6,7,8,9,10,11};
		mesh.Cell3DsFaces = {0, 1 ,2, 3, 4, 5, 6, 7};
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
		vector<unsigned int> e20 = {0,11,2};
		
		mesh.Cell2DsEdges = {e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20};
		
		//Cell3D
		
		mesh.Cell3DsId=0;
		mesh.Cell3DsNumVert = 12;
		mesh.Cell3DsNumEdg = 30;
		mesh.Cell3DsNumFaces = 20;
	
		mesh.Cell3DsVertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
		mesh.Cell3DsEdges = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};
		mesh.Cell3DsFaces = {0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
		}
		
		
		
	else{
		cerr<<"valore non valido"<<endl;
		return false;
	}
	return true;
	
}
bool converti_uns_int(const char* str, unsigned int& numero_conv){
	istringstream iss(str);
	int temp;
    if ((iss >> temp) && iss.eof() && temp >= 0) {
        numero_conv = static_cast<unsigned int>(temp);
        return true;
    }
    return false;
}


bool controllo_lati_vertici (const PolygonalMesh& mesh){
	for (unsigned int i=0; i<mesh.NumCell2Ds; i++){
		
		for (unsigned int j = 0; j<(mesh.Cell2DsEdges[i]).size(); j++){
			
			unsigned int id_vertice = mesh.Cell2DsVertices[i][j];
			unsigned int id_lato = mesh.Cell2DsEdges[i][j];
			unsigned int id_lato_succ=mesh.Cell2DsEdges[i][(j+1)%(mesh.Cell2DsEdges[i]).size()];
			
			unsigned int count = 0;
			
			//Controllo Lati
			if (mesh.Cell1DsExtrema(0, id_lato) == mesh.Cell1DsExtrema(0, id_lato_succ))
                count++;
            if (mesh.Cell1DsExtrema(0, id_lato) == mesh.Cell1DsExtrema(1, id_lato_succ))
                count++;
            if (mesh.Cell1DsExtrema(1, id_lato) == mesh.Cell1DsExtrema(0, id_lato_succ))
                count++;
            if (mesh.Cell1DsExtrema(1, id_lato) == mesh.Cell1DsExtrema(1, id_lato_succ))
                count++;

            if (count != 1) {
                cout << "Errore nei lati: count = " << count << " i = " << i << " j = " << j << std::endl;
                return false;
            }

			
			
			// Controllo Vertici
			count = 0;
            if (id_vertice == mesh.Cell1DsExtrema(0, id_lato))
                count++;
            if (id_vertice == mesh.Cell1DsExtrema(1, id_lato))
                count++;

            if (count != 1) {
                std::cout << "Errore nei vertici: count = " << count << " i = " << i << " j = " << j << std::endl;
                return false;
            }
			
		}
			
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Prove triangolazione
string ArrayToString(const size_t& n, const double* const& v)
{
    string str;
    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString<< v[i]<< " ";
    toString << "]";

    return toString.str();
}
Eigen::VectorXd Nuovo_Vertice(unsigned int id1, unsigned int id2, unsigned int b, unsigned int step, const PolygonalMesh& mesh){
	Eigen::Vector3d vertex1 = mesh.Cell0DsCoordinates.col(id1);
	Eigen::Vector3d vertex2 = mesh.Cell0DsCoordinates.col(id2);
	
	if ((vertex2 - vertex1).norm() < 1e-10) {
        cerr << "Attenzione: vertex1 e vertex2 coincidono, non si può interpolare" << endl;
        return vertex1;
    }
	Eigen::Vector3d new_vertex = (vertex2 - vertex1) * ((double)step/b) + vertex1;
	//cout << "Coordinate del nuovo vertice: " << new_vertex.transpose() << endl;
    return new_vertex;
}


int Esiste_gia(PolygonalMesh& mesh, const Eigen::Vector3d& nuovo_vertice, unsigned int k) {				   
	double epsilon = 1e-10;
    for (int i = 0; i < k; ++i) {
        if ((mesh.Cell0DsCoordinates.col(i) - nuovo_vertice).norm() < epsilon) {
            return i; // vertice esistente trovato
        }
    }
    return -1; // non trovato
}



bool Triangolazione(PolygonalMesh& mesh, unsigned int b, unsigned int c, unsigned int q){
	unsigned int T = b*b+b*c+c*c;
	unsigned int V = 0;
	if (q==3){
		V=2*T+2;
	} else if (q==4){
		V=4*T+2;
	} else if (q==5){
		V=10*T+2;
	}
	
	if (b==0){
		b=c;
	}
	
	unsigned int k = mesh.NumCell0Ds;	
	unsigned int num_facc_pre =mesh.NumCell2Ds;
	
	//creo un vettore punti_faccia che contenga i vertici, nuovi e vecchi, di ciascuna faccia
	unsigned int num_nuovi_per_faccia=((b+1)*(b+2))/2;
	unsigned int n=num_nuovi_per_faccia*num_facc_pre;
	vector<int> punti_faccia;
	punti_faccia.reserve(n);
	
	// resize della matrice che ospiterà anche i nuovi vertici
	mesh.Cell0DsCoordinates.conservativeResize(3, V);
	
	// iterazione sulle facce
	for(unsigned int j = 0; j < mesh.NumCell2Ds; j ++){
		
		unsigned int x0 = mesh.Cell2DsVertices[j][0];
		unsigned int y0 = mesh.Cell2DsVertices[j][1];
		unsigned int z0 = mesh.Cell2DsVertices[j][2];
		
		//cout << "i vertici della faccia: "<<j<<" sono: "<<x0<<" "<<y0<<" "<<z0<<" "<<endl;
		
		unsigned int x = x0;
		unsigned int y = y0;
		unsigned int z = z0;
		
		// per ogni faccia srotolo i punti su punti_faccia a partire dal primo vertice
		punti_faccia.push_back(x0);  
		
		unsigned int num_suddivisioni = b;
		
		//iterazione sui piani
		for(unsigned int w = 0; w < b-1; w++){
			
			//per ogni piano creo i vertici
			for(unsigned int i = 0; i < num_suddivisioni -1; i++) {
				
				//se un punto che sto creando, esiste già, allora aggiungerò il suo 
				//id al vettore punti_faccia e nulla alla matrice Cell0DsCoordinates
				//se invece il vertice è nuovo, gli assegno l'id successivo all'ultimo creato
				//e poi lo aggiungo a Cell0DsCoordinates (coordinate) e punti_faccia (id)
				
				Eigen::Vector3d nuovo_vertice = Nuovo_Vertice(x, y, num_suddivisioni, i + 1, mesh);
				int id=Esiste_gia(mesh, nuovo_vertice, k);
				if (id==-1){
					mesh.Cell0DsCoordinates.col(k) = nuovo_vertice;
					mesh.Cell0DsId.push_back(k);
					punti_faccia.push_back(k);
					k ++;
				}else{
					punti_faccia.push_back(Esiste_gia(mesh, nuovo_vertice, k));
				}
								
			}
			num_suddivisioni --;
			
			//aggiungo al vettore la fine del piano appena concluso
			punti_faccia.push_back(y);
			
			//creo inizio e fine del piano successivo
			Eigen::Vector3d nuovo_vertice= Nuovo_Vertice(x0, z0, b, w + 1, mesh);
			
			int id = Esiste_gia(mesh, nuovo_vertice, k);
			//se il nuovo vertice non esiste, lo aggiungo, altrimenti uso quello già fatto
			if (id==-1){
					mesh.Cell0DsCoordinates.col(k) = nuovo_vertice;
					mesh.Cell0DsId.push_back(k);
					x=k;
					punti_faccia.push_back(k);
					k ++;
			} else{
				x=id;
				punti_faccia.push_back(id);
			}
			
			// il vertice che aggiungo quì sotto, non va messo nel punti_faccia ora
			// perchè si trova alla fine del suo piano
			nuovo_vertice = Nuovo_Vertice(y0, z0, b, w + 1, mesh);
			id=Esiste_gia(mesh, nuovo_vertice, k);
			if (id==-1){
					mesh.Cell0DsCoordinates.col(k) = nuovo_vertice;
					mesh.Cell0DsId.push_back(k);
					y=k;
					k ++;
			} else{
				y=id;
			}
		}
		
	//ho finito la faccia e sono pronto ad iniziare la successiva, ma macano
	// da aggiungere a punti_faccia l'ultimo punto dell'ultimo strato e il vertice finale (sommità del triangolo)
	punti_faccia.push_back(y);
	punti_faccia.push_back(z0);	
	
	}
	
	// posso aggiornare ora mesh.NumCell0Ds
	mesh.NumCell0Ds=k;
	mesh.Cell3DsNumVert=k;
	mesh.Cell3DsVertices.resize(k);
	iota(mesh.Cell3DsVertices.begin(), mesh.Cell3DsVertices.end(), 0);
	
	//di seguito andrò a creare le nuove facce e lati
	
	tri_vertici_facce(mesh, b, punti_faccia, num_facc_pre, num_nuovi_per_faccia);
	tri_lati_facce(mesh, b, num_facc_pre);
	
	
	return true;
}

void tri_vertici_facce(PolygonalMesh& mesh, unsigned int b, vector<int> punti_faccia,
					   unsigned int num_facc_pre, unsigned int num_nuovi_per_faccia){
	
	//creo le nuove facce, perciò mi dimentico di quelle vecchie	
	mesh.Cell2DsVertices={};
	mesh.Cell2DsVertices.reserve(num_facc_pre*b*b);
	
	//riparto da capo anche con gli id
	mesh.Cell2DsId ={};
	mesh.Cell2DsId.reserve(num_facc_pre*b*b);
	
	mesh.Cell3DsFaces ={};
	mesh.Cell3DsFaces.reserve(num_facc_pre*b*b);
	
	unsigned int count=0; //variabile invrementale che aggiornerà gli id
	
	// nel vettore punti_faccia i punti appartenenti ad una certa faccia iniziano con un 
	// offset pari al numero di punti nelle facce precedenti
	unsigned int offset_faccia = 0;
	
	//ciclo sulle facce
	for (unsigned int j = 0; j < num_facc_pre; j++) {
		vector<unsigned int> inizio_strato(b + 1);
		unsigned int pos = offset_faccia;
		
		// inizio_strato mi dice l'indirizzo di partenza di ciascuno strato
		for (unsigned int r = 0; r <= b; r++) {
			inizio_strato[r] = pos;
			pos += b - r + 1;
		}

		//selezione gli indirizzi di partenza di due strati consecutivi
		for (unsigned int r = 0; r < b; r++) {
			unsigned int base_r = inizio_strato[r];
			unsigned int base_r1 = inizio_strato[r + 1];
			unsigned int len_r = b - r + 1;
			
			// creo i triangoli
			for (unsigned int k = 0; k < len_r - 1; k++) {
				unsigned int a  = punti_faccia[base_r + k];
				unsigned int b_ = punti_faccia[base_r + k + 1];
				unsigned int c  = punti_faccia[base_r1 + k];
				unsigned int d  = punti_faccia[base_r1 + k + 1];

				// Triangolo 1
				mesh.Cell2DsVertices.push_back({a, b_, c});
				mesh.Cell3DsFaces.push_back(count);
				mesh.Cell2DsId.push_back(count++);
				

				// Triangolo 2, solo se non siamo all'ultimo k (serve d)
				if (k < len_r - 2) {
					mesh.Cell2DsVertices.push_back({b_, d, c});
					mesh.Cell3DsFaces.push_back(count);
					mesh.Cell2DsId.push_back(count++);
					
				}
			}
		}
		
		//incremento l'offset dei vertici aggiunti
		offset_faccia += num_nuovi_per_faccia;
	}

	//posso aggiornare le informazioni della mesh riguardanti Cell2D
	mesh.NumCell2Ds=num_facc_pre*b*b;	
	mesh.Cell2DsNumVert.assign(num_facc_pre*b*b,3);
	mesh.Cell2DsNumEdg.assign(num_facc_pre*b*b,3);
	
	mesh.Cell3DsNumFaces=num_facc_pre*b*b;
	
}


int esiste_gia_1D(int point_1, int point_2, const PolygonalMesh& mesh) {
    
	int p1 = min(point_1, point_2);
    int p2 = max(point_1, point_2);

    for (int i = 0; i < mesh.Cell1DsExtrema.cols(); i++) {
        int q1 = mesh.Cell1DsExtrema(0, i);
        int q2 = mesh.Cell1DsExtrema(1, i);
        if ((p1 == min(q1, q2)) && (p2 == max(q1, q2))) {
            return i; 
        }
    }

    return -1; 
}


void tri_lati_facce(PolygonalMesh& mesh, unsigned int b,unsigned int num_facc_pre){
	
	unsigned int num_lati=num_facc_pre*3*b*(b+1)/2 -b*mesh.NumCell1Ds; 
	// siginificato del conto sopra: b*(b+1)/2 = b + (b-1) + (b-2) + ... che è il numero di lati creati salendo 
	// di piano in piano, moltiplico per 3: i tre lati del triangolo originale sono le direzioni dei piani
	// moltiplico per num_facc_pre. tolgo i lati creati sugli spiagoli del solido originale, che ho contato 2 vote
	mesh.Cell2DsEdges = {};
	mesh.Cell2DsEdges.reserve(mesh.Cell2DsVertices.size());
	
	mesh.Cell1DsId ={};
	mesh.Cell1DsId.reserve(num_lati);
	
	mesh.Cell1DsExtrema.resize(2, num_lati);
	unsigned int k=0;
	for (unsigned int j=0;j<mesh.Cell2DsVertices.size();j++){
		vector<unsigned int> v={};
		v.reserve(3);
		for (unsigned int i=0;i<3;i++){
			unsigned int point_1 = mesh.Cell2DsVertices[j][i];
			unsigned int point_2 = mesh.Cell2DsVertices[j][(i+1)%3];
			
			int id_l=esiste_gia_1D(point_1, point_2, mesh);
			if (id_l==-1){
				// il lato è nuovo
				Vector2i new_l(point_1,point_2);
				mesh.Cell1DsExtrema.col(k)=new_l;
				mesh.Cell1DsId.push_back(k);
				v.push_back(k);
				k++;
				// ma devo aggiungere anche gli id dei lati
			} else{
				// il lato esiste già 
				v.push_back(id_l);
			}
			
		}
		mesh.Cell2DsEdges.push_back(v);
	}
	
	mesh.NumCell1Ds=num_lati;
	mesh.Cell3DsNumEdg=num_lati;
	
	mesh.Cell3DsEdges.resize(num_lati);
	iota(mesh.Cell3DsEdges.begin(), mesh.Cell3DsEdges.end(), 0);
	
	
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
bool triangolazione_2(PolygonalMesh& mesh_2, unsigned int b, unsigned int q){
	
	unsigned int num_facc;
	unsigned int num_lati;
	if (q==3){
		num_facc=4;
		num_lati = 6;
	} else if (q==4){
		num_facc=8;
		num_lati = 12;
	} else if (q==5){
		num_facc=20;
		num_lati = 30;
	}
	// Per effettuare la triangolazione di classe II, sfrutto il poliedro di partenza (3, q, 0, 0) e la sua triangolazione di classe I di parametri (3, q, b, 0). Ricavo inizialmente tutti i vertici che otterrò (dalla triangolazione di classe II) sui lati del poliedro, e li salvo nella matrice matr_vert_lati.
	PolygonalMesh poliedro = mesh_2;
	PolygonalMesh mesh = mesh_2;
	bool stato1 = Triangolazione(mesh, b, 0, q);
	if(!stato1){
		cout<<"errore chiamata triangolazione in triangolazione_2"<<endl;
	}
	info_mesh(mesh_2);
	unsigned int numero_vert_su_lati = poliedro.NumCell0Ds + poliedro.NumCell1Ds*(2*b-1);
	MatrixXd matr_vert_lati = MatrixXd::Zero(3,numero_vert_su_lati);
	unsigned int count=0;
	for (unsigned int j = 0; j < poliedro.NumCell0Ds; j++){
		Vector3d vertice = poliedro.Cell0DsCoordinates.col(j);
		matr_vert_lati.col(count)=vertice;
		count ++;
		}
	for (unsigned int i=0;i<poliedro.NumCell1Ds;i++){
		unsigned int p_1=poliedro.Cell1DsExtrema(0,i);
		unsigned int p_2=poliedro.Cell1DsExtrema(1,i);
		for (unsigned int k=1; k<2*b;k++){
			Vector3d nuovo_vert=Nuovo_Vertice(p_1, p_2, 2*b, k, poliedro);
			matr_vert_lati.col(count)=nuovo_vert;
			count ++;
		}
	}
	// Inizializzo mesh_2, che conterrà la seconda triangolazione
	// Cell0Ds

	unsigned int num_vertices = mesh.NumCell0Ds + num_lati * b + mesh.NumCell2Ds;
	mesh_2.NumCell0Ds = num_vertices;
	
	mesh_2.Cell0DsId = {};
	mesh_2.Cell0DsId.reserve(num_vertices);
	for (unsigned int i = 0; i< num_vertices; i++){
		mesh_2.Cell0DsId.push_back(i);
		}
	mesh_2.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh_2.NumCell0Ds);

	// Cell1Ds
	mesh_2.NumCell1Ds = num_lati*2*b+(6*b*b-(b-1)*b/2*3)*num_facc;

	mesh_2.Cell1DsId = {};
	mesh_2.Cell1DsId.reserve(mesh_2.NumCell1Ds);
	for (unsigned int i = 0; i< mesh_2.NumCell1Ds; i++){
		mesh_2.Cell1DsId.push_back(i);
		}
	
	mesh_2.Cell1DsExtrema = Eigen::MatrixXi(2, mesh_2.NumCell1Ds);
	
	//Cell2Ds
	unsigned int F = num_facc*6*(b*b+b)/2;
	mesh_2.NumCell2Ds = F;
	
	mesh_2.Cell2DsId={};
	mesh_2.Cell2DsId.reserve(F);
	for (unsigned int i = 0; i< F; i++){
		mesh_2.Cell2DsId.push_back(i);
		}

	mesh_2.Cell2DsNumVert.assign(F,3);
	mesh_2.Cell2DsNumEdg.assign(F,3);
	
	mesh_2.Cell2DsVertices={};
	mesh_2.Cell2DsVertices.reserve(mesh.NumCell2Ds);
	mesh_2.Cell2DsEdges={};
	mesh_2.Cell2DsEdges.reserve(mesh.NumCell2Ds);
	
	// creo una matrice che abbia, come colonne, le componenti (x,y,z) dei baricentri delle facce di mesh.

	MatrixXd matr_bar_facce = MatrixXd::Zero(3,mesh.NumCell2Ds); 
	for (unsigned int i = 0; i < mesh.NumCell2Ds; i++) {
		Vector3d nuovo_bar = baricentro(mesh.Cell2DsVertices[i], mesh);
		matr_bar_facce.col(i)=nuovo_bar;
	}

	// Adesso itero sulle facce del poliedro, e per ogni faccia itero sui triangoli in mesh che fanno parte di questa, aggiungendo vertici, lati e facce a mesh_2.
	unsigned int v_count = 0;
	unsigned int l_count = 0;
	for (unsigned int i=0;i<num_facc;i++){ // itero sulle facce del poliedro
		// Creo delle strutture in cui salverò i vertici dei lati presenti in mesh che non sono parte di mesh_2, e il baricentro del triangolo di cui fanno parte
		VectorXd baricentri_faccia_grande = VectorXd::Zero((b-1)*b*3);
		MatrixXd estremi_lato_baricentro = MatrixXd::Zero(2, (b-1)*b*3);
		unsigned int bar_count = 0;
		// Con l'indice k itero sulle facce di mesh, salvando i vertici con i nuovi id in mesh_2. Successivamente, calcolo le coordinate dei tre punti medi dei vertici e il baricentro. Salvo quest'ultimo in mesh_2 e creo i lati tra vertici e baricentro.
		for (unsigned int k=0;k<b*b;k++){
			
			unsigned int v_1= mesh.Cell2DsVertices[i*b*b+k][0];
			unsigned int v_2= mesh.Cell2DsVertices[i*b*b+k][1];
			unsigned int v_3= mesh.Cell2DsVertices[i*b*b+k][2];
			Vector3d coord_v1 = mesh.Cell0DsCoordinates.col(v_1);

			int id_v1 = Esiste_gia(mesh_2, coord_v1, v_count);
			if (id_v1 == -1){
				id_v1 = v_count;
				mesh_2.Cell0DsCoordinates.col(v_count) = coord_v1;
				v_count ++;
				}

			Vector3d coord_v2 = mesh.Cell0DsCoordinates.col(v_2);

			int id_v2 = Esiste_gia(mesh_2, coord_v2, v_count);
			if (id_v2 == -1){
				id_v2 = v_count;
				mesh_2.Cell0DsCoordinates.col(v_count) = coord_v2;
				v_count ++;
				}
				
			Vector3d coord_v3 = mesh.Cell0DsCoordinates.col(v_3);

			int id_v3 = Esiste_gia(mesh_2, coord_v3, v_count);
			if (id_v3 == -1){
				id_v3 = v_count;
				mesh_2.Cell0DsCoordinates.col(v_count) = coord_v3;
				v_count ++;
				}

			Vector3d m_1 = Nuovo_Vertice(id_v1, id_v2, 2, 1, mesh_2);
			Vector3d m_2 = Nuovo_Vertice(id_v1, id_v3, 2, 1, mesh_2);
			Vector3d m_3 = Nuovo_Vertice(id_v2, id_v3, 2, 1, mesh_2);
			Vector3d baricentro_corrente = matr_bar_facce.col(i*b*b+k); 
			unsigned int id_bar_corrente = v_count;
			mesh_2.Cell0DsCoordinates.col(v_count++)=baricentro_corrente;

			int id_v1_b = esiste_gia_1D(id_v1, id_bar_corrente, mesh_2);
			if (id_v1_b == -1){
				id_v1_b = l_count;
				mesh_2.Cell1DsExtrema.col(l_count) << id_v1, id_bar_corrente;
				l_count ++;
				}
			int id_v2_b = esiste_gia_1D(id_v2, id_bar_corrente, mesh_2);
			if (id_v2_b == -1){
				id_v2_b = l_count;
				mesh_2.Cell1DsExtrema.col(l_count) << id_v2, id_bar_corrente;
				l_count ++;
				}
			int id_v3_b = esiste_gia_1D(id_v3, id_bar_corrente, mesh_2);
			if (id_v3_b == -1){
				id_v3_b = l_count;
				mesh_2.Cell1DsExtrema.col(l_count) << id_v3, id_bar_corrente;
				l_count ++;
				}
			// Inizializzo tre valori booleani, uno per ogni punto medio, per verificare se esistono (o meno) in mesh_2, confrontandoli con i vertici in matr_vert_lati.
			
			bool check_m1 = false;
			bool check_m2 = false;
			bool check_m3 = false;

			for(unsigned int j=0;j<numero_vert_su_lati;j++){ 
				// Controllo su m_1
				if ((matr_vert_lati.col(j) - m_1).norm() < 1e-10){
					// Se trovo una corrispondenza con i vertici salvati in matr_vert_lati, salvo il punto medio, i lati che forma con i vertici e con il baricentro e le due facce che si formano.
					int id = Esiste_gia(mesh_2, m_1, v_count);
					if (id == -1){
						id = v_count;
						mesh_2.Cell0DsCoordinates.col(v_count) = m_1;
						v_count ++;
						}
					unsigned int id_m_1 = id;
					
					int l_m1_v1 = esiste_gia_1D(id_m_1, id_v1, mesh_2);
					if (l_m1_v1 == -1){
						l_m1_v1 = l_count;
						mesh_2.Cell1DsExtrema.col(l_count) << id_m_1, id_v1;
						l_count ++;
						}
						
					int l_m1_v2 = esiste_gia_1D(id_m_1, id_v2, mesh_2);
					if (l_m1_v2 == -1){
						l_m1_v2 = l_count;
						mesh_2.Cell1DsExtrema.col(l_count) << id_m_1, id_v2;
						l_count ++;
						}
					
					mesh_2.Cell1DsExtrema.col(l_count) << id_m_1, id_bar_corrente;

					mesh_2.Cell2DsVertices.push_back({static_cast<unsigned int>(id_bar_corrente), static_cast<unsigned int>(id_v1), static_cast<unsigned int>(id_m_1)});
					mesh_2.Cell2DsVertices.push_back({static_cast<unsigned int>(id_m_1), static_cast<unsigned int>(id_v2), static_cast<unsigned int>(id_bar_corrente)});
					
					mesh_2.Cell2DsEdges.push_back({static_cast<unsigned int>(id_v1_b), static_cast<unsigned int>(l_m1_v1), l_count});
					mesh_2.Cell2DsEdges.push_back({static_cast<unsigned int>(l_m1_v2), static_cast<unsigned int>(id_v2_b), l_count});
					
					l_count ++;
					check_m1 = true;
					
					}
					
				// controllo su m_2, analogo a m_1.
				if ((matr_vert_lati.col(j) - m_2).norm() < 1e-10){
					int id_m_2 = Esiste_gia(mesh_2, m_2, v_count);
					if (id_m_2 == -1){
						id_m_2 = v_count;
						mesh_2.Cell0DsCoordinates.col(v_count) = m_2;
						v_count ++;
						}
						
					int l_m2_v1 = esiste_gia_1D(id_m_2, id_v1, mesh_2);
					if (l_m2_v1 == -1){
						l_m2_v1 = l_count;
						mesh_2.Cell1DsExtrema.col(l_count) << id_m_2, id_v1;
						l_count ++;
						}
						
					int l_m2_v3 = esiste_gia_1D(id_m_2, id_v3, mesh_2);
					if (l_m2_v3 == -1){
						l_m2_v3 = l_count;
						mesh_2.Cell1DsExtrema.col(l_count) << id_m_2, id_v3;
						l_count ++;
						}

					mesh_2.Cell1DsExtrema.col(l_count) << id_m_2, id_bar_corrente;
					
					mesh_2.Cell2DsVertices.push_back({static_cast<unsigned int>(id_bar_corrente), static_cast<unsigned int>(id_v1), static_cast<unsigned int>(id_m_2)});
					mesh_2.Cell2DsVertices.push_back({static_cast<unsigned int>(id_m_2), static_cast<unsigned int>(id_v3), static_cast<unsigned int>(id_bar_corrente)});
					
					mesh_2.Cell2DsEdges.push_back({static_cast<unsigned int>(id_v1_b), static_cast<unsigned int>(l_m2_v1), l_count});
					mesh_2.Cell2DsEdges.push_back({static_cast<unsigned int>(l_m2_v3), static_cast<unsigned int>(id_v3_b), l_count});

					l_count ++;
					check_m2 = true;
					
					}

				// controllo su m_3, analogo a m_1.
				if ((matr_vert_lati.col(j) - m_3).norm() < 1e-10){
					int id_m_3 = Esiste_gia(mesh_2, m_3, v_count);
					if (id_m_3 == -1){
						id_m_3 = v_count;
						mesh_2.Cell0DsCoordinates.col(v_count) = m_3;
						v_count ++;
						}
					
					int l_m3_v3 = esiste_gia_1D(id_m_3, id_v3, mesh_2);
					if (l_m3_v3 == -1){
						l_m3_v3 = l_count;
						mesh_2.Cell1DsExtrema.col(l_count) << id_m_3, id_v3;
						l_count ++;
						}
						
					int l_m3_v2 = esiste_gia_1D(id_m_3, id_v2, mesh_2);
					if (l_m3_v2 == -1){
						l_m3_v2 = l_count;
						mesh_2.Cell1DsExtrema.col(l_count) << id_m_3, id_v2;
						l_count ++;
						}
					
					mesh_2.Cell1DsExtrema.col(l_count) << id_m_3, id_bar_corrente;
					
					mesh_2.Cell2DsVertices.push_back({static_cast<unsigned int>(id_bar_corrente), static_cast<unsigned int>(id_v3), static_cast<unsigned int>(id_m_3)});
					mesh_2.Cell2DsVertices.push_back({static_cast<unsigned int>(id_m_3), static_cast<unsigned int>(id_v2), static_cast<unsigned int>(id_bar_corrente)});
					
					mesh_2.Cell2DsEdges.push_back({static_cast<unsigned int>(id_v3_b), static_cast<unsigned int>(l_m3_v3), l_count});
					mesh_2.Cell2DsEdges.push_back({static_cast<unsigned int>(l_m3_v2), static_cast<unsigned int>(id_v2_b), l_count});

					l_count ++;
					check_m3 = true;

					}
			}
			// Fuori dal ciclo, se non c'è stata corrispondenza per i punti medi, salvo il baricentro e gli id dei vertici del lato che contiene il punto medio. In questo caso, andrò a creare i lati tra baricentri di triangoli adiacenti e le relative facce con i vertici.
			if (check_m1 == false){
				baricentri_faccia_grande[bar_count] = id_bar_corrente;
				estremi_lato_baricentro.col(bar_count) << id_v1, id_v2;
				bar_count ++;
				}
			if (check_m2 == false){
				baricentri_faccia_grande[bar_count] = id_bar_corrente;
				estremi_lato_baricentro.col(bar_count) << id_v1, id_v3;
				bar_count ++;
				}
			if (check_m3 == false){
				baricentri_faccia_grande[bar_count] = id_bar_corrente;
				estremi_lato_baricentro.col(bar_count) << id_v2, id_v3;
				bar_count ++;
				}
		}
		// Adesso itero su baricentri_faccia_grande e estremi_lato_baricentro. Il primo contiene gli id dei baricentri dei triangoli per cui non esistevano i punti medi. Se, per esempio, per il triangolo k non esiste nessun punto medio, salvo tre volte l'id del baricentro k-esimo. La matrice, invece, contiene gli id dei vertici del lato per cui non esiste il punto medio.
		// Operativamente, scorro le colonne della matrice cercando per quali baricentri corrispondono vertici uguali (cioè i corrispettivi triangoli sono adiacenti lungo il lato con estremi i vertici), creo un lato tra i baricentri e le due facce che questo lato forma con i vertici.
		VectorXd indici_visitati = VectorXd::Zero(b*(b-1)*3);
		if (b != 1){
			for (unsigned int i_=0; i_<(b-1)*b*3-1; i_++){
				if (indici_visitati[i_]==0){
					unsigned int bar_i = baricentri_faccia_grande[i_];
					unsigned int v_1 = estremi_lato_baricentro(0, i_);
					unsigned int v_2 = estremi_lato_baricentro(1, i_);
					unsigned int v1_i = min(v_1, v_2);
					unsigned int v2_i= max(v_1, v_2);
					for (unsigned int j_=1; j_<(b-1)*b*3; j_++){
						if (indici_visitati[j_]==0){
							unsigned int bar_j = baricentri_faccia_grande[j_];
							if (bar_j != bar_i){
								unsigned int v_1_ = estremi_lato_baricentro(0, j_);
								unsigned int v_2_ = estremi_lato_baricentro(1, j_);
								unsigned int v1_j = min(v_1_, v_2_);
								unsigned int v2_j = max(v_1_, v_2_);
								if (v1_i == v1_j){
									if (v2_i == v2_j){
										indici_visitati[j_] = 1;
										mesh_2.Cell1DsExtrema.col(l_count) << bar_i, bar_j; 
										
										// creo triangolo con v1 e i due baricentri, prima recupero gli id dei lati
										int l_v1_bi = esiste_gia_1D(v1_i, bar_i, mesh_2);
										int l_v1_bj = esiste_gia_1D(v1_i, bar_j, mesh_2);
										if (l_v1_bi == -1){
											cerr << "Errore, lato non trovato" << endl;
											}
										if (l_v1_bj == -1){
											cerr << "Errore, lato non trovato" << endl;
											}
										mesh_2.Cell2DsVertices.push_back({bar_i, v1_i, bar_j});
										mesh_2.Cell2DsEdges.push_back({static_cast<unsigned int>(l_v1_bi), static_cast<unsigned int>(l_v1_bj), l_count});
	
										// creo triangolo con v2 e i due baricentri, prima recupero gli id dei lati
										int l_v2_bi = esiste_gia_1D(v2_i, bar_i, mesh_2);
										int l_v2_bj = esiste_gia_1D(v2_i, bar_j, mesh_2);
										if (l_v2_bi == -1){
											cerr << "Errore, lato non trovato" << endl;
											}
										if (l_v2_bj == -1){
											cerr << "Errore, lato non trovato" << endl;
											}
										mesh_2.Cell2DsVertices.push_back({bar_i, v2_i, bar_j});
										mesh_2.Cell2DsEdges.push_back({static_cast<unsigned int>(l_v2_bi), static_cast<unsigned int>(l_v2_bj), l_count});
										l_count ++;
										
										}
									}
								}
							}
						}
					}
				}
		}
	}

	// Infine aggiorno Cell3Ds in mesh_2
	mesh_2.Cell3DsNumVert = mesh_2.NumCell0Ds;
	mesh_2.Cell3DsNumEdg = mesh_2.NumCell1Ds;
	mesh_2.Cell3DsNumFaces = mesh_2.NumCell2Ds;
	
	mesh_2.Cell3DsVertices.resize(mesh_2.NumCell0Ds);
	iota(mesh_2.Cell3DsVertices.begin(), mesh_2.Cell3DsVertices.end(), 0);
	
	mesh_2.Cell3DsEdges.resize(mesh_2.NumCell1Ds);
	iota(mesh_2.Cell3DsEdges.begin(), mesh_2.Cell3DsEdges.end(), 0);
	
	mesh_2.Cell3DsFaces.resize(mesh_2.NumCell2Ds);
	iota(mesh_2.Cell3DsFaces.begin(), mesh_2.Cell3DsFaces.end(), 0);

	return true;
}






//Proiezione su sfera unitaria e controllo 
void proiezione_su_sfera_unitaria(PolygonalMesh& mesh) {
    for (unsigned int i = 0; i < mesh.NumCell0Ds; i++) {
        Vector3d vertice = mesh.Cell0DsCoordinates.col(i);
        vertice.normalize(); 
        mesh.Cell0DsCoordinates.col(i) = vertice;
    }
	
    for (unsigned int i = 0; i < mesh.NumCell0Ds; i++) {
        double r = mesh.Cell0DsCoordinates.col(i).norm();
        if (std::abs(r - 1.0) > 1e-10) {
            std::cerr << "il vertice " << i << " ha raggio = " << r << "\n";
        }
    }
}

void info_mesh(const PolygonalMesh& mesh){
	//questa funzione stampa i dati della mesh... mi aiuta a vedere se sto aggiornando tutto

    cout << "========== MESH =========="<<endl<<endl;

    // --- Cell0D ---
    cout << "-- Cell0D --"<<endl<<endl;
    cout << "Numero di Cell0Ds: " << mesh.NumCell0Ds <<endl;
    cout << "Cell0DsId: ";
    for (auto id : mesh.Cell0DsId)
        cout << id << " ";
    cout <<endl<< "Cell0DsCoordinates:"<<endl;
	for (int i=0;i<mesh.NumCell0Ds;i++){
	cout<<"{"<< mesh.Cell0DsCoordinates.col(i).transpose() <<"} ";
	}
	cout<<endl;

    // --- Cell1D ---
    cout <<endl<< "-- Cell1D --"<<endl<<endl;
    cout << "Numero di Cell1Ds: " << mesh.NumCell1Ds << endl;
    cout << "Cell1DsId: ";
    for (auto id : mesh.Cell1DsId)
        cout << id << " ";
	cout<<endl;
    for (int i=0;i<mesh.Cell1DsExtrema.cols();i++){
	cout<<"id: "<<i<<" {"<< mesh.Cell1DsExtrema.col(i).transpose() <<"} ";
	}
	cout<<endl;

    // --- Cell2D ---
    cout <<endl<< "-- Cell2D --"<<endl<<endl;
    cout << "Numero di Cell2Ds: " << mesh.NumCell2Ds << endl;
    cout << "Cell2DsId: ";
    for (auto id : mesh.Cell2DsId)
        cout << id << " ";
    cout << endl << "Cell2DsNumVert: ";
    for (auto n : mesh.Cell2DsNumVert)
        cout << n << " ";
    cout <<endl<< "Cell2DsNumEdg: ";
    for (auto n : mesh.Cell2DsNumEdg)
        cout << n << " ";

    cout <<endl<< "Cell2DsVertices:"<<endl;
    for (size_t i = 0; i < mesh.Cell2DsVertices.size(); ++i) {
        cout << "  [" << i << "]: ";
        for (auto v : mesh.Cell2DsVertices[i])
            cout << v << " ";
        cout << "\n";
    }

    cout << "Cell2DsEdges:"<<endl;
    for (size_t i = 0; i < mesh.Cell2DsEdges.size(); ++i) {
        cout << "  [" << i << "]: ";
        for (auto e : mesh.Cell2DsEdges[i])
            cout << e << " ";
        cout << endl;
    }
	
	
	// --- Cell3D ---
    cout <<endl<< "-- Cell3D --"<<endl<<endl;
    cout << "Numero di Cell3Ds: " << mesh.NumCell3Ds << endl;
    cout << "Cell3DsId: "<<mesh.Cell3DsId<<endl;
	cout << "Numero di vertici: " << mesh.Cell3DsNumVert << endl;
	cout << "Numero di lati: " << mesh.Cell3DsNumEdg << endl;
	cout << "Numero di facce: " << mesh.Cell3DsNumFaces << endl;
	/*
	cout << "Vertici:"<<endl;
	for (unsigned int i = 0; i < mesh.Cell3DsNumVert; i++) {
		cout << mesh.Cell3DsVertices[i];
		cout << "\n";
	}
	cout << "\n";
	cout << "Lati:";
	cout << "\n";
	for (unsigned int j = 0; j < mesh.Cell3DsNumEdg; j++) {
		cout << mesh.Cell3DsEdges[j];
        cout << "\n";
	}
	cout << "\n";
	cout << "Facce:";
	cout << "\n";
	for (unsigned int k = 0; k < mesh.Cell3DsNumFaces; k++) {
        cout << mesh.Cell3DsFaces[k];
        cout << "\n";
	}
	*/
	cout<<endl;
    cout << "==========================\n";

}
// Funzioni di salvataggio e stampa celle in txt
//Cella 0D
void salvataggio_Cell0Ds(const PolygonalMesh& mesh, const std::string& filename) {
    std::ofstream file(filename);
	file << "-- Cell0D --"<<endl<<endl;
	file << "Numero di Cell0Ds: " << mesh.NumCell0Ds <<endl << endl;
	file << "Identificativi: "<< endl <<endl;
	for (unsigned int j = 0; j< mesh.NumCell0Ds; j++){
		file << mesh.Cell0DsId[j]<<endl;
	}
	file << "\n";
	file << "Coordinate: "<<endl<<endl;
    for (unsigned int i = 0; i < mesh.NumCell0Ds; i++) {
		file << mesh.Cell0DsCoordinates.col(i)[0] << " "<< mesh.Cell0DsCoordinates.col(i)[1]<<" "<<mesh.Cell0DsCoordinates.col(i)[2]<<endl;
    }
    file.close();
}

//Cella 1D
void salvataggio_Cell1Ds(const PolygonalMesh& mesh, const std::string& filename) {
    std::ofstream file(filename);
	file << "-- Cell1D --"<<endl<<endl;
	file << "Numero di Cell1Ds: " << mesh.NumCell1Ds <<endl << endl;
	file << "Identificativi: "<<endl<<endl;
	for (unsigned int j = 0; j< mesh.NumCell1Ds; j++){
		file << mesh.Cell1DsId[j]<<endl;
	}
	file << "\n";
	file << "ID Vertici:"<<endl<<endl;
    for (unsigned int i = 0; i < mesh.NumCell1Ds; i++) {
		file << mesh.Cell1DsExtrema.col(i)[0] << " " << mesh.Cell1DsExtrema.col(i)[1]<<endl;
    }
    file.close();
}

//Cella 2D
void salvataggio_Cell2Ds(const PolygonalMesh& mesh, const std::string& filename) {
    std::ofstream file(filename);
	file << "-- Cell2D --"<<endl<<endl;
	file << "Numero di Cell2Ds: " << mesh.NumCell2Ds <<endl << endl;
	file << "Identificativi: "<<endl<<endl;
	for (unsigned int z = 0; z< mesh.NumCell2Ds; z++){
		file << mesh.Cell2DsId[z]<<endl;
	}
	file << "\n";
	file << "Numero Vertici: "<< " " << mesh.NumCell2Ds<<endl<<endl;
	file << "Vertici:"<<endl<<endl;
    for (unsigned int i = 0; i < mesh.NumCell2Ds; i++) {
		file << mesh.Cell2DsVertices[i][0] << " " << mesh.Cell2DsVertices[i][1] << " "<< mesh.Cell2DsVertices[i][2]<<endl;
	}
	file << "\n";
	file << "Numero Lati: "<< " " << mesh.NumCell2Ds<<endl<<endl;
	file << "Lati:"<<endl<<endl;
	for (unsigned int j = 0; j < mesh.NumCell2Ds; j++) {
		file << mesh.Cell2DsEdges[j][0] << " " << mesh.Cell2DsEdges[j][1] << " "<< mesh.Cell2DsEdges[j][2]<<endl;
	}
	
    file.close();
}

//Cella 3D
void salvataggio_Cell3Ds(const PolygonalMesh& mesh, const std::string& filename) {
    std::ofstream file(filename);
	file << "-- Cell3D --"<<endl<<endl;
	file << "Numero di Cell3Ds: " << mesh.NumCell3Ds <<endl << endl;
	file << "Numero Vertici: "<< " " << mesh.Cell3DsNumVert<<endl<<endl;
	file << "Vertici:"<<endl<<endl;
    for (unsigned int i = 0; i < mesh.Cell3DsNumVert; i++) {
		file << mesh.Cell3DsVertices[i]<<endl;
	}
	file << "\n";
	file << "Numero Lati: "<< " " << mesh.Cell3DsNumEdg<<endl<<endl;
	file << "Lati:"<<endl<<endl;
	for (unsigned int j = 0; j < mesh.Cell3DsNumEdg; j++) {
		file << mesh.Cell3DsEdges[j]<<endl;
	}
	file << "\n";
	file << "Numero Facce: "<< " " << mesh.Cell3DsNumFaces<<endl<<endl;
	file << "Facce:"<<endl<<endl;
	for (unsigned int k = 0; k < mesh.Cell3DsNumFaces; k++) {
        file << mesh.Cell3DsFaces[k]<<endl;
	}
	file.close();
}



//funzione baricentro

Eigen::Vector3d baricentro(const vector<unsigned int>& vertici, const PolygonalMesh& mesh) {
    Eigen::Vector3d b = Eigen::Vector3d::Zero();
    for (unsigned int v : vertici) {
        b += mesh.Cell0DsCoordinates.col(v);
    }
    return b / vertici.size();
}

// la seguente funzione crea un vettore di vettori. il vettore in posizione 
// i, cioe facce_per_vertice[i], contiene l'elenco delle facce nelle quali 
// è presente il vertice i
// ATTENZIONE: i vertici e facce a cui mi riferisco sono quelli della 
// 	           mesh, serviranno poi per il duale.
vector<vector<unsigned int>> trova_facce_per_vertice(const PolygonalMesh& mesh) {
    vector<vector<unsigned int>> facce_per_vertice(mesh.NumCell0Ds);

    for (unsigned int i = 0; i < mesh.NumCell2Ds; ++i) {
        for (unsigned int v : mesh.Cell2DsVertices[i]) {
            facce_per_vertice[v].push_back(i);
        }
    }

    return facce_per_vertice;
}


vector<unsigned int> giro_attorno_vertice(const PolygonalMesh& mesh, unsigned int v,
										  const vector<unsigned int>& facce_vicinato_v){
	
	
	if (facce_vicinato_v.size() <= 2)
        return facce_vicinato_v;
	
	// la mappa adiacenze, ha come chiave l'id di una faccia. 
	// nel vettore associato ad una chiave, sono presenti gli id delle 
	// facce adiacenti (che condividono un lato) a quella in chiave
	// OSS: le facce prese in consderazione sono solo quelle del vicinato di v
	// in pratica, due facce sono adiacenti (in questo contesto) se condividono un 
	// lato, che ha come un estremo proprio v
    map<unsigned int, vector<unsigned int>> adiacenze;

    for (unsigned int i = 0; i < facce_vicinato_v.size(); i++) {
        unsigned int fi = facce_vicinato_v[i];

        for (unsigned int j = 0; j < facce_vicinato_v.size(); j++) {
            if (i == j) continue;
            unsigned int fj = facce_vicinato_v[j];

            for (unsigned int a=0; a<mesh.Cell2DsEdges[fi].size(); a++) {
				unsigned int ei=mesh.Cell2DsEdges[fi][a];
                for (unsigned int b=0; b<mesh.Cell2DsEdges[fj].size(); b++) {
					unsigned int ej=mesh.Cell2DsEdges[fj][b];
                    if (ei == ej) {
                        unsigned int v0 = mesh.Cell1DsExtrema(0, ei);
						unsigned int v1 = mesh.Cell1DsExtrema(1, ei);

                        if (v0 == v || v1 == v) {
                            adiacenze[fi].push_back(fj);
                        }
                    }
                }
            }
        }
    }

    // Ordino ciclicamente le facce
    vector<unsigned int> ordinato;
    unordered_set<unsigned int> visitato;
    unsigned int corrente = facce_vicinato_v[0];
	
	// il vector "ordinato" conterrà gli id delle facce attorno a v, ordinati ciclicamente
	// per prima cosa aggiungiamo ad ordinato la faccia zero memorizzata in facce_vicinato_v
	// dunque tra le sue vicime memorizzare in adiacenza, prendiamo quella che non 
	// abbiamo ancora visitato, o comunque la prima disponibile
	// si procede cercando la successiava della faccia corrente.

    while (ordinato.size() < facce_vicinato_v.size()) {
        ordinato.push_back(corrente);
        visitato.insert(corrente);

        bool trovato = false;
        for (unsigned int vicina : adiacenze[corrente]) {
            if (!visitato.count(vicina)) {
                corrente = vicina;
                trovato = true;
                break;
            }
        }

        if (!trovato) break; // Caso limite: facce non ben collegate
    }

    return ordinato;
	
	
	
	
}


//funzione duale


PolygonalMesh CostruisciDualeMesh(const PolygonalMesh& mesh) {
    PolygonalMesh duale;

    unsigned int num_facce = mesh.NumCell2Ds; 
	duale.NumCell0Ds=num_facce;
    duale.Cell0DsCoordinates.resize(3, num_facce);
	
	// creo i vertici del duale, sono i baricentri delle facce di mesh
    for (unsigned int i = 0; i < num_facce; i++) {
        duale.Cell0DsCoordinates.col(i) = baricentro(mesh.Cell2DsVertices[i], mesh);
    }
	duale.Cell0DsId.resize(num_facce);
	iota(duale.Cell0DsId.begin(), duale.Cell0DsId.end(), 0);
	
	// trovo i lati del duale, posso connettere due baricentri, solo se 
	// le due facce che li generano sono adiacenti, cioè hanno un lato in comune
    unsigned int max_connessioni = num_facce * (num_facce - 1) / 2;
	duale.Cell1DsExtrema.resize(2,max_connessioni);

    unsigned int count = 0;

    for (unsigned int i = 0; i < num_facce; i++) {
        vector<unsigned int> faccia_i = mesh.Cell2DsEdges[i];

        for (unsigned int j = i + 1; j < num_facce; ++j) {
            vector<unsigned int> faccia_j = mesh.Cell2DsEdges[j];

            bool adiacenti = false;

            for (unsigned int a = 0; a < faccia_i.size(); a++) {
                unsigned int vi1 = faccia_i[a];
                
                for (unsigned int b = 0; b < faccia_j.size(); b++) {
                    unsigned int vj1 = faccia_j[b];

                    if (vi1 == vj1){
                        adiacenti = true;
                        break;
                    }
                }

                if (adiacenti) break;
            }

            if (adiacenti) {
				// OSS: grazie al fatto che j>i, potrò in seguito usare la funzione esiste_gia_1Dgià
                duale.Cell1DsExtrema.col(count) << i, j;
                count++;
            }
        }
    }

    duale.NumCell1Ds=count;
	duale.Cell1DsExtrema.conservativeResize(2,count);
	duale.Cell1DsId.resize(count);
	iota(duale.Cell1DsId.begin(), duale.Cell1DsId.end(), 0);
	
	// passo ora a costruire le facce del duale
	
	vector<vector<unsigned int>> facce_per_vertice = trova_facce_per_vertice(mesh);
	
	duale.NumCell2Ds=mesh.NumCell0Ds;
	duale.Cell2DsVertices.resize(duale.NumCell2Ds);
    duale.Cell2DsId.resize(duale.NumCell2Ds);
	duale.Cell2DsNumVert.reserve(duale.NumCell2Ds);
	duale.Cell2DsNumEdg.reserve(duale.NumCell2Ds);
	
	
	for (unsigned int v = 0; v < mesh.NumCell0Ds; v++) {
		// facce che contengono il vertice v di mesh
        vector<unsigned int> facce = facce_per_vertice[v];
        vector<unsigned int> facce_ordinate = giro_attorno_vertice(mesh, v, facce);

        duale.Cell2DsVertices[v] = facce_ordinate;
        duale.Cell2DsId[v] = v;
		duale.Cell2DsNumVert.push_back(facce_ordinate.size());
		duale.Cell2DsNumEdg.push_back(facce_ordinate.size());
    }
	
	// ora ho i vertici che compongono ogni faccia, e tutti i lati del duale
	// costruisco i lati che compongono ogni faccia cercando l'ordinamento
	// per farlo uso un modo analogo a "tri_lati_facce" con la differenza che qui 
	// tutti i lati sono già fatti
		
	duale.Cell2DsEdges.reserve(mesh.NumCell0Ds);
	
	for (unsigned int j=0;j<mesh.NumCell0Ds;j++){
		vector<unsigned int> v={};
		v.reserve(duale.Cell2DsNumEdg[j]);
		for (unsigned int i=0;i<duale.Cell2DsNumEdg[j];i++){
			unsigned int point_1 = duale.Cell2DsVertices[j][i];
			unsigned int point_2 = duale.Cell2DsVertices[j][(i+1)%(duale.Cell2DsNumEdg[j])];
			
			//OSS: posso usare esiste già perchè ho creato i lati con id della coppia crescente
			int id_l=esiste_gia_1D(point_1, point_2, duale);
			if (id_l==-1){
				// il lato è nuovo --> problema, li avevamo gia tutti
				cerr<<"Errore grave, lato non esistente---------------------------------"<<endl;
			} else{
				// il lato esiste già 
				v.push_back(id_l);
			}
			
		}
		duale.Cell2DsEdges.push_back(v);
	}
	
	duale.Cell3DsId=0;
	duale.Cell3DsNumVert =duale.NumCell0Ds;
	duale.Cell3DsNumEdg =duale.NumCell1Ds;
	duale.Cell3DsNumFaces =duale.NumCell2Ds;
	
	duale.Cell3DsVertices = duale.Cell0DsId;
	duale.Cell3DsEdges = duale.Cell1DsId;
	duale.Cell3DsFaces=duale.Cell2DsId; 
	
	
	
	
    return duale;
	
}



double distanza(const Vector3d& p1, const Vector3d& p2) {
    return (p1 - p2).norm();
}

using Grafo = std::vector<std::vector<std::pair<int, double>>>;

Grafo costruisci_grafo_pesato(int n, const Eigen::MatrixXi& Cell1DsExtrema, const std::vector<Eigen::Vector3d>& coords) {
    Grafo grafo(n); 

    for (int i = 0; i < Cell1DsExtrema.cols(); i++) {
        int u = Cell1DsExtrema(0, i);
        int v = Cell1DsExtrema(1, i);

        double peso = (coords[u] - coords[v]).norm();

        grafo[u].push_back({v, peso});
        grafo[v].push_back({u, peso});
    }

    return grafo;
}

std::vector<int> dijkstra(const Grafo& la, int s, int w, std::vector<double>& dist, std::vector<int>& pred) {
    int n = static_cast<int>(la.size());
    pred.resize(n);
    dist.resize(n);

    for (int i = 0; i < n; i++) {
        pred[i] = -1;
        dist[i] = std::numeric_limits<double>::infinity();
    }
    pred[s] = s;
    dist[s] = 0;

    using Nodo = std::pair<double, int>;
    std::priority_queue<Nodo, std::vector<Nodo>, std::greater<Nodo>> PQ;

    for (int i = 0; i < n; i++) {
        PQ.push({dist[i], i});
    }

    std::vector<bool> visitato(n, false);

    while (!PQ.empty()) {
        auto [d, u] = PQ.top();
        PQ.pop();

        if (visitato[u]) continue; 
        visitato[u] = true;

        if (u == w) break; 

        for (const auto& [vicino, peso] : la[u]) {
            if (dist[vicino] > dist[u] + peso) {
                dist[vicino] = dist[u] + peso;
                pred[vicino] = u;
                PQ.push({dist[vicino], vicino});
            }
        }
    }
	
    std::vector<int> cammino;
    if (dist[w] < std::numeric_limits<double>::infinity()) {
        for (int cur = w; cur != s; cur = pred[cur]) {
            cammino.push_back(cur);
        }
        cammino.push_back(s);
        std::reverse(cammino.begin(), cammino.end());
    }
    return cammino;
}

void trova_cammino_minimo(PolygonalMesh& mesh, int id1, int id2) {
    int n = mesh.Cell0DsCoordinates.cols();
	if (id1 < 0 || id1 >= n || id2 < 0 || id2 >= n) {
        cout << "Valore di id1 o id2 non valido" << endl;
        return;
    }
    vector<Eigen::Vector3d> coords(n);
    for (int i = 0; i < n; i++)
        coords[i] = mesh.Cell0DsCoordinates.col(i);

    Grafo grafo = costruisci_grafo_pesato(n, mesh.Cell1DsExtrema, coords);

    vector<double> dist;
    vector<int> pred;
    vector<int> cammino = dijkstra(grafo, id1, id2, dist, pred);
	
	mesh.Cell0DsShortPath.resize(n, 0);
	mesh.Cell1DsShortPath.resize(mesh.Cell1DsExtrema.cols(), 0);

    if (cammino.empty()) {
        cout << "Nessun cammino trovato tra " << id1 << " e " << id2 << endl;
        return;
    }

    for (int v : cammino) {
        mesh.Cell0DsShortPath[v] = 1;
    }

    int num_archi = 0;
    double lunghezza_totale = 0.0;
	
	for (Eigen::Index i = 0; i + 1 < cammino.size();i++) {
		int u = cammino[i];
		int v = cammino[i + 1];

		for (Eigen::Index j = 0; j < mesh.Cell1DsExtrema.cols();j++) {
			int a = mesh.Cell1DsExtrema(0, j);
			int b = mesh.Cell1DsExtrema(1, j);
			if ((a == u && b == v) || (a == v && b == u)) {
				mesh.Cell1DsShortPath[j] = 1;
				lunghezza_totale += distanza(mesh.Cell0DsCoordinates.col(a), mesh.Cell0DsCoordinates.col(b));
				num_archi++;
				break;
		}
	}
}

    cout << "Cammino minimo tra " << id1 << " e " << id2 << " trovato" << endl;
    cout << "Numero di lati nel cammino: " << num_archi << endl;
    cout << "Somma lunghezze: " << lunghezza_totale << endl;
}



	

}
/* TO DO: 1)lati e facce della triangolazione;
          2)affinare il duale;
		  3)creare funzione che stampi i file;
		  4)meanwhile iniziare scrittura di qualche google test, ad esempio nel calcolo del baricentro, esiste già, vertici della triangolazione, etc...;
		  
*/

