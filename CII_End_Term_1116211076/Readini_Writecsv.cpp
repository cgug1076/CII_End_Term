#include "CII_End_Term.h"


void read_ini() {
	// iniファイル読み込み準備
	char currentDirectory[BUFFSIZE];
	getCurrentDirectory(currentDirectory);

	char section[BUFFSIZE];
	sprintf_s(section, "section1");
	char keyword[BUFFSIZE];
	sprintf_s(keyword, "keyword1");
	char filePath[BUFFSIZE];
	sprintf_s(filePath, "%s\\Setting.ini", currentDirectory);



	//データ読み込み
	struct Book book1;

	//iniファイルから読み込み
	book1.title = readChar(section, keyword, filePath);
	sprintf_s(keyword, "keyword2");
	book1.author = readChar(section, keyword, filePath);
	sprintf_s(keyword, "keyword3");
	book1.evaluation = readDouble(section, keyword, filePath);
	sprintf_s(keyword, "keyword4");
	book1.genre = readChar(section, keyword, filePath);
	sprintf_s(keyword, "keyword5");
	book1.summary = readChar(section, keyword, filePath);
	sprintf_s(keyword, "keyword6");
	book1.comment = readChar(section, keyword, filePath);


	// Bookクラスのオブジェクトをstd::vector<std::string>に変換してファイルに追加
	std::vector<std::wstring> rowData = book1.toVector();
	const std::string filename = "Books.csv";
	if (book1.title == NULL) {
		printf("タイトルがないため追加できません。");
	}
	else {
		appendToCSV(filename, rowData);
	}
}


// CSVファイルに新しい行を追加するメソッド
void appendToCSV(const std::string& filename, const std::vector<std::wstring>& row) {
	std::wofstream file;
	file.open(filename, std::ios::app | std::ios::binary); // 追加書き込みモードとバイナリモードでファイルをオープン
	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>)); // UTF-8エンコーディングを設定

	if (!file.is_open()) {
		std::wcerr << L"ファイルをオープンできませんでした: " << std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filename) << std::endl;
		return;
	}

	// 新しい行をCSVフォーマットに変換してファイルに書き込む
	for (size_t i = 0; i < row.size(); ++i) {
		// カンマを含む場合、データをダブルクォートで囲む
		if (row[i].find(L',') != std::wstring::npos) {
			file << L"\"" << row[i] << L"\"";
		}
		else {
			file << row[i];
		}

		if (i < row.size() - 1)
			file << L",";
	}
	file << L"\n";

	// ファイルに行を追加
	file.close();
}