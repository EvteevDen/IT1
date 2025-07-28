#include"pch.h"
#include "Sign.h"


#define PI 3.1415926535897


using namespace std;



Signal::Signal(double A1, double A2, double A3, double f1, double f2, double f3, double fi1 , double fi2, double fi3, double fd, int N, double a, double g)
{

	this->fd = fd;
	
	this->A1 = A1;
	this->A2 = A2;
	this->A3 = A3;
	
	this->f1 = f1;
	this->f2 = f2;
	this->f3 = f3;
	
	this->fi1 = fi1;
	this->fi2 = fi2;
	this->fi3 = fi3;
	this->N = N;
	this->a = a;
	this->g = g;


	for (int i = 0; i < N; i++)
	{
		signal.push_back(this->X(i));
		noise_signal.push_back(this->X(i));
	}
	for (vector<double>::iterator j = this->signal.begin(); j != this->signal.end(); ++j)
	{
		Es_Sign += *j * *j;
	}

		
}

Signal::~Signal()
{
	
}


double Signal::  X (int i)
{
	
	return double(A1 * sin(2 * PI * f1 * i / fd + fi1) + A2 * sin(2 * PI * f2 * i / fd + fi2) + A3 * sin(2 * PI * f3 * i / fd + fi3));
}



vector<double> Signal::Get_Vec_Sign()
{
	return this->signal;
}

vector<double> Signal::Get_Vec_Noise_Sign()
{
	return this->noise_signal;
}

vector<double> Signal::Get_Vec_Furye()
{
	return this->furye;
}

vector<double> Signal::Get_Vec_Clear_Sign()
{
	return this->clear_signal;
}



vector<double> Signal::Get_Vec_Furye_Complex()
{
	vector<double> temp;
	for (int i = 0; i < N; i++)
	{
		temp.push_back(sqrt(furye_complex[i].real() * furye_complex[i].real() + furye_complex[i].imag() * furye_complex[i].imag()));
	}
	return temp;
}




void Signal::GaussNoise()
{
	srand(time(NULL));
	double **n0 = new double*[N];
	double **n = new double*[N];
	double En0 = 0;

	for (int i = 0; i < N; i++)
	{
		n0[i] = new double[12];
		n[i] = new double[12];
	}
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			n0[i][j] = 0.001 * ((rand() % 2000) - 1000);
			En0 += n0[i][j] * n0[i][j];

		}
	}

	double b = sqrt(a * Es_Sign / En0);
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			n[i][j] = b * n0[i][j];
			noise_signal[i] += n[i][j];

		}
	}
}



void Signal::ClearSignal()
{
	double Es_temp = 0;
	

	double Es = Es_Furye * g;

	for (int i = 0; i < furye.size(); i++)
	{
		Es_temp += furye[i] * furye[i] + furye[N - i - 1] * furye[N - i - 1];
		if (Es_temp > Es)
		{
			for (int j = i; j < furye.size() - i; j++)
			{
				this->furye_complex[j] = 0;
				this->furye[j] = 0;
			}
			return;
		}



	}

}

bool PowerOfTwo(int Value)
{
	int InitValue = 1;
	while (InitValue < Value)
		InitValue *= 2;
	if (InitValue == Value)
		return true;
	return false;
}

double FindMax(vector<double> vec)
{
	double max = *vec.begin();
	for (vector<double>::iterator i = vec.begin(); i != vec.end(); ++i)
	{
		if (*i > max)
		{
			max = *i;
		}
	}
	return max;
}

int rev(int num, int lg_n) {
	int res = 0;
	for (int i = 0; i < lg_n; ++i)
		if (num & (1 << i))
			res |= 1 << (lg_n - 1 - i);
	return res;
}


void  Signal:: fft() 
{
	bool invert = 0;
	vector<base> a;
	base z;
	for (int i = 0; i < N; i++)
	{
		z = base(this->noise_signal[i], 0);
		a.push_back(z);
	}
	int n = (int)a.size();
	int lg_n = 0;
	while ((1 << lg_n) < n)  ++lg_n;

	for (int i = 0; i < n; ++i)
		if (i < rev(i, lg_n))
			swap(a[i], a[rev(i, lg_n)]);

	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			base w(1);
			for (int j = 0; j < len / 2; ++j) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i = 0; i < n; ++i)
			a[i] /= n;
	
	for (int i = 0; i < n; ++i)
	{

		this->furye.push_back(sqrt(a[i].real() * a[i].real() + a[i].imag() * a[i].imag()));
		this->furye_complex.push_back(a[i]);
	}
	
	for (vector<double>::iterator j = this->furye.begin(); j != this->furye.end(); ++j)
	{
		Es_Furye += *j * *j;
	}	

}


void  Signal::fft_1()
{
	bool invert = 1;
	vector<base> a;
	base z;
	for (int i = 0; i < N; i++)
	{
		a.push_back(furye_complex[i]);
	}
	int n = (int)a.size();
	int lg_n = 0;
	while ((1 << lg_n) < n)  ++lg_n;

	for (int i = 0; i < n; ++i)
		if (i < rev(i, lg_n))
			swap(a[i], a[rev(i, lg_n)]);

	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			base w(1);
			for (int j = 0; j < len / 2; ++j) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i = 0; i < n; ++i)
			a[i] /= n;
	for (int i = 0; i < n; ++i)
	{
		this->clear_signal.push_back(a[i].real());
	}

}

double Signal::Find_delta_Es()
{
	double delta_Es = 0;
	for (int i = 0; i < N; i++)
	{
		delta_Es += (signal[i] - clear_signal[i]) * (signal[i] - clear_signal[i]);
	}
	return delta_Es / Es_Sign;
}

