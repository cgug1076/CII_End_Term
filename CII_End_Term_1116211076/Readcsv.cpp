#include "CII_End_Term.h"

// �f�[�^�ǂݎ��
struct Library ReadCSV() {

	Library Library1;
	Book* previousBook = NULL;

	//-------�f�[�^�擾----------//
	FILE* fp;
	char s[BUFFSIZE];
	errno_t error;
	char fileName[BUFFSIZE];
	sprintf_s(fileName, BUFFSIZE, "Books.csv");
	error = fopen_s(&fp, fileName, "r");

	char* p1; // char�^�|�C���^���[�N
	char delim[] = ",";//�f���~�^�i�����n����j�����ł̓J���}�Ƌ�
	char* ctx = 0;
	int d = 0, days = 0;

	if (error != 0) {
		fprintf_s(stderr, "failed to open");

	}
	else {
		fprintf_s(stderr, "open\n");

		int i = 1;
		while (fgets(s, BUFFSIZE, fp) != NULL) {
			Book* tmp = new Book();


			//== �ϊ������idelim�ŕ�������������̐��l�ϊ��j==//
			p1 = strtok_s(s, delim, &ctx); // title
			tmp->title = p1;

			p1 = strtok_s(NULL, delim, &ctx); // author
			tmp->author = p1;

			p1 = strtok_s(NULL, delim, &ctx); // eval
			tmp->evaluation = atof(p1);

			p1 = strtok_s(NULL, delim, &ctx); // genre
			tmp->genre = p1;

			p1 = strtok_s(NULL, delim, &ctx); // summary
			tmp->summary = p1;

			p1 = strtok_s(NULL, delim, &ctx); // comment
			tmp->comment = p1;


			if (i == 1) {
				Library1.firstBook = tmp;
			}
			else {
				previousBook->nextBook = tmp;
			}
			previousBook = tmp;
			i++;
			if (i > 75) {
				printf("����ȏ�ǉ��ł��܂���B");
				break;
			}
		}

		Library1.BookSize = i - 1;

		fclose(fp);


	}
	return Library1;

}