
// MyLastCourseworkDlg.cpp: файл реализации
//

#include "pch.h"
#include "Paint.h"
#include "Calc.h"
#include "framework.h"
#include "MyLastCoursework.h"
#include "MyLastCourseworkDlg.h"
#include "afxdialogex.h"
#include <vector>

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


// Диалоговое окно CMyLastCourseworkDlg



CMyLastCourseworkDlg::CMyLastCourseworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYLASTCOURSEWORK_DIALOG, pParent)
	, mySignalGraph()

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyLastCourseworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PAINT, mySignalGraph);
}

BEGIN_MESSAGE_MAP(CMyLastCourseworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyLastCourseworkDlg::OnBnClickedDrawGraphic)
	ON_STN_CLICKED(IDC_STATIC_PAINT, &CMyLastCourseworkDlg::OnStnClickedStaticPaint)
END_MESSAGE_MAP()


// Обработчики сообщений CMyLastCourseworkDlg

BOOL CMyLastCourseworkDlg::OnInitDialog()
{
	mySignalGraph.SubclassDlgItem(IDC_STATIC_PAINT, this);
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

	// TODO: добавьте дополнительную инициализацию
	
	mySignalGraph.GetClientRect(rc);
	rc.DeflateRect(1000, 1000);
	mySignal.ToRectCenter(rc);
	


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMyLastCourseworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyLastCourseworkDlg::OnPaint()
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
HCURSOR CMyLastCourseworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



std::vector <CPoint> CMyLastCourseworkDlg::Calculate(std::vector <CPoint> vc)
{
	CPoint mPt;
	for (double x = 1; x < 300; x++) 
	{
		mPt.y = round(mySignal.f(x)+ rc.CenterPoint().y);
		mPt.x = round(x);
		mPt = mySignal.ScalingPoint(mPt, 1);
		vc.push_back(mPt);
	}
	return vc;
}

void CMyLastCourseworkDlg::OnBnClickedDrawGraphic()
{
	vec.clear();
	vec = Calculate(vec);
	mySignalGraph.ToGraph(vec);
	mySignalGraph.RedrawWindow();
}


void CMyLastCourseworkDlg::OnStnClickedStaticPaint()
{
	// TODO: добавьте свой код обработчика уведомлений
}
