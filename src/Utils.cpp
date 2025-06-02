#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "Eigen/Eigen"
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
		cerr<<"valore non valido"<<endl;
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
	
	if ((vertex2 - vertex1).norm() < 1e-12) {
        cerr << "Attenzione: vertex1 e vertex2 coincidono, non si può interpolare" << endl;
        return vertex1;
    }
	Eigen::Vector3d new_vertex = (vertex2 - vertex1) * ((double)step/b) + vertex1;
	//cout << "Coordinate del nuovo vertice: " << new_vertex.transpose() << endl;
    return new_vertex;
}


int Esiste_gia(PolygonalMesh& mesh, const Eigen::Vector3d& nuovo_vertice, unsigned int k) {				   
	double epsilon = 1e-11;
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
	
	//di seguito andrò a creare le nuove facce e lati
	
	tri_vertici_facce(mesh, b, punti_faccia, num_facc_pre, num_nuovi_per_faccia);
	tri_lati_facce(mesh, b, num_facc_pre);
	
	// --> TODO alla fine aggiorno il num facce tutto della mesh
}

void tri_vertici_facce(PolygonalMesh& mesh, unsigned int b, vector<int> punti_faccia,
					   unsigned int num_facc_pre, unsigned int num_nuovi_per_faccia){
	
	//creo le nuove facce, perciò mi dimentico di quelle vecchie	
	mesh.Cell2DsVertices={};
	mesh.Cell2DsVertices.reserve(num_facc_pre*b*b);
	
	//riparto da capo anche con gli id
	mesh.Cell2DsId ={};
	mesh.Cell2DsId.reserve(num_facc_pre*b*b);
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
				mesh.Cell2DsId.push_back(count++);

				// Triangolo 2, solo se non siamo all'ultimo k (serve d)
				if (k < len_r - 2) {
					mesh.Cell2DsVertices.push_back({b_, d, c});
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

//Proiezione su sfera unitaria e controllo 
void proiezione_su_sfera_unitaria(PolygonalMesh& mesh) {
    for (unsigned int i = 0; i < mesh.NumCell0Ds; i++) {
        Vector3d vertice = mesh.Cell0DsCoordinates.col(i);
        vertice.normalize(); 
        mesh.Cell0DsCoordinates.col(i) = vertice;
    }
	
    for (unsigned int i = 0; i < mesh.NumCell0Ds; i++) {
        double r = mesh.Cell0DsCoordinates.col(i).norm();
        if (std::abs(r - 1.0) > 1e-6) {
            std::cerr << "il vertice " << i << " ha raggio = " << r << "\n";
        }
    }
}
	

void tri_lati_facce(PolygonalMesh& mesh, unsigned int b,unsigned int num_facc_pre){
	
	unsigned int num_lati=num_facc_pre*3*b*(b+1)/2 -b*mesh.NumCell1Ds; 
	
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

    cout << "==========================\n";

}
// Funzioni di salvataggio e stampa celle in txt
//Cella 0D
void salvataggio_Cell0Ds(const PolygonalMesh& mesh, const std::string& filename) {
    std::ofstream file(filename);

    for (unsigned int i = 0; i < mesh.NumCell0Ds; i++) {
        file << mesh.Cell0DsId[i] << " "
             << mesh.Cell0DsCoordinates(0, i) << " "
             << mesh.Cell0DsCoordinates(1, i) << " "
             << mesh.Cell0DsCoordinates(2, i) << "\n";
    }
    file.close();
}

//Cella 1D
void salvataggio_Cell1Ds(const PolygonalMesh& mesh, const std::string& filename) {
    std::ofstream file(filename);

    for (unsigned int i = 0; i < mesh.NumCell1Ds; i++) {
        file << mesh.Cell1DsId[i] << " "
             << mesh.Cell1DsExtrema(0, i) << " "
             << mesh.Cell1DsExtrema(1, i) << "\n";
    }
    file.close();
}

//Cella 2D
void salvataggio_Cell2Ds(const PolygonalMesh& mesh, const std::string& filename) {
    std::ofstream file(filename);

    for (unsigned int i = 0; i < mesh.NumCell2Ds; i++) {
        file << mesh.Cell2DsId[i] << " "
             << mesh.Cell2DsNumVert[i] << " "
             << mesh.Cell2DsNumEdg[i] << " ";

        for (unsigned int v : mesh.Cell2DsVertices[i])
            file << v << " ";

        for (unsigned int e : mesh.Cell2DsEdges[i])
            file << e << " ";

        file << "\n";
    }
    file.close();
}

//Cella 3D
void salvataggio_Cell3Ds(const PolygonalMesh& mesh, const std::string& filename) {
    std::ofstream file(filename);

    for (unsigned int i = 0; i < mesh.NumCell3Ds; i++) {
        file << mesh.Cell3DsId[i] << " ";
        for (unsigned int f : mesh.Cell3DsFaces[i])
            file << f << " ";
        file << "\n";
    }
    file.close();
}
/*
//funzione baricentro
Eigen::Vector3d baricentro(const std::vector<size_t>& vertici, const Eigen::MatrixXd& coords) {
    Eigen::Vector3d b = Eigen::Vector3d::Zero();
    for (size_t v : vertici) {
        b += coords.col(v);
    }
    return b / vertici.size();
}

//funzione duale
PolygonalMesh CostruisciDualeMesh(const PolygonalMesh& mesh) {
    PolygonalMesh duale;

    size_t num_facce = mesh.Cells2D.size(); // al posto del secondo membro posso direttamente scrivere NumCell2Ds
    duale.Cell0DCoordinates.resize(3, num_facce);

    for (size_t i = 0; i < num_facce; ++i) {
        duale.Cell0DCoordinates[i] = baricentro(mesh.Cell2DsVertices[i], mesh.Cell0DCoordinates);
    }

    size_t max_connessioni = num_facce * (num_facce - 1) / 2;
    duale.Cells1D.resize(max_connessioni);

    size_t count = 0;

    for (size_t i = 0; i < num_facce; ++i) {
        const std::vector<size_t>& faccia_i = Cells2DEdges[i];

        for (size_t j = i + 1; j < num_facce; ++j) {
            const std::vector<size_t>& faccia_j = Cells2DEdges[j];

            bool adiacenti = false;

            for (size_t a = 0; a < faccia_i.size(); ++a) {
                size_t vi1 = faccia_i[a];
                //size_t vi2 = faccia_i[(a + 1) % faccia_i.size()];

                for (size_t b = 0; b < faccia_j.size(); ++b) {
                    size_t vj1 = faccia_j[b];
                    //size_t vj2 = faccia_j[(b + 1) % faccia_j.size()];

                    if (vi1 == vj1){
                        adiacenti = true;
                        break;
                    }
                }

                if (adiacenti) break;
            }

            if (adiacenti) {
                duale.Cell1DsExtrema.col(count) << i, j;;
                ++count;
            }
        }
    }

    duale.Cell1DsExtrema.conservativeResize(2,count);

    return duale;
}


	
*/
}
/* TO DO: 1)lati e facce della triangolazione;
          2)affinare il duale;
		  3)creare funzione che stampi i file;
		  4)meanwhile iniziare scrittura di qualche google test, ad esempio nel calcolo del baricentro, esiste già, vertici della triangolazione, etc...;
		  
*/

