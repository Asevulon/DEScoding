#pragma once
#include"DES.h"
#include<fstream>

static HWND ihWnd;
static HWND chWnd;
static HWND khWnd;


class TextAlloc
{
private:
	string istr;
	string ostr;
	string key;
	CFile file;
	

	DES des;


	int addBytes;


protected:
	char* StringToChar(string& data);


public:
	TextAlloc();


	void SetIstr(string& data);
	void SetKey(string& data);
	

	string GetKey();
	string GetOstr();
	int getAddBytes();


	void CodeString(bool createkey = 0);
	void DecodeString();
	void LoadCodeWrite(bool createkey = 0);
	void LoadDecodeWrite();
};