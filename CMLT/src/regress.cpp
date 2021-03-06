#include"regress.hpp"

Matrix Regression::batch_gradient_decent(Matrix X,Matrix Y)
{
	Matrix w;
	w.create_rand(0,X.get_numcols());
	w.normalize();	
	int k=0;
	float n=0.002;
	Matrix error;
	while(k<100)
	{
		for(int tau=0;tau<=X.get_numrows();tau++)
		{
			error=(Matrix(Y(tau,0))-(w*~X(tau,':')))*X(tau,':');
			w=w+Matrix(n)*error;
		}
		k=k+1;		
	}
	return w;
}
