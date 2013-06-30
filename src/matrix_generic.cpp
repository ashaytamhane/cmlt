/*
CMLT Library
Author: Ashay Tamhane

*/

#include"matrix_generic.hpp"
using namespace std;

int Matrix::get_numrows()
{
	return numrows;
}

int Matrix::get_numcols()
{
	return numcols;
}

vector<Matrix> Matrix::eigen()
{
	Matrix eigen_values,eigen_vectors;
	vector<Matrix> result,temp_result;	
	Matrix a=(*this);
	// check if its a square Matrix
	if(a.get_numrows()!=a.get_numcols())
	{
		cout<<"Not a square matrix."<<endl;
		exit(0);
	}	
	temp_result=a.qr_algorithm();
	eigen_vectors=temp_result[0];
	a=temp_result[1];
	
	// values in diagonal of a are eigen values
	for(int i=0;i<=a.get_numrows();i++)
	{
		eigen_values.insert(i,0,a(i,i));			
	}
	result.push_back(eigen_vectors);
	result.push_back(eigen_values);
	return result;
}

vector<Matrix> Matrix::qr_algorithm()
{
	vector<Matrix> result;	
	Matrix a=(*this);	
	Matrix s;
	vector<Matrix> qr;	
	Matrix q,r;
	for(int i=0;i<1000;i++)
	{
		qr=a.qr_factorize();		
		q=qr[0];
		r=qr[1];
		a=r*q;
		if(i==0)
			s=q;
		else
			s=s*q;
	}
	result.push_back(s);
	result.push_back(a);
	return result;
}


vector<Matrix> Matrix::qr_factorize()
{
	Matrix a=(*this);
	Matrix r;
	int n=a.get_numcols();
	for(int j=0;j<=n;j++)
	{
		// calculate rjj
		float sqr=0;
		for(int i=0;i<=n;i++)
		{
			sqr=sqr+a(i,j)*a(i,j);
		}
		
		r.insert(j,j,sqrt(sqr));
		if(r(j,j)==0)
		{
			cout<<"A has linearly dependent columns."<<endl;
			break;
		}
		else
		{
			// normalize jth column of a with rjj
			for(int i=0;i<=n;i++)
			{
				float tmp=a(i,j)/r(j,j);
				a.insert(i,j,tmp);
			}	
		}
		// take dot product with rest of the columns and set rjk
		for(int k=j+1;k<=n;k++)
		{
			float tmp=0;
			for(int i=0;i<=n;i++)
			{
				tmp=tmp+a(i,j)*a(i,k);
			}
			r.insert(j,k,tmp);
			// set aik
			for(int i=0;i<=n;i++)
			{
				tmp=a(i,k)-a(i,j)*r(j,k);
				a.insert(i,k,tmp);
			}
		}
	}	
	vector<Matrix> result;
	result.push_back(a);
	result.push_back(r);	
	return result;
}



int Matrix::rank()
{
	if(matrank==-1)
	{
		Matrix m=rrf();
		return matrank;
	}
	else
		return matrank;
}

string Matrix::get_type(string s)
{
	string type;
	int cnt_int=0,cnt_dec=0;
	int flag=0;	
	for (int i=0;i<s.length();i++)
	{
		if((s.c_str()[i]>47 && s.c_str()[i]<58) || s.c_str()[0]=='-')
		{
			if(flag==0)			
				cnt_int++;
			else
				cnt_dec++;
		}
		else
		{		
			if(s.c_str()[i]=='.')
			{
				flag=1;
				cnt_dec=1;
			}
			else
			{
				cout<<"Improper input"<<endl;
				exit(1);
			}
		}
	}
	if(cnt_int==s.length())
	{
		type.append("i");		
		return type;
	}
	else
	{
		type.append("f");		
		return type;
	}
}

Matrix Matrix::operator()(int row,char c)
{
	Matrix result;	
	if(c==':')
	{
		for(int i=0;i<=numcols;i++)
		{
			result.insert(0,i,(*this)(row,i));
		}
	}	
	else
	{
		cout<<"Invalid character:"<<c<<endl;
		exit(1);
	}
	return result;
}

Matrix Matrix::operator()(char c,int col)
{
	Matrix result;	
	if(c==':')
	{
		for(int i=0;i<=numrows;i++)
		{
			result.insert(i,0,(*this)(i,col));
		}
	}	
	else
	{
		cout<<"Invalid character:"<<c<<endl;
		exit(1);
	}
	return result;
}



float Matrix::operator()(int row,int col)
{
	if(row<=get_numrows() && col<=get_numcols())
	{
		item i;
		i=mat[row][col];
		if(!i.type.compare("i"))
		{		
			return *(int*)i.p;
		}
		else
		{
			if(!i.type.compare("f"))
				return *(float*)i.p;
		}
	}	
	else
	{
		return NULL;
	}
}


void Matrix::insert(int row,int col,string n)
{
	item i;
	i.p=NULL;
	i.type="";
	if((*this)(row,col)!=NULL)
	{
		//cout<<"yeah"<<endl;		
		free(mat[row][col].p);
		free(&mat[row][col]);
		mat[row][col]=i;
	}
	if(row<=get_numrows() && col<=get_numcols())
	{
		string type;
		type.append(get_type(n));
		if(!type.compare("i"))
		{
			int num=atoi(n.c_str());
			i.type.append("i");
			int *tmp_p=(int*)malloc(sizeof(int));
			*tmp_p=num;			
			i.p=tmp_p;
			mat[row][col]=i;
		}
		else
		{
			if(!type.compare("f"))
			{
				float num=atof(n.c_str());
				i.type.append("f");
				float *tmp_p=(float*)malloc(sizeof(float));
				*tmp_p=num;
				i.p=tmp_p;
				mat[row][col]=i;	
			}
		}

	}	
	else
	{
		if(row>get_numrows())
		{
			mat.resize(row+1);
			numrows=row;
			for(int k=0;k<mat.size();k++)
				mat[k].resize(numcols+1);
		}
		if(col>get_numcols())
		{
			for(int k=0;k<mat.size();k++)
				mat[k].resize(col+1);
			numcols=col;
		}
		string type;
		type.append(get_type(n));
		if(!type.compare("i"))
		{
			int num=atoi(n.c_str());
			i.type.append("i");
			int *tmp_p=(int*)malloc(sizeof(int));
			*tmp_p=num;				
			i.p=tmp_p;
			mat[row][col]=i;
		}
		else
		{
			if(!type.compare("f"))
			{
				float num=atof(n.c_str());
				i.type.append("f");
				float *tmp_p=(float*)malloc(sizeof(float));
				*tmp_p=num;
				i.p=tmp_p;
				mat[row][col]=i;	
			}
		}
	}
}



void Matrix::create_rand(int row,int col)
{
	for(int i=0;i<=row;i++)
	{
		for(int j=0;j<=col;j++)
		{
			float f=rand();		
			(*this).insert(i,j,f);		
		}
	}
}


void Matrix::normalize()
{
	float sum=0;	
	for(int i=0;i<=numrows;i++)
	{
		for(int j=0;j<=numcols;j++)
			sum=sum+(*this)(i,j);
	}
	for(int i=0;i<=numrows;i++)
	{
		for(int j=0;j<=numcols;j++)
		{
			(*this).insert(i,j,(float)(*this)(i,j)/sum);
		}
	}
}


void Matrix::swaprows(int r1,int r2)
{
	float temp;
	for(int i=0;i<=numcols;i++)
	{
		temp=(*this)(r1,i);
		(*this).insert(r1,i,(*this)(r2,i));
		(*this).insert(r2,i,temp);
	}
}


Matrix Matrix::rrf()
{
	Matrix result=(*this);
	int numrows=result.get_numrows();	
	int m;
	for(m=0;m<=numrows;m++)	
	{		
		int pivotrow=m,pivotcol=m;
		float pivot;
						
		// get non zero pivot element		
		for(int i=0;i<numrows;i++)
		{
			pivot=result(pivotrow,pivotcol);
			if(pivot!=0)
				break;
			if(pivotrow+i>numrows)
				break;
			result.swaprows(pivotrow,pivotrow+i);
		}
		pivot=result(pivotrow,pivotcol);			
		if(pivot==0)
		{
			//cout<<"Singular matrix. Cannot be inverted."<<endl;
			matrank=m;
			// get next non zero column
			while(result(pivotrow,pivotcol)==0)
			{
				pivotcol++;
				if(pivotcol>result.get_numcols())
					return result;
			}		
			pivot=result(pivotrow,pivotcol);				
		}	
		// convert pivot element to 1
		if(pivot!=1)
		{
			// divide pivot row
			for(int i=0;i<=result.get_numcols();i++)
			{
				float temp=result(pivotrow,i);
				temp=(float)(temp/pivot);
				result.insert(pivotrow,i,temp);
			}
		}

		// convert pivot column to zeros by reducing each row
		for(int i=0;i<=result.get_numrows();i++)
		{
			if(i!=pivotrow && result(i,pivotcol)!=0)
			{
				// reduce element to 0 
				float mul=result(i,pivotcol);
				for(int j=0;j<=result.get_numcols();j++)
				{
					float temp=result(i,j);		
					temp=temp-mul*result(pivotrow,j);
					result.insert(i,j,temp);
				}
			}
		}
	}
	matrank=m;
	return result;
}


bool Matrix::is_identity()
{
	bool chk=true;		
	Matrix result=(*this);
	for(int j=0;j<=numrows;j++)
	{
		for(int i=0;i<=numcols;i++)
		{
			if(i==j)
			{
				if(result(i,j)!=1)
				{
					chk=false;						
					break;				
				}
			}
			else
			{
				if(result(i,j)!=0)
				{
					chk=false;						
					break;
				}
			}
		}
	}
	return chk;
}

Matrix Matrix::inv()
{
	Matrix result,inverse;
	result=(*this);
	// check if its square Matrix
	if(numrows!=numcols)
	{
		cout<<"Error. Matrix not square."<<endl;
		exit(1);
	}	
	else
	{
		// augment identity Matrix		
		result.augment(ones(numrows));
		
		// get row reduced form		
		result=result.rrf();

		// check if result is identity
		
		if(!result.is_identity())
		{
			cout<<"Matrix singular, cannot be inverted."<<endl;
			exit(1);
		}
		else
		{
			// extract the inverse from augmented Matrix
			for(int j=0;j<=numrows;j++)
			{
				for(int i=numcols+1;i<=result.get_numcols();i++)
				{
					inverse.insert(j,i-numcols-1,result(j,i));
				}
			}
		}
	}
	
	return inverse;
}


void Matrix::augment(Matrix m1)
{
	// check sizes of matrices
	if(numrows!=m1.get_numrows())
	{
		cout<<"Matrix row sizes different. Cannot augment."<<endl;
		exit(1);
	}
	else	
	{
		int tempcols=numcols;
		for(int i=0;i<=m1.get_numrows();i++)
		{
			for(int j=0;j<=m1.get_numcols();j++)
			{
				(*this).insert(i,tempcols+1+j,m1(i,j));
			}
		}		
	}
}

Matrix Matrix::ones(int size)
{
	Matrix result;	
	for(int i=0;i<=size;i++)
	{
		for(int j=0;j<=size;j++)
		{
			if(i==j)			
				result.insert(i,j,1);
			else
				result.insert(i,j,0);
		}
	}
	return result;
}


Matrix Matrix::operator*(float s)
{
	Matrix result;
	for(int i=0;i<=numrows;i++)
	{
		for(int j=0;j<=numcols;j++)
		{
			result.insert(i,j,(*this)(i,j)*s);
		}
	}
	return result;
}



Matrix Matrix::operator+(Matrix m)
{
	if(get_numrows()!=m.get_numrows() || get_numcols()!=m.get_numcols())
	{
		cout<<"Size mismatch in addition."<<endl;
		exit(0);
	}
	else
	{
		Matrix result;
		for(int i=0;i<=numrows;i++)
		{
			for(int j=0;j<=numcols;j++)
			{
				result.insert(i,j,(*this)(i,j)+m(i,j));
			}
		}
		return result;
	}
	
}



Matrix Matrix::operator~()
{
	Matrix result;
	for(int i=0;i<=numrows;i++)
	{
		for(int j=0;j<=numcols;j++)
		{
			result.insert(j,i,(*this)(i,j));
		}
	}
	return result;
}


Matrix Matrix::operator-(Matrix m)
{
	if(get_numrows()!=m.get_numrows() || get_numcols()!=m.get_numcols())
	{
		cout<<"Size mismatch in subtraction."<<endl;
		exit(0);
	}
	else
	{
		Matrix result;
		for(int i=0;i<=numrows;i++)
		{
			for(int j=0;j<=numcols;j++)
			{
				result.insert(i,j,(*this)(i,j)-m(i,j));
			}
		}
		return result;
	}
	
}


void Matrix::print()
{
	for(int i=0;i<=numrows;i++)
	{
		cout<<endl;		
		for(int j=0;j<=numcols;j++)
		{
			cout<<(*this)(i,j)<<" ";
		}
	}
	cout<<endl;
}



Matrix Matrix::operator*(Matrix m)
{
	if(get_numcols()!=m.get_numrows())
	{
		cout<<"Size mismatch in multiplication."<<endl;
		exit(0);
	}
	else
	{
		Matrix result;
		for(int k=0;k<=numrows;k++)
		{
			for(int j=0;j<=m.get_numcols();j++)
			{
				float sum=0;
				for(int i=0;i<=numcols;i++)
				{
					sum=sum+(*this)(k,i)*m(i,j);
				}
				result.insert(k,j,sum);
			}
		}
		return result;
	}
	
}


template<class T>
void Matrix::insert(int row,int col,T n)
{

	item i;
	if(row<=get_numrows() && col<=get_numcols())
	{
		i.type.append(typeid(T).name());
		T *tmp_p=(T*)malloc(sizeof(T));				
		*tmp_p=n;
		i.p=tmp_p;
		mat[row][col]=i;
	}	
	else
	{
		if(row>get_numrows())
		{
			mat.resize(row+1);
			numrows=row;
			for(int k=0;k<mat.size();k++)
				mat[k].resize(numcols+1);
		}
		if(col>get_numcols())
		{
			for(int k=0;k<mat.size();k++)
				mat[k].resize(col+1);
			numcols=col;
		}
		i.type.append(typeid(T).name());
		T *tmp_p=(T*)malloc(sizeof(T));				
		*tmp_p=n;
		i.p=tmp_p;
		mat[row][col]=i;
	}
}


Matrix Matrix::covariance()
{
	Matrix result, parent;
	parent=(*this);
	int numvar=parent.get_numcols()+1;
	for(int i=0;i<numvar;i++)
	{
		Matrix xi=parent(':',i);		
		for(int j=0;j<numvar;j++)
		{
			Matrix xj=parent(':',j);
			result.insert(i,j,covariance(xi,xj));
		}	
	}
	return result;
}

float Matrix::covariance(Matrix X1,Matrix X2)
{
	float result=0;
	if(X1.get_numcols()!=0 || X2.get_numcols()!=0)
	{
		cout<<"Need column vectors of variables for covariance.";
	}	
	if(X1.get_numrows()!=X2.get_numrows())
	{
		cout<<"Number of rows different for both variables.";
		exit(0);
	}
	int n=X1.get_numrows()+1;
	float x1_mean=0,x2_mean=0;	
	for(int i=0;i<n;i++)
	{
		x1_mean=x1_mean+X1(i,0);
		x2_mean=x2_mean+X2(i,0);
	}
	x1_mean=(float)x1_mean/(float)(n);
	x2_mean=(float)x1_mean/(float)(n);
	for(int i=0;i<n;i++)
	{
		result=result+(X1(i,0)-x1_mean)*(X2(i,0)-x2_mean);
	}		
	result=(float)result/(float)(n-1);
	
}


