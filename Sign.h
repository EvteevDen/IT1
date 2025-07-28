#pragma once



#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>


using namespace std;
typedef complex<double> base;

class Signal
{
	double A1;	//Амплитуда
	double A2;
	double A3;
	
	double f1;	//Частота
	double f2;
	double f3;
	
	double fi1;	//Фаза
	double fi2;
	double fi3;
	double fd;
	int N;	//Кол-во отсчетов
	double Es_Sign = 0;	
	double Es_Furye = 0;
	double a;	//Коэффициент шума
	double g;	//Коэффициент очищения

	
	vector<double> signal;	//Исходный сигнал
	vector<double> noise_signal;	//Сигнал с помехами
	vector<double> furye;	//амплитудный анализ зашумленного сигнала
	vector<base>furye_complex;	//комплексная форма фурье анализа зашумленного сигнала
	vector<double> clear_signal;	//очищенный сигнал

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

	void GaussNoise();	//Зашумление
	void ClearSignal();	//Очищение
	void fft();	//Преобразование фурье
	void fft_1();	//Обратное преобразование
	double Find_delta_Es();	//Потери энергии




};

bool PowerOfTwo(int Value);
double FindMax(vector<double> vec);