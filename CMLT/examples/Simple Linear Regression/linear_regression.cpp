/*
CMLT Library
Author: Ashay Tamhane

Sample code for simple linear regression
*/

#include<iostream>
#include<vector>
#include"headers/cmlt.hpp"
using namespace std;

int main()
{
	// load data	
	Data data;
	Matrix X,Y,W,predicted;
	data.load_file("data/sample_data");	

	// split data into features and prediction column
	data.split_cols(1);
	X=data.get_X();
	X=data.prepend_ones(X);
	Y=data.get_Y();	
	
	// regression	
	Regression reg;
	W=reg.batch_gradient_decent(X,Y);
	predicted=W*~X;
	cout<<endl<<"Predicted:"<<endl;
	predicted.print();	
	cout<<endl<<"Actual:"<<endl;
	(~Y).print(); 
	return 0;
}

