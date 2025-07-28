
// IT1Dlg.h: файл заголовка
//

#pragma once
#include "Drawer.h"
#include"Sign.h"


// Диалоговое окно CIT1Dlg
class CIT1Dlg : public CDialogEx
{
// Создание
public:
	CIT1Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IT1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	Drawer drv;
	Drawer drv1;
	Drawer drv2;
	Drawer drv3;
	Drawer drv4;

	Signal *s;
	bool signal_clear=false;
public:
	// Амплитуда 1
	float A1;
	// Частота 1
	float f1;
	// Фаза 1
	float fi1;
	afx_msg void OnBnClickedOk();
	double A2;
	double f2;
	double fi2;
	double A3;
	double f3;
	double fi3;
	// Частота дискретизации
	double fd;
	double N;
	double a;
	double g;
	double delta_Es;
	CEdit delta_Es_ctrl;



};
