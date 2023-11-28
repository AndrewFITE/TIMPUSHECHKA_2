#include "modAlphaCipher.h"
using namespace std;

Cipher::Cipher(wstring & ws_key)
{
	colum = getValidKey(ws_key);
}
void Cipher::set_key(wstring & ws_key)
{
	colum = getValidKey(ws_key);
}
void Cipher::set_tableform(const wstring& open_text)
{
	len_text = open_text.size();
	if (len_text>colum) {
		num = len_text/colum;
		if (len_text%colum >0) num += 1;
	} else {
		num = 1;
	}
}
wstring Cipher::encrypt(wstring& open_text)
{
	open_text = getValidOpenText(open_text);
	set_tableform(open_text);
	wstring table_chiper[num][colum];
	int nums_text = 0;
	for (int y=0; y<num; y++) {
		for (int x=0; x<colum; x++) {
			if (nums_text < len_text) {
				table_chiper[y][x] = open_text[nums_text];
			} else {
				table_chiper[y][x] = L"-";
			}
			nums_text++;
		}
	}
	wstring encrypt_text;
	for (int x=colum-1; x>=0; x--) {
		for (int y=0; y<num; y++) {
			encrypt_text+=table_chiper[y][x];
		}
	}
	return encrypt_text;
}
wstring Cipher::decrypt(const wstring& cipher_text)
{
	set_tableform(getValidCipherText(cipher_text));
	wstring table_chiper[num][colum];
	int nums_text = 0;
	for (int x=colum-1; x>=0; x--) {
		for (int y=0; y<num; y++) {
			table_chiper[y][x] = cipher_text[nums_text];
			nums_text++;
		}
	}
	wstring decrypt_text;
	for (int y=0; y<num; y++) {
		for (int x=0; x<colum; x++) {
			if (table_chiper[y][x] != L"-")
				decrypt_text+=table_chiper[y][x];
		}
	}
	return decrypt_text;
}
inline int Cipher::getValidKey(wstring & ws_key)
{
	if (ws_key.empty())
		throw cipher_error("Empty key!");
	string s_key = codec.to_bytes(ws_key);
	for (auto & c:ws_key) {
		if (!iswdigit(c)) {
			throw cipher_error(string("Invalid key ") + s_key);
		}
	}
	int key = stoi(ws_key);
	if (key<=0) {
		throw cipher_error(string("Invalid key! Enter a number > 0"));
	}
	return key;
}
inline wstring Cipher::getValidOpenText(const wstring & ws_open_text)
{
	wstring tmp;
	for (auto c:ws_open_text) {
		if (iswalpha(c)) {
			if (iswlower(c))
				tmp.push_back(towupper(c));
			else
				tmp.push_back(c);
		}
	}
	if (tmp.empty())
		throw cipher_error("Input text is missing!");
	return tmp;
}
inline wstring Cipher::getValidCipherText(const wstring & ws_cipher_text)
{
	if (ws_cipher_text.empty())
		throw cipher_error("Output text is missing!");

	for (auto c:ws_cipher_text) {
		if (!iswupper(c)) {
			if (c!=L'-') {
				throw cipher_error(string("Invalid text!"));
			}
		}
	}
	return ws_cipher_text;
}

