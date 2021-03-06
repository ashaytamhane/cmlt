/*
CMLT Library
Author: Ashay Tamhane

*/

#include"matrix_generic.hpp"
#include<set>
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
		int chk=s.c_str()[i];
		if((s.c_str()[i]>47 && s.c_str()[i]<58) || s.c_str()[i]=='-')
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

Matrix Matrix::operator()(int row1,int row2,int col1,int col2)
{
	Matrix result;
	Matrix current=(*this);
	if(row1<=row2 && col1<=col2 && row2<=current.get_numrows() && col2<=current.get_numcols())
	{
		for(int i=row1;i<=row2;i++)
		{
			for(int j=col1;j<=col2;j++)
			{
				result.insert(i-row1,j-col1,current(i,j));
			}
		}
	}
	else
	{
		cout<<"Invalid parameters to () operator";
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

float Matrix::norm()
{
	Matrix current=(*this);
	if(current.get_numcols()!=0)
	{
		cout<<"Norm needs a column vector"<<endl;
	}
	float result=0;
	for(int i=0;i<=current.get_numrows();i++)
	{
		float j=current(i,0);
		result=result+j*j;
	}
	result=sqrt(result);
	return result;
}


Matrix Matrix::householder(int k)
{
	Matrix H;	
	Matrix b=(*this);	
	int n=b.get_numrows();
	int c=b.get_numcols();	
	if((c+1)!=1)
	{
		cout<<"Input to Householder should be column vector. Number of columns: "<<n<<endl;
		exit(0);
	}
	Matrix d=b(k,b.get_numrows(),0,0);
	float alpha,d1,v1,p;
	d1=d(0,0);	
	if(d1>=0)
		alpha=-d.norm();
	else
		alpha=d.norm();
	if(alpha==0)
	{
		H=ones(n);
		return H;
	}	
	v1=sqrt(0.5*(1-(d1/alpha)));
	p=-alpha*v1;
	
	Matrix w;
	for(int j=0;j<k;j++)
	{
		w.insert(j,0,0);
	}	
	w.insert(k,0,v1);
	for(int j=1;j<=d.get_numrows();j++)
	{
		float vj=d(j,0)/(2*p);
		w.insert(j+k,0,vj);
	}	
	
	//cout<<n<<" "<<(w*~w).get_numrows()<<" "<<(w*~w).get_numcols()<<endl;	
	H=ones(n)-(w*~w)*2;
	return H;		
}


vector<Matrix> Matrix::bidiag_reduction()
{
	Matrix B=(*this);
	int m=B.get_numrows();
	int n=B.get_numcols();
	Matrix U,V,H;
	U=ones(m);
	V=ones(n);
	for(int k=0;k<=n;k++)
	{
		// eliminate non-zeros below the diagonal
		Matrix b=B(':',k);
		H=b.householder(k);
		B=H*B;
		U=U*(~H);
        	// eliminate non-zeroes to the right of superdiagonal by working with transpose
		if(k<n)
		{			
			Matrix B_trans=~B;
			b=B_trans(':',k);
			H=b.householder(k+1);
			Matrix B_t=H*B_trans;	
			B=(B)*(~H); // or ~B_trans * ~H
			V=V*(~H);
		}			
		 								
	}	
	vector<Matrix> result;
	result.push_back(U);
	result.push_back(B);
	result.push_back(V);
	cout<<"usv prior"<<endl;
	(U*B*(~V)).print();
	return result;	
}

vector<float> Matrix::rot(float f, float g)
{
	vector<float> result;
	float c,s,r;	
	if(f==0)
	{
		c=0;
		s=1;
		r=g;
	}
	else
	{
		if(abs(f)>abs(g))
		{
			float t=g/f;
			float t1=sqrt(1+t*t);
			c=1/t1;
			s=t*c;
			r=f*t1;		
		}
		else
		{
			float t=f/g;
			float t1=sqrt(1+t*t);
			s=1/t1;
			c=t*s;
			r=g*t1;	
		}
	}
	result.push_back(c);
	result.push_back(s);
	result.push_back(r);
	return result;
}

vector<Matrix> Matrix::vsweep(Matrix d, Matrix e)
{
	vector<Matrix> result;
	Matrix m;
	float c_old=1,s_old,c=1,s,r;	
	int n=d.get_numrows();
	for(int k=0;k<n;k++)
	{
		vector<float> csr=m.rot(c*d(k,0),e(k,0));
		c=csr[0];s=csr[1];r=csr[2];		
		if(k!=0)
		{
			e.insert(k-1,0,r*s_old);		
		}		
		csr=m.rot(c_old*r,d(k+1,0)*s);
		c_old=csr[0];s_old=csr[1];d.insert(k,0,csr[2]);
	}
	float h=c*d(n,0);
	e.insert(n-1,0,h*s_old);
	d.insert(n,0,h*c_old);	
	result.push_back(d);
	result.push_back(e);
	return result;
}

Matrix Matrix::bd_svd(Matrix d, Matrix e)
{
	Matrix result;	
	double tol=100*pow(2,-52);
	double realmin=2.2251* pow(2.71828,-308);
	int n=d.get_numrows();
	int maxit=500*n*n;
	vector<float> lambda(n+1,0);
	set<float> ordered,sorted_d;
	Matrix reverse_sorted_d;
	lambda[n]=abs(d(n,0));
	ordered.insert(lambda[n]);
	for(int j=n-1;j>=0;j--)
	{
		lambda[j]=abs(d(j,0))*lambda[j+1]/(lambda[j+1]+abs(e(j,0)));
		ordered.insert(lambda[j]);
	}
	vector<float> mu(n+1,0);
	mu[0]=abs(d(1,0));	
	ordered.insert(mu[0]);
	for(int j=0;j<n;j++)
	{
		mu[j+1]=abs(d(j+1,0))*mu[j]/(mu[j]+abs(e(j,0)));
		ordered.insert(mu[j+1]);
	}
	float sigma_lower=*(ordered.begin());
	float thresh=max(tol*sigma_lower,maxit*realmin);						
	
	int iupper=n-1;
	int ilower=0;
	for(int iter=1;iter<=maxit;iter++)
	{
		float j=iupper;
		for(int i=iupper;i>=0;i--)
		{
			if(abs(e(i,0))>thresh)
			{
				j=i;
				break;
			}
		}

		iupper=j;
		j=iupper;
		for(int i=ilower;i<=iupper;i++)
		{
			if(abs(e(i,0))>thresh)
			{
				j=i;
				break;
			}
		}
		ilower=j;
		if((iupper==ilower && abs(e(iupper,0))<=thresh) || (iupper<ilower))		
		{
			// put values in set to sort for now..later implement sort for matrix class
			for(int k=0;k<=d.get_numrows();k++)
				sorted_d.insert(abs(d(k,0)));
			int p=0;
			for(set<float>::reverse_iterator it=sorted_d.rbegin();it!=sorted_d.rend();++it)
			{
				reverse_sorted_d.insert(p,0,*it);
				p++;
			}
			return reverse_sorted_d;
		}	
		// do a sweep
		vector<Matrix> sweep=result.vsweep(d(ilower,iupper+1,0,0),e(ilower,iupper,0,0));		
		Matrix d_sweep=sweep[0];
		Matrix e_sweep=sweep[1];		
		for(int i=ilower;i<=(iupper+1);i++)
		{
			d.insert(i,0,d_sweep(i-ilower,0));
		}
		for(int i=ilower;i<=iupper;i++)
		{
			e.insert(i,0,e_sweep(i-ilower,0));
		}
	}			
	cout<<"Error in SVD. Too many iterations."<<endl;
	exit(0);
}


vector<Matrix> Matrix::svd()
{
	Matrix current=(*this);
	vector<Matrix> ubv=current.bidiag_reduction();
	Matrix U=ubv[0]; Matrix B=ubv[1]; Matrix V=ubv[2];
	vector<Matrix> diags=B.diag();
	Matrix d=diags[0]; Matrix e=diags[1];
	Matrix s=bd_svd(d,e);
	Matrix S;
	for(int i=0;i<=current.get_numrows();i++)
	{
		for(int j=0;j<=current.get_numcols();j++)
		{
			if(i==j && i<=s.get_numrows())
				S.insert(i,j,s(i,0));
			else
				S.insert(i,j,0);
		}
	}	
	vector<Matrix> result;
	result.push_back(U);
	result.push_back(S);
	result.push_back(V);	
	return result;
} 


vector<Matrix> Matrix::diag()
{
	Matrix current=(*this);
	int m=current.get_numrows();
	int n=current.get_numcols();
	Matrix diag, superdiag;	
	int diag_count=0,super_count=0;
	for(int i=0;i<=m;i++)
	{
		for(int j=0;j<=n;j++)
		{
			if(i==j)
				diag.insert(diag_count++,0,current(i,j));			
			if(j==(i+1))
				superdiag.insert(super_count++,0,current(i,j));
		}		
	}
	vector<Matrix> result;
	result.push_back(diag);
	result.push_back(superdiag);
	return result;
}

