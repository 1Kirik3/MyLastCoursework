
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




CMyLastCourseworkDlg::CMyLastCourseworkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYLASTCOURSEWORK_DIALOG, pParent)
	, userSignalGraph()

	, userDFTGraph()
	, mValueText(_T(""))
	, FmValueText(_T(""))
	, fValueText(_T(""))
	, intervalValueText(_T(""))
	, userIsLog(FALSE)
	, isScaleX(FALSE)
	, isScaleY(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyLastCourseworkDlg::DoDataExchange(CDataExchange* pDX)			//Обработчик интерфейса
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PAINT, userSignalGraph);
	DDX_Control(pDX, IDC_STATIC_PAINT2, userDFTGraph);
	DDX_Control(pDX, IDC_SCROLLBAR2, mPos);
	DDX_Control(pDX, IDC_SCROLLBAR1, FmPos);
	DDX_Control(pDX, IDC_SCROLLBAR3, fPos);
	DDX_Control(pDX, IDC_SCROLLBAR4, intervalPos);
	DDX_Text(pDX, IDC_STATIC_M, mValueText);
	DDX_Text(pDX, IDC_STATIC_Fm, FmValueText);
	DDX_Text(pDX, IDC_STATIC_f, fValueText);
	DDX_Text(pDX, IDC_STATIC_Step, intervalValueText);
	DDX_Control(pDX, IDC_CHECK1, buttonLog);
	DDX_Check(pDX, IDC_CHECK1, userIsLog);
	DDX_Control(pDX, IDC_SCROLLBAR5, signalScalePos);
	DDX_Control(pDX, IDC_SCROLLBAR6, DFTScalePos);
	DDX_Control(pDX, IDC_COMBO1, graphColorChange);
	DDX_Control(pDX, IDC_STATIC_COORD, cursorPosCoordSignal);
	DDX_Control(pDX, IDC_CHECK_XSCALE, buttonScaleX);
	DDX_Control(pDX, IDC_CHECK_YSCALE, buttonScaleY);
	DDX_Check(pDX, IDC_CHECK_XSCALE, isScaleX);
	DDX_Check(pDX, IDC_CHECK_YSCALE, isScaleY);
	DDX_Control(pDX, IDC_COMBO2, backColorChange);
	DDX_Control(pDX, IDC_STATIC_COORD2, cursorPosCoordDFT);
}

BEGIN_MESSAGE_MAP(CMyLastCourseworkDlg, CDialogEx)											//Обработчики событий
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyLastCourseworkDlg::OnBnClickedPlaySoundtrack)
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
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Обработчики сообщений CMyLastCourseworkDlg

BOOL CMyLastCourseworkDlg::OnInitDialog()
{
	RegisterHotKey(GetSafeHwnd(), 1, MOD_CONTROL | MOD_NOREPEAT, 0x52);					//Добавление пользовательских горячих клавиш
	RegisterHotKey(GetSafeHwnd(), 2, MOD_CONTROL | MOD_NOREPEAT, 0x53);


	userSignalGraph.SubclassDlgItem(IDC_STATIC_PAINT, this);
	userDFTGraph.SubclassDlgItem(IDC_STATIC_PAINT2, this);
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);							//Добавление строчек в системное меню
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
		pSysMenu->AppendMenu(MF_STRING, 0x52, _T("Сброс параметров				Ctrl+R"));
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	
	userSignalGraph.GetClientRect(SignalRc);
	SignalRc.DeflateRect(900, 200);
	//userSignal.ToRectCenter(SignalRc);
	

	userDFTGraph.GetClientRect(DFTRc);
	DFTRc.DeflateRect(900, 200);
	//userDFTSignal.ToRectCenter(DFTRc);

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
	if ((nID & 0xFFF0) == IDM_SAVEGRAPH)	//Сохранение двух графиков
	{
		DoSaveSignal();
		DoSaveDFTGraph();
		PlaySound(L"Sounds/Sonic-Ring-Sound-Effect.wav", NULL, SND_FILENAME | SND_ASYNC);

	}
	
	else if ((nID & 0xFFF0) == 0x52)	//СБрос параметров
	{
		ResetParametrs();
		PlaySound(L"Sounds/Sonic-Ring-Sound-Effect.wav", NULL, SND_FILENAME | SND_ASYNC);

	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

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
	userDFTSignal.data.clear();																//Очистка вектора с хранимыми значениями сигнала
	CPoint mPt;
	for (double x = 0; x < intervalValue; x++) 
	{
		
		mPt.y = round(userSignal.f(x)+ SignalRc.CenterPoint().y);								//Округление и сдвиг точки к центру
		mPt.x = round(x);
		double noScaleY = round(userSignal.f_no_checkBox(x));		//Подсчёт сигнала без преобразований для ДПФ
		userDFTSignal.data.push_back(noScaleY);
		vc.push_back(mPt);
	}
	return vc;
}


std::vector<CPoint> CMyLastCourseworkDlg::CalculateDFTSignal(std::vector<CPoint> vc)
{
	CPoint mPtDFT;
	for (double x = 0; x < intervalValue; x++)
	{
		mPtDFT.y = round(userDFTSignal.f_DFT(x) + DFTRc.CenterPoint().y);
		mPtDFT.x = round(x);
		vc.push_back(mPtDFT);
	}
	return vc;
}


void CMyLastCourseworkDlg::OnBnClickedPlaySoundtrack()
{

	PlaySound(L"Sounds/chuck-berry-you-never-can-tell-pulp-fiction.wav", NULL, SND_FILENAME | SND_ASYNC);	//Фоновая музыка

}


void CMyLastCourseworkDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}


void CMyLastCourseworkDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	if (pScrollBar->GetDlgCtrlID() == mPos.GetDlgCtrlID())							//Изменение параметра m скроллбаром
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			mValue = nPos;
		}
		mPos.EnableScrollBar(ESB_ENABLE_BOTH);
		mPos.SetScrollPos(mValue);

		mValueText.Format(_T("%.2f"), (mValue/100));								//Значение параметра в CStatic
		CWnd* my_m = GetDlgItem(IDC_STATIC_M);										//
		my_m->SetWindowText(mValueText);											//

		userSignal.SetParametrs(mValue/100, FmValue/100, fValue/100);
		userSignal.SetSignalScale(mSignalScale/100);

		userDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userDFTSignal.SetDFTScale(mDFTScale/100);


	}
	
	
	if (pScrollBar->GetDlgCtrlID() == FmPos.GetDlgCtrlID())						//Изменение параметра Fm скроллбаром
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			FmValue = nPos;
		}
		FmPos.EnableScrollBar(ESB_ENABLE_BOTH);
		FmPos.SetScrollPos(FmValue);

		FmValueText.Format(_T("%.2f"), (FmValue / 100));						//Значение параметра в CStatic
		CWnd* my_Fm = GetDlgItem(IDC_STATIC_Fm);
		my_Fm->SetWindowText(FmValueText);

		userSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userSignal.SetSignalScale(mSignalScale / 100);

		userDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userDFTSignal.SetDFTScale(mDFTScale / 100);



	}

	if (pScrollBar->GetDlgCtrlID() == fPos.GetDlgCtrlID())							//Изменение параметра f скроллбаром
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
		CWnd* my_f = GetDlgItem(IDC_STATIC_f);										//Значение параметра в CStatic
		my_f->SetWindowText(fValueText);

		userSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userSignal.SetSignalScale(mSignalScale / 100);

		userDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userDFTSignal.SetDFTScale(mDFTScale / 100);


	}


	if (pScrollBar->GetDlgCtrlID() == intervalPos.GetDlgCtrlID())					//Изменение интервала скроллбаром
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			intervalValue = nPos;
		}
		intervalPos.EnableScrollBar(ESB_ENABLE_BOTH);
		intervalPos.SetScrollPos(intervalValue);

		intervalValueText.Format(_T("%d"), (intervalValue));						//Значение параметра в CStatic
		CWnd* my_step = GetDlgItem(IDC_STATIC_Step);
		my_step->SetWindowText(intervalValueText);

		userSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userSignal.SetSignalScale(mSignalScale / 100);

		userDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userDFTSignal.SetDFTScale(mDFTScale / 100);

	}

	//Перерисовка графика в реальном времени в зависомости от параметра скроллбара
	vecSignal.clear();
	vecSignal = CalculateSignal(vecSignal);
	userSignalGraph.ToGraph(vecSignal);
	userSignalGraph.RedrawWindow();

	vecDFTSignal.clear();
	vecDFTSignal = CalculateDFTSignal(vecDFTSignal);
	userDFTGraph.ToGraph(vecDFTSignal);
	userDFTGraph.RedrawWindow();

	
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);

	
}


void CMyLastCourseworkDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	if (pScrollBar->GetDlgCtrlID() == signalScalePos.GetDlgCtrlID())		//Масштабирование сигнала 
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			mSignalScale = nPos;
		}
		signalScalePos.EnableScrollBar(ESB_ENABLE_BOTH);
		signalScalePos.SetScrollPos(mSignalScale);

		userSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userSignal.SetSignalScale(mSignalScale / 100);
		userDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userDFTSignal.SetDFTScale(mDFTScale / 100);

	}


	if (pScrollBar->GetDlgCtrlID() == DFTScalePos.GetDlgCtrlID())			//Масштабирование ДПФ
	{
		UpdateData(FALSE);
		switch (nSBCode)
		{
		case SB_THUMBTRACK:
			mDFTScale = nPos;
		}
		DFTScalePos.EnableScrollBar(ESB_ENABLE_BOTH);
		DFTScalePos.SetScrollPos(mDFTScale);
		userSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userSignal.SetSignalScale(mSignalScale / 100);
		userDFTSignal.SetParametrs(mValue / 100, FmValue / 100, fValue / 100);
		userDFTSignal.SetDFTScale(mDFTScale / 100);


	}

	//Перерисовка графика в зависимости масштабирования

	vecDFTSignal.clear();
	vecDFTSignal = CalculateDFTSignal(vecDFTSignal);
	userDFTGraph.ToGraph(vecDFTSignal);
	userDFTGraph.RedrawWindow();

	vecSignal.clear();
	vecSignal = CalculateSignal(vecSignal);
	userSignalGraph.ToGraph(vecSignal);
	userSignalGraph.RedrawWindow();


	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}



void CMyLastCourseworkDlg::OnBnClickedCheckLog()	//Проверка логаримфического масштаба
{
	UpdateData(TRUE);
	if (userIsLog)
	{ 
		userSignal.checkLog = true;
		userDFTSignal.checkLog = true;
	}
		
	else
	{
		userSignal.checkLog = false;
		userDFTSignal.checkLog = false;
	}
}


void CMyLastCourseworkDlg::OnBnClickedCheckYscale()				//Проверка масштабирования по Y
{
	UpdateData(TRUE);
	if (isScaleY)
	{
		userSignal.checkYScale = true;
		userDFTSignal.checkYScale = true;
	}
	else
	{
		userSignal.checkYScale = false;
		userDFTSignal.checkYScale = false;
	}
}


void CMyLastCourseworkDlg::OnBnClickedCheckXscale()				//Проверка масштабирования по X
{
	UpdateData(TRUE);
	if (isScaleX)
	{
		userSignal.checkXScale = true;
		userDFTSignal.checkXScale = true;
	}
	else
	{
		userSignal.checkXScale = false;
		userDFTSignal.checkXScale = false;
	}
}


void CMyLastCourseworkDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)	//Обработчик нажатий горячих клавиш
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


void CMyLastCourseworkDlg::OnMouseMove(UINT nFlags, CPoint point)		
{

	CRect rc1;
	userSignalGraph.GetWindowRect(&rc1);
	CPoint pt1 = point;
	ClientToScreen(&pt1);
	if (rc1.PtInRect(pt1))								//Отображение отмасштабированных коориднат сигнала по курсору 
	{
		userSignalGraph.ScreenToClient(&pt1);
		double x, y;
		x = pt1.x ;
		y = -1 * pt1.y ;
		CString strPos;
		strPos.Format(_T("T=%.2f Y=%.2f"), x, y);
		cursorPosCoordSignal.SetWindowTextW(strPos);
	}
	else
		cursorPosCoordSignal.SetWindowTextW(_T(""));

	CRect rc2;
	userDFTGraph.GetWindowRect(&rc2);
	CPoint pt2 = point;
	ClientToScreen(&pt2);
	if (rc2.PtInRect(pt2))								//Отображение отмасштабированных коориднат ДПФ по курсору 
	{
		userDFTGraph.ScreenToClient(&pt2);
		double x, y;
		x = pt2.x;
		y = -1 * pt2.y;
		CString strPos;
		strPos.Format(_T("T=%.2f Y=%.2f"), x, y);
		cursorPosCoordDFT.SetWindowTextW(strPos);
	}
	else
		cursorPosCoordDFT.SetWindowTextW(_T(""));

		
	CDialogEx::OnMouseMove(nFlags, point);
}   


void CMyLastCourseworkDlg::OnCbnSelchangeComboColor()		//Выбор цвета графика в ComboBox
{
	int cmb = graphColorChange.GetCurSel();

	if (LB_ERR == cmb)
	{
		cmb = 5;
	};

	switch (cmb)
	{
	case 0:
		userSignalGraph.graphUserColor.red = 5;
		userSignalGraph.graphUserColor.green = 255;
		userSignalGraph.graphUserColor.blue = 42;

		userDFTGraph.graphUserColor.red = 5;
		userDFTGraph.graphUserColor.green = 255;
		userDFTGraph.graphUserColor.blue = 42;
		break;
	case 1:
		userSignalGraph.graphUserColor.red = 255;
		userSignalGraph.graphUserColor.green = 35;
		userSignalGraph.graphUserColor.blue = 25;

		userDFTGraph.graphUserColor.red = 255;
		userDFTGraph.graphUserColor.green = 35;
		userDFTGraph.graphUserColor.blue = 25;
		break;
	case 2:
		userSignalGraph.graphUserColor.red = 255;
		userSignalGraph.graphUserColor.green = 255;
		userSignalGraph.graphUserColor.blue = 255;

		userDFTGraph.graphUserColor.red = 255;
		userDFTGraph.graphUserColor.green = 255;
		userDFTGraph.graphUserColor.blue = 255;
		break;
	case 3:
		userSignalGraph.graphUserColor.red = 255;
		userSignalGraph.graphUserColor.green = 36;
		userSignalGraph.graphUserColor.blue = 254;

		userDFTGraph.graphUserColor.red = 255;
		userDFTGraph.graphUserColor.green = 36;
		userDFTGraph.graphUserColor.blue = 254;
		break;
	case 4:
		userSignalGraph.graphUserColor.red = 255;
		userSignalGraph.graphUserColor.green = 245;
		userSignalGraph.graphUserColor.blue = 31;

		userDFTGraph.graphUserColor.red = 255;
		userDFTGraph.graphUserColor.green = 245;
		userDFTGraph.graphUserColor.blue = 31;
		break;
	case 5:
		userSignalGraph.graphUserColor.red = 0;
		userSignalGraph.graphUserColor.green = 0;
		userSignalGraph.graphUserColor.blue = 0;

		userDFTGraph.graphUserColor.red = 0;
		userDFTGraph.graphUserColor.green = 0;
		userDFTGraph.graphUserColor.blue = 0;
		break;
	}
	
	userSignalGraph.RedrawWindow();
	userDFTGraph.RedrawWindow();
}


void CMyLastCourseworkDlg::OnCbnSelchangeComboBackColor()			//Выбор цвета фона в ComboBox
{
	int cmb = backColorChange.GetCurSel();
	if (LB_ERR == cmb)
	{
		cmb = 2;
	};

	switch (cmb)
	{
	case 0:
		userSignalGraph.backUserColor.red = 147;
		userSignalGraph.backUserColor.green = 112;
		userSignalGraph.backUserColor.blue = 219;

		userDFTGraph.backUserColor.red = 147;
		userDFTGraph.backUserColor.green = 112;
		userDFTGraph.backUserColor.blue = 219;
		break;
	case 1:
		userSignalGraph.backUserColor.red = 30;
		userSignalGraph.backUserColor.green = 144;
		userSignalGraph.backUserColor.blue = 255;

		userDFTGraph.backUserColor.red = 30;
		userDFTGraph.backUserColor.green = 144;
		userDFTGraph.backUserColor.blue = 255;
		break;
	case 2:
		userSignalGraph.backUserColor.red = 255;
		userSignalGraph.backUserColor.green = 255;
		userSignalGraph.backUserColor.blue = 255;

		userDFTGraph.backUserColor.red = 255;
		userDFTGraph.backUserColor.green = 255;
		userDFTGraph.backUserColor.blue = 255;
		break;
	case 3:
		userSignalGraph.backUserColor.red = 240;
		userSignalGraph.backUserColor.green = 128;
		userSignalGraph.backUserColor.blue = 128;

		userDFTGraph.backUserColor.red = 240;
		userDFTGraph.backUserColor.green = 128;
		userDFTGraph.backUserColor.blue = 128;
		break;
	case 4:
		userSignalGraph.backUserColor.red = 50;
		userSignalGraph.backUserColor.green = 205;
		userSignalGraph.backUserColor.blue = 50;

		userDFTGraph.backUserColor.red = 50;
		userDFTGraph.backUserColor.green = 205;
		userDFTGraph.backUserColor.blue = 50;
		break;
	case 5:
		userSignalGraph.backUserColor.red = 128;
		userSignalGraph.backUserColor.green = 128;
		userSignalGraph.backUserColor.blue = 128;

		userDFTGraph.backUserColor.red = 128;
		userDFTGraph.backUserColor.green = 128;
		userDFTGraph.backUserColor.blue = 128;
		break;
	}

	userSignalGraph.myBgrOk = false;
	userDFTGraph.myBgrOk = false;
	userSignalGraph.RedrawWindow();
	userDFTGraph.RedrawWindow();
}


void CMyLastCourseworkDlg::DoSaveSignal()		//Сохранение сигнальной функции в формат PNG
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

void CMyLastCourseworkDlg::DoSaveDFTGraph()			//Сохранение ДПФ в формат PNG
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
	userSignalGraph.ToGraph(vecSignal);
	userSignalGraph.RedrawWindow();

	vecDFTSignal.clear();
	userDFTGraph.ToGraph(vecDFTSignal);
	userDFTGraph.RedrawWindow();

	buttonLog.SetCheck(false);
	buttonScaleX.SetCheck(false);
	buttonScaleY.SetCheck(false);

	mPos.SetScrollPos(0);
	FmPos.SetScrollPos(0);
	fPos.SetScrollPos(10);
	intervalPos.SetScrollPos(1);
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

void CMyLastCourseworkDlg::SetScrollsBarRange()			//Задание диапозона и начальных значений скролл баров
{
	mPos.SetScrollRange(0, 50);
	FmPos.SetScrollRange(0, 9);
	fPos.SetScrollRange(10, 40);
	intervalPos.SetScrollRange(100, 900);
	signalScalePos.SetScrollRange(1, 1000);
	DFTScalePos.SetScrollRange(1, 10000);

	mPos.SetScrollPos(0);
	FmPos.SetScrollPos(0);
	fPos.SetScrollPos(10);
	intervalPos.SetScrollPos(100);
	signalScalePos.SetScrollPos(1);
	DFTScalePos.SetScrollPos(1);


	vecSignal.clear();
	vecSignal = CalculateSignal(vecSignal);
	userSignalGraph.ToGraph(vecSignal);
	userSignalGraph.RedrawWindow();

	vecDFTSignal.clear();
	vecDFTSignal = CalculateDFTSignal(vecDFTSignal);
	userDFTGraph.ToGraph(vecDFTSignal);
	userDFTGraph.RedrawWindow();
}



