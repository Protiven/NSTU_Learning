#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale.h>
#include <memory.h>
#include "math.h"
using namespace std;

#define STR 15                         // ���������� ��������� ������ ����� �������
#define EPS			1e-15			   // �������� ������� ����
#define PI			3.141592653589793  // ����� ��
#define MAXITER	    1000               // ���������� ��������
#define MEMORY		200000			   // ����� ������

typedef double REAL;

REAL  *global;	    // ��������� ������� ������
REAL  *GridX;		// ����� ��� �
REAL  *GridY;		// ����� ��� �
REAL  *di;		    // ��������� �������� �������			
REAL  *ggl;		    // ������ ����������� �������� �������
REAL  *ggu;		    // ������� ����������� �������� �������		
REAL  *r;			// ��������������� ������
REAL  *x;			// ������ �������
REAL  *f;			// ������ ������ �����
REAL  *p;			// ��������������� ������
REAL  *z;			// ��������������� ������
REAL  *q;			// ��������������� ������				
REAL  *L;			// ������ ����������� ������������� �������
REAL  *U;			// ������� ����������� ������������� �������
REAL  *diag;		// ��������� ������������� �������
REAL  *s;			// ��������������� ������				
REAL  *sout;		// ��������������� ������				
REAL  eps;		    // �������� �������	
	
int   *ig;		    // ������� �������
int   *jg;		    // ������� ��������� �������		
int   N;			// ����������� ����
int	  Nx;			// ���������� �� �				
int   Ny;			// ���������� �� Y				
int   maxiter;	    // ������������ ����������� ��������				
				
int	  LU();		    // ������� ������������		 
void  assembling();	// c����� ���������� �������			
void  GetInfo();	// ��������� ���������				
void  ReadGrid();	// ������ �����	

void    AddToMatrix(int, int, REAL);	     // ��������� � �������				
REAL    GetLambda(REAL,REAL);		         // ����������� ������				
REAL    GetGamma(REAL,REAL);		         // ����������� �����		 
REAL    GetF(REAL,REAL);			         // ������ �����		 
REAL    GetIdeal(REAL,REAL);		         // ������ �������		  
void    GaussL(REAL *,REAL *);		         // ������� ����		
void	GaussU(REAL *,REAL *);		         // ������� ����		
void	MultMatrixOnVector(REAL *,REAL *);	 // ��������� ������� �� ������		 
REAL    ScalarMult(REAL *,REAL *);			 // ��������� ������������ ��������
REAL    sum(int,int);	                     // ��������� ������������ ������������		
void    method();				             // ������ ������
void    run();			                     // ���������� ������	
void    result();                            // ����� ���������� � ����     


//	������� ����������� � �������
REAL GetLambda(REAL x, REAL y)
{
	return 1.0;
}
REAL GetGamma(REAL x, REAL y)
{
	return 0;
}
REAL GetF(REAL x, REAL y)
{
	return 0;
}
REAL GetIdeal(REAL x, REAL y)
{
	return 100*x;
}

void method()
{
    int i, k;
	// ��������� ���������� � ������
	global = new double[MEMORY];			// ��������� ������
	memset(global,0,MEMORY*sizeof(double));	// �e ���������
	GetInfo();	

	// ��������� ����������
	ig = (int *)global;
	jg = (int *)(global+N+1);

	// ��������� ���������� ��������� �������
	int istep = 0;
	for(i=0;i<N+1;i++)
	{
		ig[i] = istep;
		istep += i;
	}

	// ��������� ������� ��������� �������
	istep = 0;
	for(i=0;i<N;i++)
		for(k=0;k<i;k++)
		{
			jg[istep] = k;
			istep++;
		}

	//	��������� ����������
	ggl   = global+N+1+ig[N];
	ggu   = global+2*(ig[N])+N+1;
	di	  = global+3*(ig[N])+N+1;
	f	  = di+N;
	r	  = f+N;
	z	  = r+N;
	p	  = z+N;
	q	  = p+N;
	diag  = q+N;
	L	  = diag+N;
	U	  = L+ig[N];
	x	  = U+ig[N];
	s	  = x+N;
	sout  = s+N;
	GridX = sout + N;
	GridY = GridX + Nx;

	// ������ �����
	ReadGrid();

	// ������ ���������� �������
	assembling();
}

void GetInfo()
{
	ifstream file("Area.txt");
	file >> Nx >> Ny;
	N = Nx * Ny;					// ������ ������� ����
	file.close();
}

void ReadGrid()
{
	int i;

	// ������ ����� �� ��� �
	ifstream fileX("GridX.txt");
	for(i=0;i<Nx;i++)	
		fileX >> GridX[i];
	fileX.close();

	// ������ ����� �� ��� �
	ifstream fileY("GridY.txt");
	for(i=0;i<Ny;i++)	
		fileY >> GridY[i];
	fileY.close();
}


void assembling()
{	
	int		i, k, i1, k1;

	int		Index[4];	// ������ �����
	REAL	lambda, gamma, px, y, xp, yp, hx, hy;	// ��������� ��
	REAL	tmp, hx2, hy2, ud, u1, u2, u3;

	REAL	fv[4];		// �������� ������ �����
	REAL	B[4][4];	// ������� ��������
	REAL	C[4][4];	// ������� ����
	REAL	F[4];		// ������ ������ �����

	// ��������� ��������������� ���������� �������
	for(k=0;k<Ny-1;k++)
		for(i=0;i<Nx-1;i++)
		{
			px = GridX[i];	// ������� �����
			y = GridY[k];

			// ������� �����
			xp = GridX[i+1];	
			yp = GridY[k+1];
            
			// ����
			hx = xp - px;		
			hy = yp - y;
			hx2 = hx * hx;
			hy2 = hy * hy;
            
			// ������������
			lambda	= GetLambda(px+hx/2.0,y+hy/2.0);	
			gamma	= GetGamma (px+hx/2.0,y+hy/2.0);
			
			// �������� ������ �����
			fv[0] = GetF(px,y);		
			fv[1] = GetF(xp,y);
			fv[2] = GetF(px,yp);
			fv[3] = GetF(xp,yp);

			// ����� �������� ������� ��������
			tmp = 1.0/(hx*hy);

			ud = (hx2+hy2)*tmp/3;
			u1 = (hx2-2*hy2)*tmp/6;
			u2 =-(2*hx2-hy2)*tmp/6; 
			u3 =-(hx2+hy2)*tmp/6;

			
			B[0][0] = ud;
			B[0][1] = u1;
			B[0][2] = u2;
			B[0][3] = u3;
			
			B[1][0] = u1;
			B[1][1] = ud;
			B[1][2] = u3;
			B[1][3] = u2;
			
			B[2][0] = u2;
			B[2][1] = u3;
			B[2][2] = ud;
			B[2][3] = u1;

			B[3][0] = u3;
			B[3][1] = u2;
			B[3][2] = u1;
			B[3][3] = ud;
 
			// ����� �������� ������� ����
			ud = hx*hy/9.0;
			u1 = hx*hy/18.0;
			u2 = u1;
			u3 = hx*hy/36.0;

			C[0][0] = ud;
			C[0][1] = u1;
			C[0][2] = u2;
			C[0][3] = u3;
			
			C[1][0] = u1;
			C[1][1] = ud;
			C[1][2] = u3;
			C[1][3] = u2;
			
			C[2][0] = u2;
			C[2][1] = u3;
			C[2][2] = ud;
			C[2][3] = u1;

			C[3][0] = u3;
			C[3][1] = u2;
			C[3][2] = u1;
			C[3][3] = ud;
            
            //����� �������� ������� ������ �����
			F[0] =	C[0][0]*fv[0]+C[0][1]*fv[1]+
					C[0][2]*fv[2]+C[0][3]*fv[3];
			F[1] =	C[1][0]*fv[0]+C[1][1]*fv[1]+
					C[1][2]*fv[2]+C[1][3]*fv[3];
			F[2] =	C[2][0]*fv[0]+C[2][1]*fv[1]+
					C[2][2]*fv[2]+C[2][3]*fv[3];
			F[3] =	C[3][0]*fv[0]+C[3][1]*fv[1]+
					C[3][2]*fv[2]+C[3][3]*fv[3];
            

			Index[0] = Nx * k   + i;
			Index[1] = Nx * k   + i+1;
			Index[2] = Nx *(k+1)+ i;
			Index[3] = Nx *(k+1)+ i+1;

			for(i1=0;i1<4;i1++)
			{
				for(k1=0;k1<4;k1++)
					AddToMatrix(Index[i1],Index[k1],lambda*B[i1][k1]+gamma*C[i1][k1]);
				f[Index[i1]] += F[i1];
			}	
		}

	// ���� ������� ������� ������� ����
	for(i=0;i<Nx;i++)			// ����������� ��� �
	{
		px	= GridX[i];
		y	= GridY[0];
		di[i]	= 1.0e+50;
		f[i]	= 1.0e+50 * GetIdeal(px,y);
		y	= GridY[Ny-1];
		di[Nx*(Ny-1)+i]	= 1.0e+50;
		f[Nx*(Ny-1)+i]	= 1.0e+50 * GetIdeal(px,y);
	}
	
	for(k=0;k<Ny;k++)			// ����������� ��� Y
	{
		y	= GridY[k];
		px	= GridX[0];
		di[k*Nx]	= 1.0e+50;
		f[k*Nx]		= 1.0e+50 * GetIdeal(px,y);
		px	= GridX[Nx-1];
		di[(k+1)*Nx-1]	= 1.0e+50;
		f[(k+1)*Nx-1]	= 1.0e+50 * GetIdeal(px,y);
	}
}

//	���������� ��������� � �������
void AddToMatrix(int i, int j, REAL el)
{
	int k;
	if (i==j) di[i]+=el;
	else
	{
		if(i>j)
		{
			for(k=ig[i];k<ig[i+1];k++)
				if(jg[k]==j) ggl[k]+=el;
		}
		else
		{
   			for(k=ig[j];k<ig[j+1];k++)
				if(jg[k]==i) ggu[k]+=el;
		}
	}
}

//	������������
int LU()
{
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=ig[i];j<ig[i+1];j++)
		{
			L[j]=(ggl[j]-sum(i,jg[j]));
			U[j]=(ggu[j]-sum(jg[j],i))/diag[jg[j]];
		}
	diag[i]=di[i]-sum(i,i);
	}
	return 0;
}

//	������� ������� ������������
void GaussL(REAL *in, REAL *out)
{
	int i,j;
	REAL result;
	for(i=0;i<N;i++)
	{
		result=0;
		for(j=ig[i];j<ig[i+1];j++)
		{
			result+=L[j]*out[jg[j]];
		}
		out[i]=(in[i]-result)/diag[i];
	}
}

//	������� �������� ������������
void GaussU(REAL *in, REAL *out)
{
	int i,j;
	for(i=0;i<N;i++) out[i]=in[i];
	for(i=N-1;i>=0;i--)
	{
		for(j=ig[i];j<ig[i+1];j++)
		{
			out[jg[j]]-=U[j]*out[i];
		}
	}
}

//	��������� ������� �� ������
void MultMatrixOnVector(REAL *in, REAL *out)
{
	int i,j;
	REAL *out1;
	out1 = new REAL[N];
	for(i=0;i<N;i++)
	{
		out1[i]=di[i]*in[i];
		for(j=ig[i];j<ig[i+1];j++)
		{
			out1[i]+=ggl[j]*in[jg[j]];
			out1[jg[j]]+=ggu[j]*in[i];
		}
	}

	for(i=0;i<N;i++)
		out[i]=out1[i];
	delete [] out1;
}

//	��������� ������������
REAL ScalarMult(REAL *v1, REAL *v2)
{
	int i;
	REAL result;
	result = 0;
	for(i=0;i<N;i++)
	{
		result+=v1[i]*v2[i];
	}
	return result;
}

//	��������� ������������ ��� ������������
REAL sum(int i,int j)
{
	int k,l,find;
	REAL result;
	result=0.0;
	if(i==j)
	{
		for(k=ig[i];k<ig[i+1];k++)
			result+=U[k]*L[k];
	}
	else
	{
		// ������� �����������
		if(i>j)
		{
			for(k=ig[j];k<ig[j+1];k++)
			{
				find=0;
				for(l=ig[i];l<ig[i+1]&&find==0;l++)
				{
					if(jg[l]==jg[k])
					{
						result+=U[k]*L[l];
						find=1;
					}
				}
			}
		}
		// ������ �����������
		else
		{
			for(l=ig[i];l<ig[i+1];l++)
			{
				find=0;
				for(k=ig[j];k<ig[j+1]&&find==0;k++)
				{
					if(jg[l]==jg[k])
					{
						result+=U[k]*L[l];
						find=1;
					}
				}
			}
		}
  
	}
	return result; 
}


//	�������� ������� ������
void run()
{
	int iter;
	int i,check,stop;
	REAL alpha,alphazn,alphach,beta,betach,betazn,CheckExit;

	// ������������
	check = LU();
	if(check!=0) cout << "������ ��������� ������������!" << check+1 << endl;

	// �������������
	stop=0;
	for(i=0; i<N; i++) x[i]=0;
	GaussL(f,r);
	GaussU(r,z);
	MultMatrixOnVector(z,q);
	GaussL(q,p);

	// ������� ������� ����
	for(iter=0;iter<MAXITER && stop==0;iter++)
	{
		alphach=ScalarMult(p,r);
		alphazn=ScalarMult(p,p);
		alpha=alphach/alphazn;
		for(i=0;i<N;i++) x[i]+=alpha*z[i];
		for(i=0;i<N;i++) r[i]-=alpha*p[i];
		GaussU(r,s);
		MultMatrixOnVector(s,sout);
		GaussL(sout,q);
		betazn=ScalarMult(p,p);
		betach=ScalarMult(p,q);
		beta=-betach/betazn;
		//GaussU(r,s);
		for(i=0;i<N;i++) z[i]=beta*z[i]+s[i];
		for(i=0;i<N;i++) p[i]=beta*p[i]+q[i];
		CheckExit=ScalarMult(r,r);
		if(CheckExit<EPS) stop=1;
	}
}


void result()
{
	int i, k, num = 0;
	REAL px, y, func, res = 0.0, norm = 0.0, tmp;

	ofstream output("result.txt");
	output << "X" << setw(STR+8) << "Y" << setw(STR+8) 
		   << "U" << setw(STR+8) << "U*"<< setw(STR+8) << "U* - U" << endl;
		   
	for(k=0;k<Ny;k++)
		for(i=0;i<Nx;i++) 
		{
			px = GridX[i];
			y = GridY[k];
			func = GetIdeal(px,y);
			tmp = fabs(x[num]-func);
			res += tmp * tmp;
			norm += func * func;

			output << setprecision(STR) << px 
				   << setw(STR+8) << y 
			       << setw(STR+8) << x[num]
			       << setw(STR+8) << func; 
			output << setw(STR+8) << tmp << endl;
			num++;
		}
		output << "\n ||U-U*|| / ||U*|| = " << scientific << sqrt(res/norm) << endl;
	output.close() ;
} 

//	������� �������
int main()
{
	setlocale(LC_CTYPE,"russian");
	method();
	run();
    result();
	return 0;
}