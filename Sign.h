#pragma once



#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>


using namespace std;
typedef complex<double> base;

class Signal
{
	double A1;	//���������
	double A2;
	double A3;
	
	double f1;	//�������
	double f2;
	double f3;
	
	double fi1;	//����
	double fi2;
	double fi3;
	double fd;
	int N;	//���-�� ��������
	double Es_Sign = 0;	
	double Es_Furye = 0;
	double a;	//����������� ����
	double g;	//����������� ��������

	
	vector<double> signal;	//�������� ������
	vector<double> noise_signal;	//������ � ��������
	vector<double> furye;	//����������� ������ ������������ �������
	vector<base>furye_complex;	//����������� ����� ����� ������� ������������ �������
	vector<double> clear_signal;	//��������� ������

public:

	Signal(double A1, double A2, double A3, double f1, double f2, double f3, double fi1, double fi2,  double fi3,
		double dt, int N, double a, double g);		
	
	~Signal();
	double X(int i);	
	
	vector<double> Get_Vec_Sign();
	vector<double> Get_Vec_Noise_Sign();
	vector<double> Get_Vec_Furye();
	vector<double> Get_Vec_Clear_Sign();
	vector<double> Signal::Get_Vec_Furye_Complex();

	void GaussNoise();	//����������
	void ClearSignal();	//��������
	void fft();	//�������������� �����
	void fft_1();	//�������� ��������������
	double Find_delta_Es();	//������ �������




};

bool PowerOfTwo(int Value);
double FindMax(vector<double> vec);