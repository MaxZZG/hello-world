
/*

	此程序为读入节点数据

	返回数组时使用静态变量

*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>


using namespace std;




//				计算形函数，返回指针，数组首地址
//				这段程序没问题，局部变量也很合理

double *ShapeFunction(double s,double t)		//s,t为局部坐标
{
	static double N[4];						//		必须有static，防止出错
	N[0] = (1 - s)*(1 - t) / 4;
	N[1] = (1 + s)*(1 - t) / 4;
	N[2] = (1 - s)*(1 + t) / 4;
	N[3] = (1 + s)*(1 + t) / 4;
	return N;
}

//			形函数求导
//			这段也没问题

double *DiffShape(double s, double t)			//s,t是局部坐标
{
	static double Ns[8];			//		static

	Ns[0] = -(1 - t) / 4;	//  N1对s求导
	Ns[1] = (1 - t) / 4;	//  N2对s求导
	Ns[2] = (1 + t) / 4;	//  N3对s求导
	Ns[3] = -(1 + t) / 4;	//  N4对s求导
	Ns[4] = -(1 - s) / 4;	//	N1对t求导
	Ns[5] = -(1 + s) / 4;	//	N2对t求导
	Ns[6] =  (1 + s) / 4;	//	N3对t求导
	Ns[7] =  (1 - s) / 4;	//	N4对t求导
	
	return Ns;
}

//			求雅可比矩阵
//			没有问题

double **Jacobi(double x1,double y1,double x2,double y2, double x3, double y3, double x4, double y4, double s, double t)
{
	//		单元坐标
	double X[4] = { x1,x2,x3,x4 };
	double Y[4] = { y1,y2,y3,y4 };
	static double **J;					//		static
	//		求形函数的导数

	double Ns[8];
	

	for (int i = 0; i < 8; i++)
	{
		Ns[i]= *(DiffShape(s, t)+i);
		//cout << Ns[i]<<"  ";			//测试
	}

	//		初始化雅可比矩阵
	J = (double **)malloc(2 * sizeof(double));
	for (int i = 0; i < 2; i++)
	{
		J[i] = (double *)malloc(2 * sizeof(double));
		for (int j = 0; j < 2; j++)
		{
			J[i][j] = 0;
		}

	}

	//求雅可比矩阵
	double J1=0, J2=0, J3=0, J4=0;



	for (int i = 0; i < 4; i++)
	{
		J1 = J1 + Ns[i] * X[i];
		J2 = J2 + Ns[i] * Y[i];
		J3 = J3 + Ns[i + 4] * X[i];
		J4 = J4 + Ns[i + 4] * Y[i];
	}

	J[0][0] = J1;
	J[0][1] = J2;
	J[1][0] = J3;
	J[1][1] = J4;

	//	cout << (J1*J4 - J2 * J3) << endl;
	return J;
}

//			求几何矩阵
//			好像是没有问题了

double **BMatrix(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double s, double t)
{
	static double **B;							//			static			
	double J[2][2];
	double Ns[8];
	
	for (int i = 0; i < 8; i++)
	{
		Ns[i] = *(DiffShape(s, t) + i);
		//cout << Ns[i] << "  ";				//测试
	}
		//cout << endl;							//测试
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			J[i][j] = *(*(Jacobi(x1,y1,x2,y2,x3,y3,x4,y4,s,t)+i) + j);

			//cout << J[i][j] << endl;			//做测试用
		}
	}

	//			求雅可比矩阵行列式

	double detJ = 0;
	detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];
	//cout<<(detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1])<<endl; //测试



	//		初始化几何矩阵
	B = (double **)malloc(3 * sizeof(double));

	for (int i = 0; i < 3; i++)
	{
		B[i] = (double *)malloc(8 * sizeof(double));
		for (int j = 0; j < 8; j++)
		{
			B[i][j] = 0;
		}
	}



	//		求几何矩阵
	//		B为3x8矩阵

	B[0][0] = (J[1][1] * Ns[0] - J[0][1] * Ns[4])/detJ;
	B[0][2] = (J[1][1] * Ns[1] - J[0][1] * Ns[5])/detJ;
	B[0][4] = (J[1][1] * Ns[2] - J[0][1] * Ns[6]) / detJ;
	B[0][6] = (J[1][1] * Ns[3] - J[0][1] * Ns[7]) / detJ;
	B[1][1] = (-J[1][0] * Ns[0] + J[0][0] * Ns[4]) / detJ;
	B[1][3] = (-J[1][0] * Ns[1] + J[0][0] * Ns[5]) / detJ;
	B[1][5] = (-J[1][0] * Ns[2] + J[0][0] * Ns[6]) / detJ;
	B[1][7] = (-J[1][0] * Ns[3] + J[0][0] * Ns[7]) / detJ;

	for (int i = 0; i < 8; i=i+2)
	{
		B[2][i] = B[1][i + 1];
		B[2][i + 1] = B[0][i];

	}
	/*			//做测试用
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << B[i][j] << "  ";
		}
		cout << endl;
	}
	*/
	
	return B;

	

}


//				单元刚度矩阵
//				运行没问题


double **ElementStiffness(double E,double u,double h,double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	//				单元刚度矩阵为8x8矩阵
	//				E ：弹性模量；u ：泊松比；h：厚度
	//				弹性矩阵 D

	double D[3][3] = { E / (1 - u * u) ,E * u / (1 - u * u) , 0, E * u / (1 - u * u) ,E / (1 - u * u) , 0, 0, 0,(1 - u)*E / (2 * (1 - u * u)) };


	//				初始化单元刚度矩阵

	static double **Ke;		//	8x8矩阵

	Ke = (double **)malloc(8 * sizeof(double));
	for (int i = 0; i < 8; i++)
	{
		Ke[i] = (double *)malloc(8 * sizeof(double));
		for (int j = 0; j < 8; j++)
		{
			Ke[i][j] = 0;
		}

	}

	//				高斯积分

	int W[2] = { 1,1 };																	//加权系数
	double x[2] = { -0.577350 , 0.577350 };	//积分点

	//cout << x[1] << endl;		//		测试

	double B[3][8], Bt[8][3];				//  定义几何矩阵及其转置
	double J[2][2];							//  定义雅可比矩阵
	double detJ = 0;	
	double BtD[8][3];

	//				初始化BtD

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			BtD[i][j] = 0;
		}
	}

	//		对四个积分点进行高斯积分，求解单元刚度矩阵

	for (int a = 0; a < 2; a++)
	{
		for (int b = 0; b < 2; b++)
		{

			//				初始化BtD
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					BtD[i][j] = 0;
				}
			}

			//				求几何矩阵B及其转置矩阵

			for (int s = 0; s < 3; s++)
			{
				for (int k = 0; k < 8; k++)
				{
					B[s][k] = *(*(BMatrix(x1, y1, x2, y2, x3, y3, x4, y4, x[a], x[b])+s)+k);
				}
			}
							//	B 转置矩阵Bt

			for (int s = 0; s < 3; s++)
			{
				for (int k = 0; k < 8; k++)
				{

					Bt[k][s] = B[s][k];

				}
			}

			//			求雅可比矩阵 J	以及detJ

			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					J[i][j] = *(*(Jacobi(x1, y1, x2, y2, x3, y3, x4, y4, x[a], x[b]) + i) + j);
				}
			}
			detJ = J[0][0] * J[1][1] - J[1][0] * J[0][1];
			//cout << detJ << endl;

			//			B的转置×D  BtD

			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						BtD[i][j] = BtD[i][j]+Bt[i][k] * D[k][j];
					}
				
				}

			}

			//			求单元刚度矩阵


			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						Ke[i][j] = Ke[i][j] + BtD[i][k] * B[k][j]*detJ*h*W[a]*W[b];
						
					}
					
				}
				
			}


		}
	}

	return Ke;

}

/*

	主函数
	整体刚度矩阵的整合在主函数里


*/

int main()
{
	//			先跑起来，之后把节点坐标数组和单元节点数组都改成动态分配的方式

	double **a; //节点坐标数组
	int **c;    //单元节点
	
	string nouse,nouse1;

	int j = 0,i = 0,m = 0 ,k = 0 , d = 0, countEle = 0, countGrid = 0;

    
	ifstream infile;
	infile.open("E:\\k.txt",ios::in);
	if (!infile)
	{
		cout << "fail to open file" << endl;
		return -1;
	}

	ifstream infile1;
	infile1.open("E:\\k.txt", ios::in);
	if (!infile1)
	{
		cout << "fail to open file" << endl;
		return -1;
	}
	//			判断文件的数据量

	//			收集数据以动态分配节点坐标数组、单元节点数组
	int counta = 0, countc = 0;			//			counta,countb用来收集数据

	while (nouse != "ENDDATA")
	{
		infile >> nouse;
		if (nouse == "GRID")
			counta++;
		if (nouse == "CQUAD4")
			countc++;

		d++;
	}

	cout << d << endl;

	//			有了counta，countc，可以对a,c动态分配了

	infile.seekg(0);			//		流指针回到文件头

	//		对a进行动态分配并且初始化

	a = (double **)malloc(counta * sizeof(double));
	for (int i = 0; i < counta; i++)
	{
		a[i] = (double *)malloc(3 * sizeof(double));
		for (int j = 0; j < 3; j++)
		{
			a[i][j] = 0;
		}
	}

	//		对c进行初始化

	c = (int **)malloc(countc * sizeof(int));
	for (int i = 0; i < countc; i++)
	{
		c[i] = (int *)malloc(4 * sizeof(int));
		for (int j = 0; j < 4; j++)
		{
			c[i][j] = 0;
		}
	}



	//			将文件流中数据导入a中
	//			成功实现

	nouse = "0",nouse1="0";
	infile1 >> nouse1;
	

	while (nouse != "ENDDATA")
	{
		infile >> nouse;
		infile1 >> nouse1;
		

		if (nouse == "$$" || nouse == "$")
		{
			infile >> nouse;
			infile1 >> nouse1;
			continue;
		}
		if (nouse == "GRID"&& nouse1 == "Data")
		{
			infile >> nouse;
			infile1 >> nouse1;
			continue;
		}
		
		if (nouse == "GRID"&& nouse1 == "1")
		{
			infile >> nouse;
			infile1 >> nouse1;
			continue;
		}

		if (nouse == "GRID"&& nouse1 == "2")
		{
			
				infile >> nouse;
				infile1 >> nouse1;
			
			continue;
		}

		if (nouse == "GRID"&& nouse1 == "3")
		{
			infile >> nouse;
			infile1 >> nouse1;
			continue;
		}

		if (nouse == "GRID"&& nouse1 == "4")
		{
			infile >> nouse;
			infile1 >> nouse1;
			continue;
		}

		if (nouse == "GRID")
		{
			
			infile >> nouse;
			infile1 >> nouse1;
			for (m = 0; m < 3; m++)
			{
				infile >> nouse;
				infile1 >> nouse1;
				stringstream ss;
				ss << nouse;
				ss >> a[countGrid][m];
				cout << a[countGrid][m] << "  ";
			}
			
			countGrid++;
			cout << endl;
		}
	}

	//				根据节点数定义载荷矩阵

	double *F;
	F = (double *)malloc(2 * countGrid * sizeof(double));
	for (int i = 0; i < 2 * countGrid; i++)
	{
		F[i] = 0;
	}

	nouse = "0", nouse1 = "0";
	infile.seekg(0);			//		又回到最初的起点


	//			跳过第一个FORCE

	while (nouse!="FORCE")
	{
		infile >> nouse;
	
	}

	while (nouse != "ENDDATA")
	{
		infile >> nouse;
		
		double DXtem = 0;		//		局部变量传输数据的
		double DYtem = 0;
		if (nouse == "FORCE")
		{
			infile >> nouse;
			infile >> nouse;
			stringstream sf;
			sf << nouse;
			sf >> k;
			infile >> nouse;
			infile >> nouse;
			stringstream sf1;
			sf1 << nouse;
			sf1 >> DXtem;
			infile >> nouse;
			stringstream sf2;
			sf2 << nouse;
			sf2 >> DYtem;
		}
		F[2 * k - 2] = F[2 * k - 2] + DXtem;
		F[2 * k - 1] = F[2 * k - 1] + DYtem;
	}
	
	for (int i = 0; i < 2 * countGrid; i++)
	{
		cout<<F[i]<<"   " ;
	}











		//		根据节点数定义总体刚度矩阵
		//		初始化总体刚度矩阵


	long double **K;
	K = (long double **)malloc( 2* countGrid * sizeof(long double));
	for (i = 0; i < 2 * countGrid ; i++)
	{
		K[i] = (long double *)malloc(2 * countGrid * sizeof(long double));
		for (j = 0; j < 2 * countGrid; j++)
		{
			K[i][j] = 0;
		}
	}


	//将b中的数据读入c中
	nouse = "0", nouse1 = "0";

	infile.seekg(0);
	infile1.seekg(0);

	//			跳过第一次CQUAD4

	infile1 >> nouse1;
	while (nouse != "CQUAD4")
	{
		infile >> nouse;
		infile1 >> nouse1;
	}


	while(nouse!="ENDDATA")
	{
		infile >> nouse;
		infile1 >> nouse1;
		
		if ((nouse == "CQUAD4" ))
		{
			infile >> nouse;
			infile1 >> nouse1;
			stringstream sa;
			sa << nouse;
			sa >> k;
			
				infile >> nouse;
				infile1 >> nouse1;
			
			for (m = 0; m < 4; m++)
			{
				infile >> nouse;
				infile1 >> nouse1;
				stringstream ss;
				ss << nouse;
				ss >> c[k-1][m];
				//cout << c[k-1][m] << "  ";
					
			}
			countEle++;
			//cout << endl;
			
		}
	}



	for (i = 0; i < countEle; i++)
	{
		for (m = 0; m < 4; m++)
		{
			c[i][m] = c[i][m] - 4;
			cout << c[i][m] << "  ";
		}
		cout << endl;
	}

	//cout << countEle << endl;		//此时countEle为单元数


	//				求总体刚度矩阵
	
	

	//				单元刚度矩阵

	double Ke[8][8];

	for (int q = 0; q < 8; q++)
	{
		for (int w = 0; w < 8; w++)
		{
			Ke[q][w] = 0;
		}
		
	}
	
	for (i = 0; i < countEle; i++)				//		k个单元求k次单元刚度矩阵
	{
			for (int q = 0; q < 8; q++)
			{
				for (int w = 0; w < 8; w++)
				{
					
					Ke[q][w] = *(*(ElementStiffness(30000000, 0.3, 1, a[c[i][0] - 1][0], a[c[i][0] - 1][1], a[c[i][1] - 1][0], a[c[i][1] - 1][1], a[c[i][2] - 1][0], a[c[i][2] - 1][1], a[c[i][3] - 1][0], a[c[i][3] - 1][1]) + q) + w);
					//cout << Ke[q][w]<<" ";
				}
				//cout << endl;
			}
			
				//			整合到总体刚度矩阵中

		for(j = 0; j < 4; j++)
		{
			for (int p = 0; p < 4; p++)
			{
				
				K[2 * c[i][j]-2][2 * c[i][p]-2] = Ke[2 * j][2 * p]+ K[2 * c[i][j] - 2][2 * c[i][p] - 2];
				K[2 * c[i][j]-2][2 * c[i][p]-2 + 1] = Ke[2*j][2*p+1]+ K[2 * c[i][j] - 2][2 * c[i][p] - 2 + 1];
				K[2 * c[i][j]-2+ 1][2 * c[i][p]-2] = Ke[2*j+1][2*p]+ K[2 * c[i][j] - 2 + 1][2 * c[i][p] - 2];
				K[2 * c[i][j]-2 + 1][2 * c[i][p] -2+ 1] = Ke[2*j+1][2*p+1]+ K[2 * c[i][j] - 2 + 1][2 * c[i][p] - 2 + 1];
				
			}
		}
	}
	cout << endl;

	ofstream fout;
	fout.open("E:\\text.txt", ios::out);
	if (!fout)
	{
		cout << "不能创建整体刚度输出文件"<< endl;
	}
	for (i = 0; i < countGrid * 2; i++)
	{
		for (j = 0; j < countGrid * 2; j++)
		{
			fout << K[i][j] << "\t";
		}
		fout << endl;
	}

	//			整体刚度矩阵应该是对称阵，这个已经实现了。


		/*
				读入约束数据，进行约束处理，使用乘大数法
		*/

	infile.seekg(0);
	nouse = "0";

	int Bound;
	
	double big = 10e100;

	/*
				跳过第一个SPC
	*/
	while (nouse != "ENDDATA")				//		这层循环是为了防止没有约束的情况下成为死循环
	{
		while (nouse != "SPC")
		{
			infile >> nouse;
		}

		while (nouse != "ENDDATA")
		{
			infile >> nouse;
			if (nouse == "SPC")
			{
				infile >> nouse;
				infile >> nouse;

				stringstream ss;
				ss << nouse;
				ss >> Bound;

				/*
							乘大数法
				*/

				K[2 * Bound - 2][2 * Bound - 2] = big * K[2 * Bound - 2][2 * Bound - 2];
				K[2 * Bound - 1][2 * Bound - 1] = big * K[2 * Bound - 1][2 * Bound - 1];
				F[2 * Bound - 2] = 0;
				F[2 * Bound - 1] = 0;

			}
		}
	}

	/*
	
				下一步就是借线性方程组了。先整理整理代码,整刚矩阵终于没问题了，开始解线性方程组

	
	*/

	/*
				解方程组,用Cholesky分解法
				有精力的话就改成改进型的cholesky分解法


	*/

	//			定义L

	double **L;
	L = (double **)malloc(2 * countGrid * sizeof(double));
	for (i = 0; i < 2 * countGrid; i++)
	{
		L[i] = (double *)malloc(2 * countGrid * sizeof(double));
		for (j = 0; j < 2 * countGrid; j++)
		{
			L[i][j] = 0;
		}
	}

	/*
				cholesky分解法,经过验证，此分解法已经没有问题，此方法弃用。总刚矩阵还是不对，依然是非正定
				使用改进的cholesky分解法

				（1）求 K 的Cholesky分解，得到 L*Lt = K

				（2）求解 L*Y = F，得到 Y

				（3）求解 Lt* X = Y，得到 X


	*/

	L[0][0] = pow(K[0][0], 0.5);



	//			第一列的元素
	//			i 是行

	double sum = 0, sum1 = 0;

	for (i = 1; i < 2 * countGrid; i++)
	{
		L[i][0] = K[i][0] / L[0][0];

	}

	//			已知第一列，求余下的列,第一列求对了
	//			j是列



	for (j = 1; j < 2 * countGrid; j++)
	{

		sum = 0;
		//		先求sum
		for (i = 0; i < j; i++)
		{
			sum = sum + L[j][i] * L[j][i];
		}

		L[j][j] = pow((K[j][j] - sum), 0.5);


		for (k = j + 1; k < 2 * countGrid; k++)
		{
			sum1 = 0;
			for (i = 0; i < j; i++)
			{
				sum1 = sum1 + L[k][i] * L[j][i];
			}

			L[k][j] = (K[k][j] - sum1) / L[j][j];

		}
	}

	/*

				转置 L 得到 Lt
	*/


	double **Lt;
	Lt = (double **)malloc(2 * countGrid * sizeof(double));
	for (i = 0; i < 2 * countGrid; i++)
	{
		Lt[i] = (double *)malloc(2 * countGrid * sizeof(double));
		for (j = 0; j < 2 * countGrid; j++)
		{
			Lt[i][j] = 0;
		}
	}

	for (i = 0; i < 2 * countGrid; i++)
	{
		for (j = 0; j < 2 * countGrid; j++)
		{
			Lt[i][j] = L[j][i];
		}
	}

	/*

				输出 L 文件做检查

	*/
	/*
	ofstream fLout;
	fLout.open("E:\\text1.txt", ios::out);
	if (!fLout)
	{
		cout << "不能创建L输出文件" << endl;
	}
	for (i = 0; i < countGrid * 2; i++)
	{
		for (j = 0; j < countGrid * 2; j++)
		{
			fLout << L[i][j] << "\t";
		}
		fLout << endl;
	}
	*/
	/*

				L 已经求出了，下面开始求 Y

	*/

	double *Y;
	Y = (double *)malloc(2 * countGrid * sizeof(double));
	for (i = 0; i < 2 * countGrid; i++)
	{
		Y[i] = 0;
	}

	for (i = 0; i < 2 * countGrid; i++)
	{
		sum = 0;
		for (j = 0; j < i; j++)
		{
			sum = sum + L[i][j] * Y[j];
		}
		Y[i] = (F[i] - sum) / L[i][i];
		//cout << Y[i] << endl;
	}

	/*
					求X

	*/

	long double *X;
	X = (long double *)malloc(2 * countGrid * sizeof(long double));
	for (i = 0; i < 2 * countGrid; i++)
	{
		X[i] = 0;
	}

	for (i = 2 * countGrid - 1; i >= 0; i--)
	{
		sum = 0;
		for (j = 2 * countGrid - 1; j > i; j--)
		{
			sum = sum + Lt[i][j] * X[j];
		}
		X[i] = (Y[i] - sum) / Lt[i][i];
		//cout << X[i] << endl;
	}


	/*
	
				至此，位移矩阵X求出，但是还有很多问题
				上面的方法不够精确，已弃用，数据已经被下面改进型的cholesky分解法代替


	*/

	/*
	
				使用改进型的cholesky算法
				因为在计算过程中有比较大的误差，所以需要后边误差处理
				但是刚度矩阵是qi
	
	*/

	double **D;				//		D 是正对角矩阵

	//						初始化D

	D = (double **)malloc(2 * countGrid * sizeof(double));
	for (i = 0; i < 2 * countGrid; i++)
	{
		D[i] = (double *)malloc(2 * countGrid * sizeof(double));
		for (j = 0; j < 2 * countGrid; j++)
		{
			D[i][j] = 0;
		}
		
	}
	//					初始化 L
	for (i = 0; i < 2 * countGrid; i++)
	{
		for (j = 0; j < 2 * countGrid; j++)
		{
			L[i][j] = 0;
		}
	}
	//					初始化 Lt
	for (i = 0; i < 2 * countGrid; i++)
	{
		for (j = 0; j < 2 * countGrid; j++)
		{
			Lt[i][j] = 0;
		}
	}


	//			k 是列 , j 是行
	
	for (k = 0; k < 2 * countGrid; k++)
	{
		sum = 0;
		for (int m = 0; m <= k - 1; m++)
		{
			sum = sum + L[k][m] * L[k][m] * D[m][m];
		}

		D[k][k] = K[k][k] - sum;
		
		for (j = k ; j < 2 * countGrid; j++)
		{
			sum1 = 0;
			for (int m = 0; m < k - 1; m++)
			{
				sum1 = sum1 + L[j][m] * L[k][m] * D[m][m];
			}

			L[j][k] = ( K[j][k] - sum1 ) / D[k][k];

		}
		//cout <<D[k][k]<< endl;
	}
	


	for (k = 0; k < 2 * countGrid; k++)
	{
		L[k][k] = 1;
	}

	for (i = 0; i < 2 * countGrid; i++)
	{
		for (j = 0; j < 2 * countGrid; j++)
		{
			Lt[i][j] = L[j][i];
			//cout << Lt[i][j] << "  ";
		}
		//cout << endl;
	}


	/*
			求Y
	*/

	for (i = 0; i < 2 * countGrid; i++)
	{
		Y[i] = 0;
	}

	for (i = 0; i < 2 * countGrid; i++)
	{
		sum = 0;
		for (j = 0; j < i; j++)
		{
			sum = sum + L[i][j] * Y[j];
		}
		Y[i] = (F[i] - sum) / L[i][i];
		//cout << Y[i] << endl;
	}

	double **DLt;				//		D 是正对角矩阵

	//						初始化D

	DLt = (double **)malloc(2 * countGrid * sizeof(double));
	for (i = 0; i < 2 * countGrid; i++)
	{
		DLt[i] = (double *)malloc(2 * countGrid * sizeof(double));
		for (j = 0; j < 2 * countGrid; j++)
		{
			DLt[i][j] = 0;
		}

	}

	for (i = 0; i < 2 * countGrid; i++)
	{
		for (j = 0; j < 2 * countGrid; j++)
		{
			for (k = 0; k < 2 * countGrid; k++)
			{
				DLt[i][j] = DLt[i][j] + D[i][k]*Lt[k][j] ;
				
			}
			//cout << DLt[i][j] << "  ";
			
		}
		//cout << endl;
	}

	

	for (i = 0; i < 2 * countGrid; i++)
	{
		X[i] = 0;
	}

	for (i = 2 * countGrid - 1; i >= 0; i--)
	{
		sum = 0;
		for (j = 2 * countGrid - 1; j > i; j--)
		{
			sum = sum + DLt[i][j] * X[j];
		}
		X[i] = (Y[i] - sum) / DLt[i][i];
		
	}
	for (i = 0; i < 2 * countGrid; i++)
	{
		cout << X[i] << endl;
	}

	/*
				将结果输出到文件中，输出单元节点坐标和节点位移，好画图
	*/

	
	ofstream fLout;
	fLout.open("E:\\text1.txt", ios::out);
	if (!fLout)
	{
		cout << "不能创建L输出文件" << endl;
	}
	fLout << "weiyi" << endl;
	for (i = 0; i < countGrid * 2; i++)
	{
		fLout << X[i] << endl;
	}

	fLout << "输出力以验证结果正确性" << endl;

	for (i = 0; i < 2 * countGrid; i++)
	{
		fLout << i << "\t" << F[i] << endl;
	}


	for (i = 0; i < 2 * countGrid; i++)
	{
		cout << F[i] << endl;
	}


	/*
	
				老师给的umfpack文件已经包含进来了，现在探索怎么用
				失败了
	
	*/
	/*
	
				用jacobi迭代法
	
	*/

	
	double s1, s2;
	k = 0;

	for (i = 0; i < 2 * countGrid; i++)
	{
		X[i] = 0;
	}
	do
	{
		s2 = 0;
		k = k + 1;
		for (i = 0; i < 2*countGrid; i++)
		{
			s1 = 0;
			for (j = 0; j < 2*countGrid; j++)
			{
				if (i == j)
					continue;
				s1 += K[i][j] * X[j];
			}
			Y[i] = (F[i] - s1) / K[i][i];
			s2 += fabs(X[i] - Y[i]);
		}
		if (s2 < 1e-20)
			cout << "迭代次数K=" << k << endl;
		if (k > 10000)
		{
			cout << "不收敛" << endl;
		}
		for (i = 0; i <2* countGrid; i++)
		{
			X[i] = Y[i];
		}
		/*
		for (i = 0; i < 2*countGrid; i++)
		{
			cout << X[i] << "  ";
		}
		*/
	} while (s2 > 1e-20);


	for (i = 0; i < 2 * countGrid; i++)
	{
		cout << X[i] << "  ";
	}

	



	infile.close();
	infile1.close();
	fLout.close();
	fout.close();
	return 0;

}

