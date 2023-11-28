#pragma once
#include <vector>
#include <string>
#include <map>
#include <codecvt>
#include <locale>
#include <iostream>
using namespace std;

class Cipher
{
private:
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	int colum, num, len_text;
public:
	Cipher() = delete;
	Cipher(wstring & ws_key);
	wstring encrypt(wstring& ws_open_text);
	wstring decrypt(const wstring& ws_cipher_text);
	void set_tableform(const wstring& ws_text);
	void set_key(wstring & ws_key);
	int getValidKey(wstring& ws_key);
	wstring getValidOpenText(const wstring & ws_open_text);
	wstring getValidCipherText(const wstring & ws_cipher_text);
};

class cipher_error: public invalid_argument
{
public:
	explicit cipher_error (const string& what_arg):
		invalid_argument(what_arg) {}
	explicit cipher_error (const char* what_arg):
		invalid_argument(what_arg) {}
};
