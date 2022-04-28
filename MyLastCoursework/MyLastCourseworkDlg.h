
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
	std::vector<CPoint> userVec;

public:
	CRect rc;
	size_t GetSignalPoints(std::vector<CPoint>& vecDst) { vecDst = userVec; return userVec.size(); }

public:
	std::vector <CPoint> vec;
	std::vector <CPoint> Calculate(std::vector <CPoint> vc);

public:
	afx_msg void OnBnClickedDrawGraphic();
	afx_msg void OnStnClickedStaticPaint();
	Paint mySignalGraph;
	
};
