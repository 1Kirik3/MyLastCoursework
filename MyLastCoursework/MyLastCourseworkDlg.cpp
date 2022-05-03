
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
#include <string>
#include <iostream>


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

	, DFTGraph()
	, mValueText(_T(""))
	, FmValueText(_T(""))
	, fValueText(_T(""))
	, stepValueText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyLastCourseworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PAINT, mySignalGraph);
	DDX_Control(pDX, IDC_STATIC_PAINT2, DFTGraph);
	DDX_Control(pDX, IDC_SCROLLBAR2, mPos);
	DDX_Control(pDX, IDC_SCROLLBAR1, FmPos);
	DDX_Control(pDX, IDC_SCROLLBAR3, fPos);
	DDX_Control(pDX, IDC_SCROLLBAR4, stepPos);
	DDX_Text(pDX, IDC_STATIC_M, mValueText);
	DDX_Text(pDX, IDC_STATIC_Fm, FmValueText);
	DDX_Text(pDX, IDC_STATIC_f, fValueText);
	DDX_Text(pDX, IDC_STATIC_Step, stepValueText);
}

BEGIN_MESSAGE_MAP(CMyLastCourseworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyLastCourseworkDlg::OnBnClickedDrawGraphic)
	ON_STN_CLICKED(IDC_STATIC_PAINT, &CMyLastCourseworkDlg::OnStnClickedStaticPaint)
	ON_STN_CLICKED(IDC_STATIC_PAINT2, &CMyLastCourseworkDlg::OnStnClickedStaticPaint2)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR2, &CMyLastCourseworkDlg::OnNMThemeChangedScrollbar2)
	// ON_BN_CLICKED(IDOK, &CMyLastCourseworkDlg::OnBnClickedOk)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Обработчики сообщений CMyLastCourseworkDlg

BOOL CMyLastCourseworkDlg::OnInitDialog()
{
	mySignalGraph.SubclassDlgItem(IDC_STATIC_PAINT, this);
	DFTGraph.SubclassDlgItem(IDC_STATIC_PAINT2, this);
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
	DFTGraph.GetClientRect(rc);
	rc.DeflateRect(1000, 1000);
	mySignal.ToRectCenter(rc);
	SetScrollsBarRange();
	


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



std::vector <CPoint> CMyLastCourseworkDlg::CalculateSignal(std::vector <CPoint> vc)
{
	CPoint mPt;
	for (double x = 1; x < 300; x++) 
	{
		mPt.y = round(mySignal.f(x)+ rc.CenterPoint().y);
		mPt.x = round(x);
		myData.push_back(mPt.y);
		//mPt = mySignal.ScalingPoint(mPt, 1);
		vc.push_back(mPt);
	}
	return vc;
}

std::vector<CPoint> CMyLastCourseworkDlg::CalculateDFTSignal(std::vector<CPoint> vc)
{
	CPoint mPt;
	mySignal.data = myData;
	for (double x = 1; x < 300; x++)
	{
		mPt.y = round(myDFTSignal.f(x) + rc.CenterPoint().y);
		mPt.x = round(x);
		vc.push_back(mPt);
	}
	return vc;
}



void CMyLastCourseworkDlg::OnBnClickedDrawGraphic()
{
	vecSignal.clear();
	vecSignal = CalculateSignal(vecSignal);
	mySignalGraph.ToGraph(vecSignal);
	mySignalGraph.RedrawWindow();


	DFTSignal.clear();
	DFTSignal = CalculateDFTSignal(DFTSignal);
	DFTGraph.ToGraph(DFTSignal);
	DFTGraph.RedrawWindow();
}


void CMyLastCourseworkDlg::OnStnClickedStaticPaint()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CMyLastCourseworkDlg::OnStnClickedStaticPaint2()
{
	// TODO: добавьте свой код обработчика уведомлений
}


//Work with ScrollBar


void CMyLastCourseworkDlg::OnNMThemeChangedScrollbar2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// Для этого средства требуется Windows XP или более поздняя версия.
	// Символ _WIN32_WINNT должен быть >= 0x0501.
	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;
}


void CMyLastCourseworkDlg::SetScrollsBarRange()
{
	mPos.SetScrollRange(0, 50);
	FmPos.SetScrollRange(0, 9);
	fPos.SetScrollRange(10, 40);
	stepPos.SetScrollRange(1, 2);
	
	fPos.SetScrollPos(1);
}


void CMyLastCourseworkDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}


void CMyLastCourseworkDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	if (pScrollBar->GetDlgCtrlID() == mPos.GetDlgCtrlID())
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			mValue = nPos;
		}
		mPos.EnableScrollBar(ESB_ENABLE_BOTH);
		mPos.SetScrollPos(mValue);
		mValueText.Format(_T("%.2f"), (mValue/100));
		CWnd* my_m = GetDlgItem(IDC_STATIC_M);
		my_m->SetWindowText(mValueText);
		mySignal.SetParametrs(mValue/100, FmValue/100, fValue/100);
		vecSignal.clear();
		vecSignal = CalculateSignal(vecSignal);
		mySignalGraph.ToGraph(vecSignal);
		mySignalGraph.RedrawWindow();
	}
	
	
	if (pScrollBar->GetDlgCtrlID() == FmPos.GetDlgCtrlID())
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			FmValue = nPos;
		}
		FmPos.EnableScrollBar(ESB_ENABLE_BOTH);
		FmPos.SetScrollPos(FmValue);

		FmValueText.Format(_T("%.2f"), (FmValue / 100));
		CWnd* my_Fm = GetDlgItem(IDC_STATIC_Fm);
		my_Fm->SetWindowText(FmValueText);
		mySignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		vecSignal.clear();
		vecSignal = CalculateSignal(vecSignal);
		mySignalGraph.ToGraph(vecSignal);
		mySignalGraph.RedrawWindow();

	}

	if (pScrollBar->GetDlgCtrlID() == fPos.GetDlgCtrlID())
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			fValue = nPos;
		}
		fPos.EnableScrollBar(ESB_ENABLE_BOTH);
		fPos.SetScrollPos(fValue);

		fValueText.Format(_T("%.2f"), (fValue / 100));
		CWnd* my_f = GetDlgItem(IDC_STATIC_f);
		my_f->SetWindowText(fValueText);
		mySignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		vecSignal.clear();
		vecSignal = CalculateSignal(vecSignal);
		mySignalGraph.ToGraph(vecSignal);
		mySignalGraph.RedrawWindow();
	}


	if (pScrollBar->GetDlgCtrlID() == stepPos.GetDlgCtrlID())
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			stepValue = nPos;
		}
		stepPos.EnableScrollBar(ESB_ENABLE_BOTH);
		stepPos.SetScrollPos(stepValue);

		stepValueText.Format(_T("%.0f"), (stepValue));
		CWnd* my_step = GetDlgItem(IDC_STATIC_Step);
		my_step->SetWindowText(stepValueText);
		mySignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		vecSignal.clear();
		vecSignal = CalculateSignal(vecSignal);
		mySignalGraph.ToGraph(vecSignal);
		mySignalGraph.RedrawWindow();

	}
	
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);

	
}
