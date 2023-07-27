#include "CII_End_Term.h"


void drawRectangle(int x, int y, int width, int height);
void appendToCSV(const std::string& filename, const std::vector<std::wstring>& row);

int main() {
	
	initscr(); // PDCursesの初期化
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE); // キーボード入力を待たずに進行するように設定

	initscr(); // PDCursesの初期化



	// 色の準備
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);	// 色1 は黒地に黄文字
	init_pair(2, COLOR_BLACK, COLOR_BLUE);	// 色2 は青地に黒文字
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);// 色3は黄色地に黒文字
	init_pair(4, COLOR_RED, COLOR_BLACK);	// 色4 は黒地に赤文字
	init_pair(5, COLOR_WHITE, COLOR_BLACK);	// 色5 は黒地に白文字
	init_pair(6, COLOR_GREEN, COLOR_BLACK);	// 色6 は黒地に緑文字
	init_pair(7, COLOR_BLUE, COLOR_BLACK);	// 色7 は黒地に青文字


	//iniファイルから読み込み、csvに書き込み
	read_ini();

	//csvから読み込み
	Library Library1;
	Library1 = ReadCSV();



	// 枠の位置とサイズ
	int B_x = 0;
	int B_y = 16;
	int B_width = 70;
	int B_height = 13;

	// 四角い枠を描画
	drawRectangle(B_x, B_y, B_width, B_height);


	// 枠の位置とサイズ
	B_x = 75;
	B_y = 1;
	B_width = 1;
	B_height = 29;

	// 四角い枠を描画
	drawRectangle(B_x, B_y, B_width, B_height);
	
	refresh();

	// 本棚
	attrset(COLOR_PAIR(5));
	int x = 80;
	int y = 3;
	int i = 1;
	while (i <= Library1.BookSize) {
		mvprintw(y, x, "%d冊目", i);
		i++;
		y++;
		if (i == 26) {
			y = 3;
			x = 95;
		}else if(i == 51) {
			y = 3;
			x = 110;
		}
	}
	attrset(COLOR_PAIR(1));


	//最高評価
	Book *No1 = NULL, *No2 = NULL, *No3 = NULL;
	Book* previousBook = Library1.firstBook;
	No1 = previousBook;
	while (previousBook->nextBook != NULL) {
		if (previousBook->evaluation >= No1->evaluation) {
			No3 = No2;
			No2 = No1;
			No1 = previousBook;
		}
		else if(previousBook->evaluation >= No2->evaluation) {
			No3 = No2;
			No2 =  previousBook;
		}

		else if (previousBook->evaluation >= No3->evaluation) {
			No3 = previousBook;
		}
		previousBook = previousBook->nextBook;
	}
	attrset(COLOR_PAIR(5));
	mvprintw(18, 1, "No.1：%s", No1->title);
	mvprintw(18, 30, "評価：%.1f", No1->evaluation);

	if (No2 != NULL) {
		mvprintw(20, 1, "No.2：%s", No2->title);
		mvprintw(20, 30, "評価：%.1f", No2->evaluation);
	}
	if (No3 != NULL) {
		mvprintw(22, 1, "No.3：%s", No3->title);
		mvprintw(22, 30, "評価：%.1f", No3->evaluation);
	}

	refresh();
	

	// キー入力のための変数
	int key;
	int re = 1;
	int selectedBook = 1;
	int P_x = 77;
	int P_y = 3;
	previousBook = Library1.firstBook;


	//カーソル初期位置
	mvprintw(P_y + selectedBook - 1, P_x, "*");
	

	// キー入力
	while (1) {
		re = 1;
		i = 29;
		y = 11;
		x = 110;
		attrset(COLOR_PAIR(5));




		// 選択された本にカーソルを表示

		if (selectedBook <= 25) {
			P_x = 77;
			mvprintw(P_y + selectedBook - 1, P_x, "*");
		}
		else if(selectedBook <= 50) {
			P_x = 92;
			mvprintw(P_y - 25 + selectedBook - 1, P_x, "*");
		}
		else {
			P_x = 107;
			mvprintw(P_y - 50 + selectedBook - 1, P_x, "*");
		}


		// フォーマット
		mvprintw(2, 3, "                                            ");
		mvprintw(2, 3, "タイトル：%s", previousBook->title);
		 
		mvprintw(5, 3, "                       ");
		mvprintw(5, 3, "著者：%s", previousBook->author);

		mvprintw(5, 25, "                       ");
		mvprintw(5, 25, "ジャンル：%s", previousBook->genre);

		mvprintw(8, 3, "                                            ");
		mvprintw(8, 3, "評価：%.1f", previousBook->evaluation);

		mvprintw(11, 3, "                                           ");
		mvprintw(11, 3, "要約：%s", previousBook->summary);

		mvprintw(14, 3, "                                           ");
		mvprintw(14, 3, "コメント：%s", previousBook->comment);




		refresh();

		key = getch(); // キー入力を待機

		// キー入力に応じて選択された値を変更
		switch (key) {
		case KEY_UP:	// ↑
			mvprintw(P_y + selectedBook - 1, P_x, " ");
			mvprintw(P_y + selectedBook - 26, P_x, " ");
			mvprintw(P_y + selectedBook - 51, P_x, " ");
			selectedBook--;
			if (selectedBook < 1) {
				selectedBook = Library1.BookSize;
				previousBook = Library1.firstBook;
				while (Library1.BookSize - 1 > re) {
					previousBook = previousBook->nextBook;
					re++;
				}
			}
			else {
				previousBook = Library1.firstBook;
				while (selectedBook > re) {
					previousBook = previousBook->nextBook;
					re++;
				}
			}

			mvprintw(5, 5, "                        ");
			mvprintw(10, 5, "                       ");
			mvprintw(5, 50, "                        ");
			mvprintw(10, 50, "                       ");

			break;

		case KEY_DOWN:	// ↓
			mvprintw(P_y + selectedBook - 1, P_x, " ");
			mvprintw(P_y + selectedBook - 26, P_x, " ");
			mvprintw(P_y + selectedBook - 51, P_x, " ");
			selectedBook++;
			if (selectedBook > Library1.BookSize) {
				selectedBook = 1;
				previousBook = Library1.firstBook;
			}
			else {
				previousBook = previousBook->nextBook;
			}

			mvprintw(5, 5, "                        ");
			mvprintw(10, 5, "                       ");
			mvprintw(5, 50, "                        ");
			mvprintw(10, 50, "                       ");

			break;

		case 'q':
			endwin(); // PDCursesの終了
			return 0;
		}

	}
	return 0;
}






// 枠を描画
void drawRectangle(int x, int y, int width, int height) {
	int i;

	attrset(COLOR_PAIR(1));
	// 上辺
	mvhline(y, x + 1, '-', width - 2);

	// 下辺
	mvhline(y + height - 1, x + 1, '-', width - 2);

	// 左辺と右辺
	for (i = y + 1; i < y + height - 1; i++) {
		mvaddch(i, x, '|');        // 左辺
		mvaddch(i, x + width - 1, '|'); // 右辺
	}

}
