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
	Matrix X,Y,Z;
	data.load_file("data/sample_data2");	

	// get the loaded data in a matrix
	X=data.get_data();

	// print the matrix
	cout<<endl<<"X:";
	X.print(); 

	// get last array index of rows and columns (number of rows and columns will +1 this number)	
	cout<<endl<<"Rows: "<<X.get_numrows()+1<<" Columns: "<<X.get_numcols()+1<<endl;	
	
	// get the covariance matrix
	Matrix cov_mat;
	cov_mat=X.covariance();
	cout<<endl<<"Covariance Matrix of X:";
	cov_mat.print();
	
	// get the eigen vectors and eigen values of a matrix
	vector<Matrix> eigen;
	Matrix eigen_vectors,eigen_values;
	eigen=X.eigen();
	eigen_vectors=eigen[0];
	eigen_values=eigen[1];
	cout<<endl<<"Eigen vectors of X:";
	eigen_vectors.print();
	cout<<endl<<"Eigen values of X:";
	eigen_values.print();
		
	// invert the matrix
	Y=X.inv();
	cout<<endl<<"Y=inv(X):";	
	Y.print();

	// multiplying two matrices
	Z=X*Y;
	cout<<endl<<"Z=X*Y:";
	Z.print();	

	// adding two matrices
	Z=X+Y;
	cout<<endl<<"Z=X+Y:";	
	Z.print();

	// subtracting two matrices
	Z=X-Y;
	cout<<endl<<"Z=X-Y:";	
	Z.print();
		
	// getting row reduced form of a matrix
	Z=X.rrf();
	cout<<endl<<"Row reduced form of X:";
	Z.print();
	
	
	// get the transpose of a matrix
	Z=~eigen_values;
	cout<<endl<<"Transpose of eigen values of X";
	Z.print();
	
	// create a random matrix 
	Matrix R;
	// note that arguements are max array sizes, which are one less than the actual size of matrix
	R.create_rand(2,2);  
	cout<<endl<<"Random matrix R:";
	R.print();	
	
	// augment a matrix to other
	R.augment(X);
	cout<<endl<<"Augmenting X to R:";
	R.print();
		
	return 0;
}

