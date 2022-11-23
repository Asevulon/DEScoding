
// MyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "DEScoding.h"
#include "MyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно MyDlg



MyDlg::MyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DESCODING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &MyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_LCW, &MyDlg::OnBnClickedLcw)
	ON_BN_CLICKED(IDC_LDW, &MyDlg::OnBnClickedLdw)
	ON_BN_CLICKED(IDC_DECODE, &MyDlg::OnBnClickedDecode)
	ON_BN_CLICKED(IDC_SAVE1, &MyDlg::OnBnClickedSave1)
	ON_BN_CLICKED(IDC_LOAD1, &MyDlg::OnBnClickedLoad1)
	ON_BN_CLICKED(IDC_SAVE2, &MyDlg::OnBnClickedSave2)
	ON_BN_CLICKED(IDC_LOAD2, &MyDlg::OnBnClickedLoad2)
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg

BOOL MyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	ihWnd = GetDlgItem(IDC_EDIT1)->GetSafeHwnd();
	chWnd = GetDlgItem(IDC_EDIT2)->GetSafeHwnd();
	khWnd = GetDlgItem(IDC_EDIT3)->GetSafeHwnd();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MyDlg::OnPaint()
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
HCURSOR MyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void MyDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	int ilen(GetWindowTextLengthA(ihWnd)), klen (GetWindowTextLengthA(khWnd));
	if (klen > 0 && klen != 8)
	{
		MessageBox(L"Введите ключ корректной длины (8 символов). Либо оставьте поле пустым, тогда ключ создастся сам.", L"Неверная длина ключа.", MB_OK);
		return;
	}
	char* itext = new char[ilen + 1];
	char* ktext = new char[klen + 1];
	GetWindowTextA(ihWnd, itext, sizeof(char) * (ilen + 1));
	GetWindowTextA(khWnd, ktext, sizeof(char) * (klen + 1));
	

	tall.SetIstr(string(itext));
	tall.SetKey(string(ktext));
	tall.CodeString(klen == 0);
	
	SetWindowTextA(khWnd, tall.GetKey().c_str());
	SetWindowTextA(chWnd, tall.GetOstr().c_str());
	

	codedtxt = tall.GetOstr();


	delete[]itext;
	delete[]ktext;
}


void MyDlg::OnBnClickedLcw()
{
	// TODO: добавьте свой код обработчика уведомлений
	int klen(GetWindowTextLengthA(khWnd));
	if (klen > 0 && klen != 8)
	{
		MessageBox(L"Введите ключ корректной длины (8 символов). Либо оставьте поле пустым, тогда ключ создастся сам.", L"Неверная длина ключа.", MB_OK);
		return;
	}
	char* ktext = new char[klen + 1];
	GetWindowTextA(khWnd, ktext, sizeof(char) * (klen + 1));
	

	tall.SetKey(string(ktext));
	tall.LoadCodeWrite(klen==0);
	SetWindowTextA(chWnd, tall.GetOstr().c_str());
	SetWindowTextA(khWnd, tall.GetKey().c_str());
	delete[]ktext;
}


void MyDlg::OnBnClickedLdw()
{
	// TODO: добавьте свой код обработчика уведомлений
	int klen(GetWindowTextLengthA(khWnd));
	if (klen != 8)
	{
		MessageBox(L"Введите ключ корректной длины (8 символов).", L"Неверная длина ключа.", MB_OK);
		return;
	}
	char* ktext = new char[klen + 1];
	GetWindowTextA(khWnd, ktext, sizeof(char) * (klen + 1));

	
	tall.SetKey(string(ktext));
	tall.LoadDecodeWrite();
	SetWindowTextA(ihWnd, tall.GetOstr().c_str());
	SetWindowTextA(khWnd, tall.GetKey().c_str());


	delete[]ktext;
}


void MyDlg::OnBnClickedDecode()
{
	// TODO: добавьте свой код обработчика уведомлений
	int clen(GetWindowTextLengthA(chWnd)), klen(GetWindowTextLengthA(khWnd));
	if (klen != 8)
	{
		MessageBox(L"Введите ключ корректной длины (8 символов).", L"Неверная длина ключа.", MB_OK);
		return;
	}
	char* ctext = new char[clen + 1];
	char* ktext = new char[klen + 1];
	GetWindowTextA(chWnd, ctext, sizeof(char) * (clen + 1));
	GetWindowTextA(khWnd, ktext, sizeof(char) * (klen + 1));

	if (codedtxt.empty())tall.SetIstr(string(ctext));
	else tall.SetIstr(codedtxt);
	tall.SetKey(string(ktext));
	tall.DecodeString();


	SetWindowTextA(ihWnd, tall.GetOstr().c_str());
	SetWindowTextA(khWnd, tall.GetKey().c_str());


	delete[]ctext;
	delete[]ktext;
}


void MyDlg::OnBnClickedSave1()
{
	int ilen(GetWindowTextLengthA(ihWnd));
	char* itext = new char[ilen + 1];
	GetWindowTextA(ihWnd, itext, sizeof(char) * (ilen + 1));


	CFileDialog file1_dialog(1);
	file1_dialog.DoModal();

	CString path = file1_dialog.GetPathName();
	if (path.GetLength() == 0)return;


	ofstream ostr(path, ios::binary);
	ostr.write(itext, sizeof(char) * (ilen + 1));
	ostr.close();


	delete[]itext;
}


void MyDlg::OnBnClickedLoad1()
{
	CFileDialog file1_dialog(1);
	file1_dialog.DoModal();

	CString path = file1_dialog.GetPathName();
	if (path.GetLength() == 0)return;


	string in;


	ifstream istr(path, ios::binary);
	while (1)
	{
		char c = 0;
		istr.read(&c, sizeof(c));
		if (istr.eof())break;
		in += c;
	}
	istr.close();
	SetWindowTextA(ihWnd, in.c_str());
}


void MyDlg::OnBnClickedSave2()
{
	CFileDialog file1_dialog(1);
	file1_dialog.DoModal();

	CString path = file1_dialog.GetPathName();
	if (path.GetLength() == 0)return;


	if (codedtxt.empty())
	{
		int clen(GetWindowTextLengthA(chWnd));
		char* ctext = new char[clen + 1];
		GetWindowTextA(chWnd, ctext, sizeof(char) * (clen + 1));


		ofstream ostr(path, ios::binary);
		ostr.write(ctext, sizeof(char) * (clen + 1));
		ostr.close();


		delete[]ctext;
	}
	else
	{
		ofstream ostr(path, ios::binary);
		for (int i = 0; i < codedtxt.size(); i++)
		{
			char c = codedtxt[i];
			ostr.write(&c, sizeof(c));
		}
		ostr.close();
	}
}


void MyDlg::OnBnClickedLoad2()
{
	CFileDialog file1_dialog(1);
	file1_dialog.DoModal();

	CString path = file1_dialog.GetPathName();
	if (path.GetLength() == 0)return;


	string in;


	ifstream istr(path, ios::binary);
	while (1)
	{
		char c = 0;
		istr.read(&c, sizeof(c));
		if (istr.eof())break;
		in += c;
	}
	istr.close();
	SetWindowTextA(chWnd, in.c_str());
	codedtxt = in;
}
