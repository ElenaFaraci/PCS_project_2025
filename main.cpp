#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
//#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


int main(){
	
	PolygonalMesh mesh;
	int q=4;
	bool a= valorizza_poliedro(q, mesh);
	
	if (!a){
		cout<<"suca"<<endl;
	}
	
	bool b=controllo_lati_vertici (mesh);
	
	if (!b){
		cout<<"fallisce controllo"<<endl;
	}
		
	
	
	return 0;
}