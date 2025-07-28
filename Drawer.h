#pragma once

#include <afxwin.h>
#include <vector>


using namespace std;

class Drawer
{
	// ������������� ������� ���������.
	CRect frame;
	// ��������� �� ������ ����, ������� ���������.
	CWnd * wnd;
	// �������� ���������, ����������� � ������� ���������.
	CDC * dc;
	// �������� ���������, ����������� � ������.
	CDC memDC;
	// ������ ��� ��������� ��������� memDC.
	CBitmap bmp;
	// ���� ��� ������������ ��������� ������������� ������.
	bool init;
	double x = 100;	//���������� �������� �����
	double x_max = 100;	//������� �� ����
	double y_min = 0;	//������� y
	double y_max = 10;
	CString name_x;	//������������ ����
	CString name_y;
public:
	
	/*Drawer(double x, double y)
	{
		this->x = x;
		this->y = y;
	}*/

	void XY(double x, CString name_x,  double y_max, CString name_y, double y_min = 0, double  x_max = 100 )
	{
		this->x = x;
		this->x_max = x_max;
		this->y_min = y_min;
		this->y_max = y_max;
		this->name_x = name_x;
		this->name_y = name_y;


	}
	
	// ������������������� ������ ������ �� ������ HWND.
	void Create(HWND hWnd)
	{
		// �������� ��������� �� ����.
		wnd = CWnd::FromHandle(hWnd);
		// �������� ������������� ����.
		wnd->GetClientRect(frame);
		// �������� �������� ��� ��������� � ���� ����.
		dc = wnd->GetDC();

		// ������� �����-��������.
		memDC.CreateCompatibleDC(dc);
		// ������� ����� ��� ��������� ���������.
		bmp.CreateCompatibleBitmap(dc, frame.Width(), frame.Height());
		// �������� ����� ��� ������������� �����-����������.
		memDC.SelectObject(&bmp);
		init = true;
	}

	// ���������� ������ �� ���������� ������.
	void Draw(vector<double> &data,vector<double> &data1 = vector<double>(), vector<double> &keys = vector<double>(), vector<double>&keys1 = vector<double>())
	{
		if (!init) return;

		CPen subgrid_pen(PS_DOT, 1, RGB(200, 200, 200));
		CPen grid_pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen data_pen(PS_SOLID, 2, RGB(255, 0, 0));
		CPen data2_pen(PS_SOLID, 2, RGB(0, 0, 255));
		CFont font;
		font.CreateFontW(18, 0, 0, 0,
			FW_DONTCARE,
			FALSE,				// ������
			FALSE,				// ������������
			FALSE,				// �������������
			DEFAULT_CHARSET,	// ����� ��������
			OUT_OUTLINE_PRECIS,	// �������� ������������.	
			CLIP_DEFAULT_PRECIS,//  
			CLEARTYPE_QUALITY,	// ��������
			VARIABLE_PITCH,		//
			TEXT("Times New Roman")		//
		);

		int padding = 20;
		int left_keys_padding = 20;
		int bottom_keys_padding = 10;

		int actual_width = frame.Width() - 2 * padding - left_keys_padding;
		int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;

		int actual_top = padding;
		int actual_bottom = actual_top + actual_height;
		int actual_left = padding + left_keys_padding;
		int actual_right = actual_left + actual_width;
		
		// ����� ���.
		memDC.FillSolidRect(frame, RGB(255,255,255));

		// ������ ����� � ��������.
		unsigned int grid_size = 10;

		memDC.SelectObject(&subgrid_pen);

		for (double i = 0.5; i < grid_size; i+=1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left,   actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}

		memDC.SelectObject(&grid_pen);

		for (double i = 0.0; i < grid_size+1; i+=1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}
	
		// ������ ������.
		if (data.empty()) return;

		if (keys.size() != data.size())
		{
			keys.resize(data.size());
			for (int i = 0; i < keys.size(); i++)
			{
				keys[i] = i;

			}
		}
		if (!data1.empty())
		{
			if (keys1.size() != data1.size())
			{
				keys1.resize(data1.size());
				for (int i = 0; i < keys1.size(); i++)
				{
					keys1[i] = i;

				}
			}

		}
		
		memDC.SelectObject(&data_pen);

		double data_y_max(y_max), data_y_min(y_min);
		double data_x_max(x), data_x_min(0);
		double data_x(x_max);

		vector<double> y = convert_range(data, actual_top, actual_bottom, data_y_max, data_y_min);
		vector<double> x = convert_range(keys, actual_right, actual_left, data_x_max, data_x_min);
				
		memDC.MoveTo(x[0], y[0]);
		for (unsigned int i = 0; i < y.size(); i++)
		{
			memDC.LineTo(x[i], y[i]);
		}
		
		if (!data1.empty())
		{
			memDC.SelectObject(&data2_pen);
			y = convert_range(data1, actual_top, actual_bottom, data_y_max, data_y_min);
			x = convert_range(keys1, actual_right, actual_left, data_x_max, data_x_min);

			memDC.MoveTo(x[0], y[0]);
			for (unsigned int i = 0; i < y.size(); i++)
			{
				memDC.LineTo(x[i], y[i]);
			}

		}

		memDC.SelectObject(&font);
		
		memDC.SetTextColor(RGB(0, 0, 0));
		for (int i = 0; i < grid_size/2 ; i++)
		{
			CString str;
			str.Format(L"%.1f", data_x_min + i*(data_x - data_x_min) /(grid_size / 2));
			memDC.TextOutW(actual_left + (double)i * actual_width / (grid_size / 2) - bottom_keys_padding, actual_bottom + bottom_keys_padding/2, str);

			str.Format(L"%.1f", data_y_min + i*(data_y_max - data_y_min) / (grid_size / 2));
			memDC.TextOutW(actual_left - 1.5*left_keys_padding, actual_bottom - (double)i * actual_height / (grid_size / 2) - bottom_keys_padding, str);
		}

		CString str;
		str = this->name_x;
		memDC.TextOutW(actual_left + (grid_size / 2 ) * actual_width / (grid_size / 2) - bottom_keys_padding, actual_bottom + bottom_keys_padding / 2, str);
		

		str = this->name_y;
		memDC.TextOutW(actual_left - 1.5 * left_keys_padding, actual_bottom - grid_size / 2 * actual_height / (grid_size / 2) - bottom_keys_padding, str);
		
		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}

	vector<double> convert_range(vector <double> & data, double outmax, double outmin, double inmax, double inmin)
	{
		vector<double> output = data;
		double k = (outmax - outmin) / (inmax - inmin);
		for (auto & item : output)
		{
			item = (item - inmin) * k + outmin;
		}

		return output;
	}
};