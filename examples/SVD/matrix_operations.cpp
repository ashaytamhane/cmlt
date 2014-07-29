/*
CMLT Library
Author: Ashay Tamhane

Sample code for demonstrating Matrix operations
*/

#include<iostream>
#include<vector>
#include"headers/cmlt.hpp" 
using namespace std;

int main()
{
	// load data	
	Data data;
	Matrix X,Y,H;
	data.load_file("data/sample_data5");	

	// get the loaded data in a matrix
	X=data.get_data();

	// print the matrix
	cout<<endl<<"X:";
	X.print(); 
	
/*	// select a column from matrix	
	Y=X(':',0);
	cout<<endl<<"Y:";
	Y.print();

	// householder form of column Y
	H=Y.householder(0);
	cout<<endl<<"H:";
	H.print();

	// H*Y
	cout<<"H*Y"<<endl;
	(H*Y).print();

	// Bi-diagonal form of matrix
	cout<<"Bi-diagonal"<<endl;
	X.bidiag_reduction();
*/
	vector<Matrix> usv=X.svd();	
	usv[0].print();
	usv[1].print();
	usv[2].print();
	(usv[0]*usv[1]*(~usv[2])).print();
	
	return 0;
}

