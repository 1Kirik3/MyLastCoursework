
// MyLastCourseworkDlg.cpp: файл реализации
//

#include "pch.h"
#include "Paint.h"
#include "Calc.h"
#include "framework.h"
#include "MyLastCoursework.h"
#include "MyLastCourseworkDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#include <vector>
#include <string>
#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "initguid.h"
DEFINE_GUID(SignalImageFormatPNG, 0xb96b3caf, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(DFTImageFormatPNG, 0xb96b3caf, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);



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
	, userIsLog(FALSE)
	, isScaleX(FALSE)
	, isScaleY(FALSE)
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
	DDX_Control(pDX, IDC_CHECK1, buttonLog);
	DDX_Check(pDX, IDC_CHECK1, userIsLog);
	DDX_Control(pDX, IDC_SCROLLBAR5, signalScalePos);
	DDX_Control(pDX, IDC_SCROLLBAR6, DFTScalePos);
	DDX_Control(pDX, IDC_COMBO1, graphColorChange);
	DDX_Control(pDX, IDC_STATIC_COORD, cursorPosCoord);
	DDX_Control(pDX, IDC_CHECK_XSCALE, buttonScaleX);
	DDX_Control(pDX, IDC_CHECK_YSCALE, buttonScaleY);
	DDX_Check(pDX, IDC_CHECK_XSCALE, isScaleX);
	DDX_Check(pDX, IDC_CHECK_YSCALE, isScaleY);
	DDX_Control(pDX, IDC_COMBO2, backColorChange);
}

BEGIN_MESSAGE_MAP(CMyLastCourseworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyLastCourseworkDlg::OnBnClickedPlaySoundtrack)
	ON_STN_CLICKED(IDC_STATIC_PAINT, &CMyLastCourseworkDlg::OnStnClickedStaticPaint)
	ON_STN_CLICKED(IDC_STATIC_PAINT2, &CMyLastCourseworkDlg::OnStnClickedStaticPaint2)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR2, &CMyLastCourseworkDlg::OnNMThemeChangedScrollbar2)
	ON_BN_CLICKED(IDOK, &CMyLastCourseworkDlg::OnBnClickedOk)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK1, &CMyLastCourseworkDlg::OnBnClickedCheckLog)
	ON_WM_VSCROLL()
	ON_WM_HOTKEY()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMyLastCourseworkDlg::OnCbnSelchangeComboColor)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_CHECK_YSCALE, &CMyLastCourseworkDlg::OnBnClickedCheckYscale)
	ON_BN_CLICKED(IDC_CHECK_XSCALE, &CMyLastCourseworkDlg::OnBnClickedCheckXscale)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMyLastCourseworkDlg::OnCbnSelchangeComboBackColor)
END_MESSAGE_MAP()


// Обработчики сообщений CMyLastCourseworkDlg

BOOL CMyLastCourseworkDlg::OnInitDialog()
{
	RegisterHotKey(GetSafeHwnd(), 1, MOD_CONTROL | MOD_NOREPEAT, 0x52);
	RegisterHotKey(GetSafeHwnd(), 2, MOD_CONTROL | MOD_NOREPEAT, 0x53);


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
		pSysMenu->AppendMenu(MF_STRING, IDM_SAVEGRAPH, _T("Сохранить график					Ctrl+S"));
		pSysMenu->AppendMenu(MF_STRING, IDM_RESET_PAR, _T("Сброс параметров				Ctrl+R"));
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	
	mySignalGraph.GetClientRect(SignalRc);
	SignalRc.DeflateRect(100, 100);
	mySignal.ToRectCenter(SignalRc);
	

	DFTGraph.GetClientRect(DFTRc);
	DFTRc.DeflateRect(100, 100);
	myDFTSignal.ToRectCenter(DFTRc);

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
	if ((nID & 0xFFF0) == IDM_SAVEGRAPH)
	{
		DoSaveSignal();
		DoSaveDFTGraph();
		PlaySound(L"Sounds/Sonic-Ring-Sound-Effect.wav", NULL, SND_FILENAME | SND_ASYNC);

	}
	
	else if ((nID & 0xFFF0) == IDM_RESET_PAR)
	{
		ResetParametrs();
		PlaySound(L"Sounds/Sonic-Ring-Sound-Effect.wav", NULL, SND_FILENAME | SND_ASYNC);

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
	myDFTSignal.data.clear();
	CPoint mPt;
	for (double x = 1; x < 700.0; x++) 
	{
		
		mPt.y = round(mySignal.f(x)+ SignalRc.CenterPoint().y);
		mPt.x = round(x);
		double noScaleY = round(mySignal.f_no_scale(x) + SignalRc.CenterPoint().y);
		myDFTSignal.data.push_back(noScaleY);
		vc.push_back(mPt);
	}
	return vc;
}


std::vector<CPoint> CMyLastCourseworkDlg::CalculateDFTSignal(std::vector<CPoint> vc)
{
	CPoint mPtDFT;
	for (double x = 1; x < 700; x++)
	{
		mPtDFT.y = round(myDFTSignal.f_DFT(x) + DFTRc.CenterPoint().y);
		mPtDFT.x = round(x);
		vc.push_back(mPtDFT);
	}
	return vc;
}


void CMyLastCourseworkDlg::OnBnClickedPlaySoundtrack()
{

	PlaySound(L"Sounds/chuck-berry-you-never-can-tell-pulp-fiction.wav", NULL, SND_FILENAME | SND_ASYNC);

}


void CMyLastCourseworkDlg::OnStnClickedStaticPaint()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CMyLastCourseworkDlg::OnStnClickedStaticPaint2()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CMyLastCourseworkDlg::OnNMThemeChangedScrollbar2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// Для этого средства требуется Windows XP или более поздняя версия.
	// Символ _WIN32_WINNT должен быть >= 0x0501.
	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;
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
		mySignal.SetSignalScale(mSignalScale/100);
		myDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		myDFTSignal.SetDFTScale(mDFTScale/100);


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
		mySignal.SetSignalScale(mSignalScale / 100);
		myDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		myDFTSignal.SetDFTScale(mDFTScale / 100);



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
		mySignal.SetSignalScale(mSignalScale / 100);
		myDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		myDFTSignal.SetDFTScale(mDFTScale / 100);


	}


	/*if (pScrollBar->GetDlgCtrlID() == stepPos.GetDlgCtrlID())
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			stepValue = nPos;
		}
		stepPos.EnableScrollBar(ESB_ENABLE_BOTH);
		stepPos.SetScrollPos(stepValue);

		stepValueText.Format(_T("%d"), (stepValue));
		CWnd* my_step = GetDlgItem(IDC_STATIC_Step);
		my_step->SetWindowText(stepValueText);
		mySignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		mySignal.SetSignalScale(mSignalScale / 100);
		myDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		myDFTSignal.SetDFTScale(mDFTScale / 100);

	}*/

	vecSignal.clear();
	vecSignal = CalculateSignal(vecSignal);
	mySignalGraph.ToGraph(vecSignal);
	mySignalGraph.RedrawWindow();

	vecDFTSignal.clear();
	vecDFTSignal = CalculateDFTSignal(vecDFTSignal);
	DFTGraph.ToGraph(vecDFTSignal);
	DFTGraph.RedrawWindow();


	
	
	
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);

	
}


void CMyLastCourseworkDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	if (pScrollBar->GetDlgCtrlID() == signalScalePos.GetDlgCtrlID())
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			mSignalScale = nPos;
		}
		signalScalePos.EnableScrollBar(ESB_ENABLE_BOTH);
		signalScalePos.SetScrollPos(mSignalScale);

		mySignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		mySignal.SetSignalScale(mSignalScale / 100);
		myDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		myDFTSignal.SetDFTScale(mDFTScale / 100);

	}


	if (pScrollBar->GetDlgCtrlID() == DFTScalePos.GetDlgCtrlID())
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			mDFTScale = nPos;
		}
		DFTScalePos.EnableScrollBar(ESB_ENABLE_BOTH);
		DFTScalePos.SetScrollPos(mDFTScale);
		mySignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		mySignal.SetSignalScale(mSignalScale / 100);
		myDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		myDFTSignal.SetDFTScale(mDFTScale / 100);


	}

	vecDFTSignal.clear();
	vecDFTSignal = CalculateDFTSignal(vecDFTSignal);
	DFTGraph.ToGraph(vecDFTSignal);
	DFTGraph.RedrawWindow();

	vecSignal.clear();
	vecSignal = CalculateSignal(vecSignal);
	mySignalGraph.ToGraph(vecSignal);
	mySignalGraph.RedrawWindow();


	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}



void CMyLastCourseworkDlg::OnBnClickedCheckLog()
{
	UpdateData(TRUE);
	if (userIsLog)
	{ 
		mySignal.checkLog = true;
		myDFTSignal.checkLog = true;
	}
		
	else
	{
		mySignal.checkLog = false;
		myDFTSignal.checkLog = false;
	}
}



void CMyLastCourseworkDlg::OnBnClickedCheckYscale()
{
	UpdateData(TRUE);
	if (isScaleY)
	{
		mySignal.checkYScale = true;
		myDFTSignal.checkYScale = true;
	}
	else
	{
		mySignal.checkYScale = false;
		myDFTSignal.checkYScale = false;
	}
}


void CMyLastCourseworkDlg::OnBnClickedCheckXscale()
{
	UpdateData(TRUE);
	if (isScaleX)
	{
		mySignal.checkXScale = true;
		myDFTSignal.checkXScale = true;
	}
	else
	{
		mySignal.checkXScale = false;
		myDFTSignal.checkXScale = false;
	}
}


void CMyLastCourseworkDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	if (nHotKeyId == 1)
	{
		ResetParametrs();
	}

	if (nHotKeyId == 2)
	{
		DoSaveSignal();
		DoSaveDFTGraph();

		PlaySound(L"Sounds/Sonic-Ring-Sound-Effect.wav", NULL, SND_FILENAME | SND_ASYNC);
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

//Доработать 
void CMyLastCourseworkDlg::OnMouseMove(UINT nFlags, CPoint point)		
{

	CRect rc1;
	CRect rc2;
	mySignalGraph.GetWindowRect(&rc1);
	DFTGraph.GetWindowRect(&rc2);
	CPoint pt1 = point;
	CPoint pt2 = point;
	ClientToScreen(&pt1);
	
	if (rc1.PtInRect(pt1));
	{
		mySignalGraph.ScreenToClient(&pt1);
		double x, y;
		x = pt1.x / mSignalScale;
		y = (-1 * pt1.y) / mSignalScale;
		CString strPos;
		strPos.Format(_T("X=%.2f Y=%.2f"), x, y);
		cursorPosCoord.SetWindowTextW(strPos);
	}
	ClientToScreen(&pt2);
	if (rc2.PtInRect(pt2))
	{
		DFTGraph.ScreenToClient(&pt2);
		double x, y;
		x = pt2.x / mDFTScale;
		y = (-1 * pt2.y) / mDFTScale;
		CString strPos;
		strPos.Format(_T("X=%.2f Y=%.2f"), x, y);
		cursorPosCoord.SetWindowTextW(strPos);
	}
	else
		cursorPosCoord.SetWindowTextW(_T(""));
	CDialogEx::OnMouseMove(nFlags, point);
}   



void CMyLastCourseworkDlg::OnCbnSelchangeComboColor()
{
	int cmb = graphColorChange.GetCurSel();

	if (LB_ERR == cmb)
	{
		cmb = 5;
	};

	switch (cmb)
	{
	case 0:
		mySignalGraph.graphUserColor.red = 5;
		mySignalGraph.graphUserColor.green = 255;
		mySignalGraph.graphUserColor.blue = 42;

		DFTGraph.graphUserColor.red = 5;
		DFTGraph.graphUserColor.green = 255;
		DFTGraph.graphUserColor.blue = 42;
		break;
	case 1:
		mySignalGraph.graphUserColor.red = 255;
		mySignalGraph.graphUserColor.green = 35;
		mySignalGraph.graphUserColor.blue = 25;

		DFTGraph.graphUserColor.red = 255;
		DFTGraph.graphUserColor.green = 35;
		DFTGraph.graphUserColor.blue = 25;
		break;
	case 2:
		mySignalGraph.graphUserColor.red = 255;
		mySignalGraph.graphUserColor.green = 255;
		mySignalGraph.graphUserColor.blue = 255;

		DFTGraph.graphUserColor.red = 255;
		DFTGraph.graphUserColor.green = 255;
		DFTGraph.graphUserColor.blue = 255;
		break;
	case 3:
		mySignalGraph.graphUserColor.red = 255;
		mySignalGraph.graphUserColor.green = 36;
		mySignalGraph.graphUserColor.blue = 254;

		DFTGraph.graphUserColor.red = 255;
		DFTGraph.graphUserColor.green = 36;
		DFTGraph.graphUserColor.blue = 254;
		break;
	case 4:
		mySignalGraph.graphUserColor.red = 255;
		mySignalGraph.graphUserColor.green = 245;
		mySignalGraph.graphUserColor.blue = 31;

		DFTGraph.graphUserColor.red = 255;
		DFTGraph.graphUserColor.green = 245;
		DFTGraph.graphUserColor.blue = 31;
		break;
	case 5:
		mySignalGraph.graphUserColor.red = 0;
		mySignalGraph.graphUserColor.green = 0;
		mySignalGraph.graphUserColor.blue = 0;

		DFTGraph.graphUserColor.red = 0;
		DFTGraph.graphUserColor.green = 0;
		DFTGraph.graphUserColor.blue = 0;
		break;
	}
	
	mySignalGraph.RedrawWindow();
	DFTGraph.RedrawWindow();
}

void CMyLastCourseworkDlg::OnCbnSelchangeComboBackColor()
{
	int cmb = backColorChange.GetCurSel();
	if (LB_ERR == cmb)
	{
		cmb = 2;
	};

	switch (cmb)
	{
	case 0:
		mySignalGraph.backUserColor.red = 147;
		mySignalGraph.backUserColor.green = 112;
		mySignalGraph.backUserColor.blue = 219;

		DFTGraph.backUserColor.red = 147;
		DFTGraph.backUserColor.green = 112;
		DFTGraph.backUserColor.blue = 219;
		break;
	case 1:
		mySignalGraph.backUserColor.red = 30;
		mySignalGraph.backUserColor.green = 144;
		mySignalGraph.backUserColor.blue = 255;

		DFTGraph.backUserColor.red = 30;
		DFTGraph.backUserColor.green = 144;
		DFTGraph.backUserColor.blue = 255;
		break;
	case 2:
		mySignalGraph.backUserColor.red = 255;
		mySignalGraph.backUserColor.green = 255;
		mySignalGraph.backUserColor.blue = 255;

		DFTGraph.backUserColor.red = 255;
		DFTGraph.backUserColor.green = 255;
		DFTGraph.backUserColor.blue = 255;
		break;
	case 3:
		mySignalGraph.backUserColor.red = 240;
		mySignalGraph.backUserColor.green = 128;
		mySignalGraph.backUserColor.blue = 128;

		DFTGraph.backUserColor.red = 240;
		DFTGraph.backUserColor.green = 128;
		DFTGraph.backUserColor.blue = 128;
		break;
	case 4:
		mySignalGraph.backUserColor.red = 50;
		mySignalGraph.backUserColor.green = 205;
		mySignalGraph.backUserColor.blue = 50;

		DFTGraph.backUserColor.red = 50;
		DFTGraph.backUserColor.green = 205;
		DFTGraph.backUserColor.blue = 50;
		break;
	case 5:
		mySignalGraph.backUserColor.red = 128;
		mySignalGraph.backUserColor.green = 128;
		mySignalGraph.backUserColor.blue = 128;

		DFTGraph.backUserColor.red = 128;
		DFTGraph.backUserColor.green = 128;
		DFTGraph.backUserColor.blue = 128;
		break;
	}

	mySignalGraph.myBgrOk = false;
	DFTGraph.myBgrOk = false;
	mySignalGraph.RedrawWindow();
	DFTGraph.RedrawWindow();
}




void CMyLastCourseworkDlg::DoSaveSignal()
{
	CWnd* pWn = GetDlgItem(IDC_STATIC_PAINT);
	if (!pWn)
		return;
	CRect rc1;
	pWn->GetClientRect(&rc1);
	CWindowDC winDC(pWn);
	CDC memDC;
	memDC.CreateCompatibleDC(&winDC);
	CBitmap bmpG;
	bmpG.CreateCompatibleBitmap(&winDC, rc1.Width(), rc1.Height());
	HGDIOBJ old = memDC.SelectObject(bmpG);
	memDC.BitBlt(0, 0, rc1.Width(), rc1.Height(), &winDC, 0, 0, SRCCOPY);
	memDC.SelectObject(old);
	CImage image;
	image.Attach(HBITMAP(bmpG));
	image.Save(_T("Signal.png"), SignalImageFormatPNG);
}			

void CMyLastCourseworkDlg::DoSaveDFTGraph()
{
	CWnd* pWn = GetDlgItem(IDC_STATIC_PAINT2);
	if (!pWn)
		return;
	CRect rc1;
	pWn->GetClientRect(&rc1);
	CWindowDC winDC(pWn);
	CDC memDC;
	memDC.CreateCompatibleDC(&winDC);
	CBitmap bmpG;
	bmpG.CreateCompatibleBitmap(&winDC, rc1.Width(), rc1.Height());
	HGDIOBJ old = memDC.SelectObject(bmpG);
	memDC.BitBlt(0, 0, rc1.Width(), rc1.Height(), &winDC, 0, 0, SRCCOPY);
	memDC.SelectObject(old);
	CImage image;
	image.Attach(HBITMAP(bmpG));
	image.Save(_T("DFT.png"), DFTImageFormatPNG);
}

void CMyLastCourseworkDlg::ResetParametrs()
{
	vecSignal.clear();
	mySignalGraph.ToGraph(vecSignal);
	mySignalGraph.RedrawWindow();

	vecDFTSignal.clear();
	DFTGraph.ToGraph(vecDFTSignal);
	DFTGraph.RedrawWindow();

	buttonLog.SetCheck(false);
	buttonScaleX.SetCheck(false);
	buttonScaleY.SetCheck(false);

	mPos.SetScrollPos(0);
	FmPos.SetScrollPos(0);
	fPos.SetScrollPos(10);
	stepPos.SetScrollPos(1);
	signalScalePos.SetScrollPos(1);
	DFTScalePos.SetScrollPos(1);

	mValueText.Format(_T("%.2f"), (0));
	CWnd* my_m = GetDlgItem(IDC_STATIC_M);
	my_m->SetWindowText(mValueText);

	FmValueText.Format(_T("%.2f"), (0));
	CWnd* my_Fm = GetDlgItem(IDC_STATIC_Fm);
	my_Fm->SetWindowText(FmValueText);

	fValueText.Format(_T("%.2f"), (0.1));
	CWnd* my_f = GetDlgItem(IDC_STATIC_f);
	my_f->SetWindowText(fValueText);

	PlaySound(L"Sounds/Sonic-Ring-Sound-Effect.wav", NULL, SND_FILENAME | SND_ASYNC);
}

void CMyLastCourseworkDlg::SetScrollsBarRange()
{
	mPos.SetScrollRange(0, 50);
	FmPos.SetScrollRange(0, 9);
	fPos.SetScrollRange(10, 40);
	stepPos.SetScrollRange(1, 2);
	signalScalePos.SetScrollRange(1, 1000);
	DFTScalePos.SetScrollRange(1, 10000);

	mPos.SetScrollPos(0);
	FmPos.SetScrollPos(0);
	fPos.SetScrollPos(10);
	stepPos.SetScrollPos(1);
	signalScalePos.SetScrollPos(1);
	DFTScalePos.SetScrollPos(1);

	/*mValueText.Format(_T("%.2f"), (mValue / 100));
	CWnd* my_m = GetDlgItem(IDC_STATIC_M);
	my_m->SetWindowText(mValueText);

	FmValueText.Format(_T("%.2f"), (FmValue / 100));
	CWnd* my_Fm = GetDlgItem(IDC_STATIC_Fm);
	my_Fm->SetWindowText(FmValueText);

	fValueText.Format(_T("%.2f"), (fValue / 100));
	CWnd* my_f = GetDlgItem(IDC_STATIC_f);
	my_f->SetWindowText(fValueText);

	stepValueText.Format(_T("%d"), (stepValue));
	CWnd* my_step = GetDlgItem(IDC_STATIC_Step);
	my_step->SetWindowText(stepValueText);*/


	vecSignal.clear();
	vecSignal = CalculateSignal(vecSignal);
	mySignalGraph.ToGraph(vecSignal);
	mySignalGraph.RedrawWindow();
}