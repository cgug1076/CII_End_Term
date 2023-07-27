#pragma once
#include "CII_End_Term.h"


void getCurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(BUFFSIZE, currentDirectory);
}



//--------------------------------read--------------------------------------//

int readInt(const char* section, const char* keyword, const char* filePath) {
	int keyValue = 0;
	keyValue = GetPrivateProfileInt(section, keyword, -1, filePath);
	return keyValue;
}

double readDouble(const char* section, const char* keyword, const char* filePath) {  //delete double defaultValue
	char* keyValue = NULL;
	keyValue = (char*)malloc(BUFFSIZE);
	GetPrivateProfileString(section, keyword, "none", keyValue, BUFFSIZE, filePath), 0;
	return strtod(keyValue, 0);
}


char* readChar(const char* section, const char* keyword, const char* filePath) {  //delete , const char* returnValue
	//char keyValue[BUFFSIZE];
	char* keyValue = NULL;
	keyValue = (char*)malloc(BUFFSIZE);

	if (GetPrivateProfileString(section, keyword, "none", keyValue, BUFFSIZE, filePath) != 0) {
	}
	else {
		fprintf(stdout, "%s doesn't contain [%s] %s\n", filePath, section, keyword);
	}

	return keyValue;
}



