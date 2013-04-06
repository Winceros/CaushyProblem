// CaushyProblem.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

double getF1(double x, double y1, double y2) {
	return -y2 + y1*(y1*y1 + y2*y2 - 1);
}

double getF2(double x, double y1, double y2) {
	return y1 + y2*(y1*y1 + y2*y2 - 1);
}

vector<double> Exact(double a, double b, double h) {
	FILE *f_t;
	f_t = fopen("_exact.txt","w");

	vector<double> res;
	for(double x = a ; x <= b; x+=h) {
		double y1 = cos(x)/sqrt(1+exp(2*x));
		double y2 = sin(x)/sqrt(1+exp(2*x));
		res.push_back(y1);
		res.push_back(y2);
		fprintf(f_t,"%9f\t%9f\t%9f\n",x,y1,y2);
	}
	fclose(f_t);
	return res;
}

vector<double> RungeKuttMethod(double a, double b, double h) {
	FILE *f_rk;
	f_rk = fopen("_rungekutt.txt","w");
	
	vector<double> res;
	double y1 = cos(a)/sqrt(1+exp(2*a));
	double y2 = sin(a)/sqrt(1+exp(2*a));
	res.push_back(y1);
	res.push_back(y2);
	fprintf(f_rk,"%9f\t%9f\t%9f\n",a,y1,y2);

	for(double x = a+h ; x <= b; x+=h) {
		double k1_1 = getF1(x,y1,y2);
		double k2_1 = getF1(x + h/2, y1 + h*k1_1/2, y2 + h*k1_1/2);
		double k3_1 = getF1(x + h/2, y1 + h*k2_1/2, y2 + h*k2_1/2);	
		double k4_1 = getF1(x + h, y1 + h*k3_1, y2 + h*k3_1);
		y1 = y1 + h*(k1_1 + 2*k2_1 + 2*k3_1 + k4_1)/6;
		
		double k1_2 = getF2(x,y1,y2);
		double k2_2 = getF2(x + h/2, y1 + h*k1_2/2, y2 + h*k1_2/2);
		double k3_2 = getF2(x + h/2, y1 + h*k2_2/2, y2 + h*k2_2/2);
		double k4_2 = getF2(x + h, y1 + h*k3_2, y2 + h*k3_2);		
		y2 = y2 + h*(k1_2 + 2*k2_2 + 2*k3_2 + k4_2)/6;
		
		res.push_back(y1);
		res.push_back(y2);
		fprintf(f_rk,"%9f\t%9f\t%9f\n",x,y1,y2);
	}
	fclose(f_rk);
	return res;
}

double maxVecDelta(vector<double> v1, vector<double> v2) {
	int len = v1.size();
	double maxDelta = abs(v1[0] - v2[0]);
	for(int i=1 ; i<len ; i++) {
		double eps = abs(v1[i] - v2[i]);
		if( eps > maxDelta )
			maxDelta = eps;
	}
	return maxDelta;
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *f_eps;
	f_eps = fopen("max_eps(h).txt","w");
	vector<double> rungeKutt;
	vector<double> exact;
	for(double h = 0.0001; h<=0.1 ; h+=0.003) {
		//cout<<h<<endl;
		rungeKutt = RungeKuttMethod(0,5,h);
		exact = Exact(0,5,h);
		fprintf(f_eps,"%f\t%9f\n",h,maxVecDelta(rungeKutt, exact));
	}
	fclose(f_eps);
	return 0;
}

