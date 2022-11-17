
// DEScoding.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CDEScodingApp:
// Сведения о реализации этого класса: DEScoding.cpp
//

class CDEScodingApp : public CWinApp
{
public:
	CDEScodingApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDEScodingApp theApp;
