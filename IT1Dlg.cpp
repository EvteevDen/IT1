
// IT1Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "IT1.h"
#include "IT1Dlg.h"
#include "afxdialogex.h"
#include "Drawer.h"
#include "Sign.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CIT1Dlg



CIT1Dlg::CIT1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IT1_DIALOG, pParent)
	, A1(3)
	, f1(30)
	, fi1(0)
	, A2(2)
	, f2(20)
	, fi2(0)
	, A3(1)
	, f3(10)
	, fi3(0)
	, fd(2000)
	, N(1024)
	, a(20)
	, g(80)
	,delta_Es(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIT1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A1);
	DDX_Text(pDX, IDC_EDIT2, f1);
	DDX_Text(pDX, IDC_EDIT3, fi1);
	DDX_Text(pDX, IDC_EDIT4, A2);
	DDX_Text(pDX, IDC_EDIT5, f2);
	DDX_Text(pDX, IDC_EDIT6, fi2);
	DDX_Text(pDX, IDC_EDIT7, A3);
	DDX_Text(pDX, IDC_EDIT8, f3);
	DDX_Text(pDX, IDC_EDIT9, fi3);
	DDX_Text(pDX, IDC_EDIT10, fd);
	DDX_Text(pDX, IDC_EDIT11, N);
	DDX_Text(pDX, IDC_EDIT12, a);
	DDX_Text(pDX, IDC_EDIT13, g);
	DDX_Text(pDX, IDC_EDIT14, delta_Es);
	DDX_Control(pDX, IDC_EDIT14, delta_Es_ctrl);
	delta_Es_ctrl.EnableWindow(FALSE);
}

BEGIN_MESSAGE_MAP(CIT1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CIT1Dlg::OnBnClickedOk)

END_MESSAGE_MAP()


// Обработчики сообщений CIT1Dlg

BOOL CIT1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	drv.Create(GetDlgItem(IDC_PIC)->GetSafeHwnd());
	drv1.Create(GetDlgItem(IDC_PIC1)->GetSafeHwnd());
	drv2.Create(GetDlgItem(IDC_PIC3)->GetSafeHwnd());
	drv3.Create(GetDlgItem(IDC_PIC2)->GetSafeHwnd());
	drv4.Create(GetDlgItem(IDC_PIC4)->GetSafeHwnd());

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CIT1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CIT1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CIT1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIT1Dlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	

	if (!PowerOfTwo(N))
	{
		MessageBox(L"N должно быть степенью 2", L"Ошибка", MB_OK | MB_ICONERROR);
		//exit(EXIT_FAILURE);
		return;
	}


	Signal S(A1, A2, A3, f1, f2, f3, fi1, fi2, fi3, fd, N, a / 100, g / 100);	//Создаем объект сигнала
	s=&S;	//указатель на объект в классе CIT1Dlg


	int y_max = int(1.5 * FindMax(this->s->Get_Vec_Sign()));	//Масштабирование графика
	
	CString str_y("  x");	//Подписи по осям
	CString str_x("t");

	drv.XY(N, str_x, y_max, str_y, -y_max,N/fd);
	drv.Draw(this->s->Get_Vec_Sign());	//Рисование

	this->s->GaussNoise();	//Зашумление

	y_max = int(1.5 * FindMax(this->s->Get_Vec_Noise_Sign()));

	drv3.XY(N, str_x, y_max, str_y, -y_max, N/fd);	
	drv3.Draw(this->s->Get_Vec_Noise_Sign());	

	this->s->fft();	//Фурье анализ
	y_max = int(1.5 * FindMax(this->s->Get_Vec_Furye()));
	

	CString str_y1("  x");
	CString str_x1("f");
	drv1.XY(N, str_x1, y_max, str_y1, 0, fd);
	drv1.Draw(this->s->Get_Vec_Furye());


	this->s->ClearSignal();

	drv4.XY(N, str_x1, y_max, str_y1, 0, fd);
	drv4.Draw(this->s->Get_Vec_Furye());

	this->s->fft_1();	//Фурье анализ
	y_max =int(1.5 * FindMax(this->s->Get_Vec_Sign()));

	CString str_y2("  x");
	CString str_x2("t");
	drv2.XY(N, str_x2, y_max, str_y2,-y_max,N/fd);
	drv2.Draw( this->s->Get_Vec_Sign(), this->s->Get_Vec_Clear_Sign() );

	delta_Es = round((s->Find_delta_Es()*100)*100)/100;
	UpdateData(FALSE);
	




}





