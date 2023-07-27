#include "CII_End_Term.h"


void read_ini() {
	// ini�t�@�C���ǂݍ��ݏ���
	char currentDirectory[BUFFSIZE];
	getCurrentDirectory(currentDirectory);

	char section[BUFFSIZE];
	sprintf_s(section, "section1");
	char keyword[BUFFSIZE];
	sprintf_s(keyword, "keyword1");
	char filePath[BUFFSIZE];
	sprintf_s(filePath, "%s\\Setting.ini", currentDirectory);



	//�f�[�^�ǂݍ���
	struct Book book1;

	//ini�t�@�C������ǂݍ���
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


	// Book�N���X�̃I�u�W�F�N�g��std::vector<std::string>�ɕϊ����ăt�@�C���ɒǉ�
	std::vector<std::wstring> rowData = book1.toVector();
	const std::string filename = "Books.csv";
	if (book1.title == NULL) {
		printf("�^�C�g�����Ȃ����ߒǉ��ł��܂���B");
	}
	else {
		appendToCSV(filename, rowData);
	}
}


// CSV�t�@�C���ɐV�����s��ǉ����郁�\�b�h
void appendToCSV(const std::string& filename, const std::vector<std::wstring>& row) {
	std::wofstream file;
	file.open(filename, std::ios::app | std::ios::binary); // �ǉ��������݃��[�h�ƃo�C�i�����[�h�Ńt�@�C�����I�[�v��
	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>)); // UTF-8�G���R�[�f�B���O��ݒ�

	if (!file.is_open()) {
		std::wcerr << L"�t�@�C�����I�[�v���ł��܂���ł���: " << std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filename) << std::endl;
		return;
	}

	// �V�����s��CSV�t�H�[�}�b�g�ɕϊ����ăt�@�C���ɏ�������
	for (size_t i = 0; i < row.size(); ++i) {
		// �J���}���܂ޏꍇ�A�f�[�^���_�u���N�H�[�g�ň͂�
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

	// �t�@�C���ɍs��ǉ�
	file.close();
}