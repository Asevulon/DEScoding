﻿
// MyDlg.h: файл заголовка
//

#pragma once


#include"TextAllocator.h"


// Диалоговое окно MyDlg
class MyDlg : public CDialogEx
{
// Создание
public:
	MyDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DESCODING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	TextAlloc tall;
	afx_msg void OnBnClickedLcw();
	afx_msg void OnBnClickedLdw();
	afx_msg void OnBnClickedDecode();
	string codedtxt;
	afx_msg void OnBnClickedSave1();
	afx_msg void OnBnClickedLoad1();
	afx_msg void OnBnClickedSave2();
	afx_msg void OnBnClickedLoad2();
};
