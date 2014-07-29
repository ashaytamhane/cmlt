/*
CMLT Library
Author: Ashay Tamhane

*/

#ifndef MATRIX_GEN
#define MATRIX_GEN

#include<iostream>
#include<vector>
#include<stdlib.h>
#include<typeinfo>
#include<cmath>

using namespace std;

/*! \brief 
	* Matrix class. */

class Matrix{
private:
	typedef struct item{
		void* p;
		string type;
	}item;
	vector<vector<item> > mat;
	int numrows,numcols,matrank;
public:
	/*!
		Get number of rows of the matrix	
	*/	
	int get_numrows();
	/*!
		Get number of rows of the matrix	
	*/	
	int get_numcols();
	/*!
		Insert an item into the matrix
	*/	
		
	template<class T>	
	void insert(int row,int col,T i);	
	void insert(int row,int col,string s);

	/*!
		Fetch the value at ith row and jth column	
	*/	
	
	float operator()(int,int);

	/*!
		Support retrieving all rows of  matrix. Example: A(:,1) returns a matrix with all rows for column 1	
	*/	
	
	Matrix operator()(char c,int col);
	
	/*!
		Support retrieving all columns of  matrix. Example: A(1,:) returns a matrix with all columns for row 1	
	*/	

	Matrix operator()(int row,char c);

	/*!
		Support retrieving all the rows with specified range
	*/

	Matrix operator()(int row1,int row2,int col1,int col2);

	/*!
		Add two matrices
	*/	
	
	Matrix operator+(Matrix m);
	
	/*!
		Subtract two matrices
	*/	
		
	Matrix operator-(Matrix m);
	
	/*!
		Multiply two matrices
	*/	
		
	Matrix operator*(Matrix m);
	
	/*!
		Multiple constant to a matrix
	*/	
		
	Matrix operator*(float s);

	/*!
		Transpose the matrix
	*/	
	
	Matrix operator~();
	
	/*!
		Invert the matrix
	*/	
		
	Matrix inv();

	/*!
		Check if the matrix is an identity matrix
	*/	
	
	bool is_identity();

	/*!
		Return the row reduced form of matrix
	*/	
	
	Matrix rrf();

	/*!
		QR factorization. Returns a size 2 vector in which first matrix is Q and second is R
	*/	
	
	vector<Matrix> qr_factorize();

	/*!
		Display the matrix
	*/	
	
	void print();

	/*!
		Create a random matrix of i rows and j columns
	*/	
	
	void create_rand(int,int);

	/*!
		Normalize the matrix
	*/	
	
	void normalize();

	/*!
		Augment the matrix with the one given as arguement
	*/	
		
	void augment(Matrix);

	/*!
		Create a square matrix of ones of given size
	*/	
	
	Matrix ones(int size);
	string get_type(string s);

	/*!
		Swap two rows of matrix
	*/	
	
	void swaprows(int r1,int r2);

	/*!
		QR algorithm for getting eigen values and eigen vectors
	*/	
	
	vector<Matrix> qr_algorithm();

	/*!
	 	Get the eigen vectors and eigen values of the matrix
	*/	
	
	vector<Matrix> eigen();
	
	/*!
		Return rank of the matrix
	*/	

	int rank();
	
	/*!
		Return Covariance matrix
	*/	
	
	Matrix covariance();	

	/*!
		Return covariance of two variable (vectors)
	*/
	
	float covariance(Matrix X1,Matrix X2);
	
	/*!
		Return the Housholder matrix for a column vector
        */	

	Matrix householder(int k);

	/*!
		Return the norm of a vector
	*/

	
	float norm();
	
	/*!
		Return the bidiagonal reduction
	*/
	
	vector<Matrix> bidiag_reduction();

	/*!
		Return the vector sweep	
	*/

	vector<Matrix> vsweep(Matrix d, Matrix e);

	/*!
		Rot the vector
	*/

	vector<float> rot(float f,float g);
		
	/*!
		Bi-diagonal SVD
 	*/
	
	Matrix bd_svd(Matrix d,Matrix e);

	/*!
		Calculate the SVD
	*/

	vector<Matrix> svd();

	/*!
		Return the diagonal and super diagonal
	*/

	vector<Matrix> diag();

	Matrix()
	{
		numrows=-1;
		numcols=-1;
		matrank=-1;
	}

	Matrix(float f)
	{
		numrows=-1;
		numcols=-1;
		(*this).insert(0,0,f);
		numrows=0;
		numcols=0;		
	}
};

#endif
