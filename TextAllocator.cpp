#include"pch.h"
#include"TextAllocator.h"


TextAlloc::TextAlloc() :istr(""), ostr(""), addBytes(0) {}


void TextAlloc::SetIstr(string& data)
{
	istr = data;
}
void TextAlloc::SetKey(string& data)
{
	key = data;
}


string TextAlloc::GetKey()
{
	return key;
}
string TextAlloc::GetOstr()
{
	return ostr;
}
int TextAlloc::getAddBytes()
{
	return addBytes;
}


void TextAlloc::CodeString(bool createkey)
{
	ostr = "";
	if (createkey)key = des.CreateAndGetKey();


	while (istr.size() > 7)
	{
		string temp = istr.substr(0, 8);
		ostr += des.Code(temp, key);
		istr.erase(0, 8);
	}


	if (istr.size() > 0)
	{
		addBytes = 8 - istr.size();
		for (int i = 0; i < addBytes; i++)istr += char(0);
		ostr += des.Code(istr, key);
	}
}
void TextAlloc::DecodeString()
{
	ostr = "";
	while (istr.size() > 7)
	{
		string temp = istr.substr(0, 8);
		ostr += des.Decode(temp, key);
		istr.erase(0, 8);
	}
}



void TextAlloc::LoadCodeWrite(bool createkey)
{
	CFileDialog file1_dialog(1);
	file1_dialog.DoModal();

	CString path = file1_dialog.GetPathName();
	if (path.GetLength() == 0)return;
	ifstream istr(path, ios::binary);


	CFileDialog file2_dialog(1);
	file2_dialog.DoModal();
	path = file2_dialog.GetPathName();
	if (path.GetLength() == 0)return;
	ofstream ostr(path, ios::binary);


	if (createkey)key = des.CreateAndGetKey();
	

	while (1)
	{
		//заполняет строку
		string in = "";
		for (int i = 0; i < 8; i++)
		{
			char c = 0;
			istr.read(&c, sizeof(c));
			if (istr.eof())break;
			in += c;
		}


		if (in.size() == 0)break;
		if (in.size() < 8)
		{
			addBytes = 8 - in.size();
			for (int i = 0; i < addBytes; i++)in += char(0);
		}


		char* out = StringToChar(des.Code(in, key));
		ostr.write(out, sizeof(out));
	}


	istr.close();
	ostr.close();
}
void TextAlloc::LoadDecodeWrite()
{
	CFileDialog file1_dialog(1);
	file1_dialog.DoModal();

	CString path = file1_dialog.GetPathName();
	if (path.GetLength() == 0)return;
	ifstream istr(path, ios::binary);


	CFileDialog file2_dialog(1);
	file2_dialog.DoModal();
	path = file2_dialog.GetPathName();
	if (path.GetLength() == 0)return;
	ofstream ostr(path, ios::binary);


	while (1)
	{
		//заполняет строку
		string in = "";
		for (int i = 0; i < 8; i++)
		{
			char c = 0;
			istr.read(&c, sizeof(c));
			if (istr.eof())break;
			in += c;
		}


		if (in.size() == 0)break;


		char* out = StringToChar(des.Decode(in, key));
		ostr.write(out, sizeof(out));
	}


	istr.close();
	ostr.close();
}


char* TextAlloc:: StringToChar(string& data)
{
	char res[8];
	for (int i = 0; i < data.size(); i++)res[i] = data[i];
	return res;
}
