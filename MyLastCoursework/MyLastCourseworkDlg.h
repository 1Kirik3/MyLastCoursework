
// MyLastCourseworkDlg.h: файл заголовка
//

#pragma once
#include "Paint.h"
#include "Calc.h"

// Диалоговое окно CMyLastCourseworkDlg
class CMyLastCourseworkDlg : public CDialogEx
{
// Создание
public:
	CMyLastCourseworkDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYLASTCOURSEWORK_DIALOG };
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

protected:
	RealSignal mySignal;
	DFTSignal myDFTSignal;
	std::vector<CPoint> userVec;

public:
	CRect rc;
	size_t GetSignalPoints(std::vector<CPoint>& vecDst) { vecDst = userVec; return userVec.size(); }

public:
	std::vector <double> myData;
	std::vector <CPoint> vecSignal;
	std::vector <CPoint> DFTSignal;
	std::vector <CPoint> CalculateSignal(std::vector <CPoint> vc);
	std::vector <CPoint> CalculateDFTSignal(std::vector <CPoint> vc);
	void SetScrollsBarRange();

public:
	afx_msg void OnBnClickedDrawGraphic();
	afx_msg void OnStnClickedStaticPaint();
	Paint mySignalGraph;
	Paint DFTGraph;
	afx_msg void OnStnClickedStaticPaint2();
	
	afx_msg void OnNMThemeChangedScrollbar2(NMHDR* pNMHDR, LRESULT* pResult);
	CScrollBar mPos;
	CScrollBar FmPos;
	CScrollBar fPos;
	CScrollBar stepPos;
	double mValue, FmValue, fValue, stepValue;
	afx_msg void OnBnClickedOk();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CString mValueText;
	CString FmValueText;
	CString fValueText;
	CString stepValueText;
};
