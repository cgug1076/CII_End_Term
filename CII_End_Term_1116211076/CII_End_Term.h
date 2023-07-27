#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <locale> 
#include <codecvt> 
#include <Windows.h>
#define BUFFSIZE 1024

void getCurrentDirectory(char* currentDirectory);


int readInt(const char* section, const char* keyword, const char* filePath);
double readDouble(const char* section, const char* keyword, const char* filePath);
char* readChar(const char* section, const char* keyword, const char* filePath);


void read_ini();
void appendToCSV(const std::string& filename, const std::vector<std::wstring>& row);

struct Library ReadCSV();


typedef struct Book {
	const char* title;
	const char* author;
	double evaluation;
	const char* genre;
	const char* summary;
	const char* comment;
	int end = NULL;
	Book* nextBook;

	// BookƒNƒ‰ƒX‚Ìƒƒ“ƒo‚ğstd::vector<std::string>‚É•ÏŠ·‚·‚éŠÖ”
	std::vector<std::wstring> toVector() const {
		std::vector<std::wstring> data;
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

		data.push_back(converter.from_bytes(title));
		data.push_back(converter.from_bytes(author));
		data.push_back(std::to_wstring(evaluation));
		data.push_back(converter.from_bytes(genre));
		data.push_back(converter.from_bytes(summary));
		data.push_back(converter.from_bytes(comment));
		data.push_back(converter.from_bytes(end));
		return data;
	}
}Book;

typedef struct Library {
	int BookSize;
	Book* firstBook;
}Library;
