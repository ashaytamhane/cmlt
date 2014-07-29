/*
CMLT Library
Author: Ashay Tamhane

*/

#ifndef DATA_F
#define DATA_F

#include<fstream>
#include "matrix_generic.hpp"

/*! \brief 
	* Class for handling data. */

class Data{
private:
	Matrix data;
	Matrix X,Y;
public:

	/*!
		Load data from a file in a matrix
	*/	
	
	Matrix load_file(string filename);

	/*!
		Splits a the matrix in 'X' and 'Y' matrices depending on the splitting column index passed as arguement
	*/	
	
	void split_cols(int);

	/*!
		Prepend the matrix with a column of ones
	*/	
		
	Matrix prepend_ones(Matrix X) ;

	/*!
		Returns the 'X' split of the matrix
	*/	
	
	Matrix get_X();
	
	/*!
		Returns the 'Y' split of the matrix
	*/	
		
	Matrix get_Y();
	
	/*!
		Returns the data loaded 
	*/	

	Matrix get_data();
};


#endif

