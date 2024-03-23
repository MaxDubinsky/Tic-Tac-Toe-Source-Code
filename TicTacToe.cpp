/// ------------------
/// TIC TAC Toe GAME.
/// BY M4x.
/// ------------------

#include <iostream>
#include <array>

using namespace std;

// CONSTANTS.
#define LENGTH_OF_TABLE 3
#define WIDTH_OF_TABLE 3

int random(int min, int max) {
	return(rand() % (max - min) + min);
}

enum GameVariant {
	cross = 1,
	circle = 2
};

enum GameResult {
	user_win,
	bot_win,
	draw,
	nullres
};

void getTable(char table[WIDTH_OF_TABLE][LENGTH_OF_TABLE]) {
	for (int i = 0; i < WIDTH_OF_TABLE; i++) {
		for (int j = 0; j < LENGTH_OF_TABLE; j++) {
			cout << table[i][j] << "  ";
		}
		cout << endl;
	}
}

char convert_to_char(GameVariant gamevariant) {
	switch (gamevariant) {
		case GameVariant::cross:
			return 'X';
		case GameVariant::circle:
			return 'O';
		default:
			return NULL;
	}
}

GameResult check_if_someone_win(char table[WIDTH_OF_TABLE][LENGTH_OF_TABLE], GameVariant gamevariant) {
	char ch;
	char enemy_ch;

	switch (gamevariant) {
		case GameVariant::cross:
			ch = convert_to_char(gamevariant);
			enemy_ch = 'O';
		case GameVariant::circle:
			ch = convert_to_char(gamevariant);
			enemy_ch = 'X';
	}

	for (int i = 0; i < WIDTH_OF_TABLE; ++i) {
		if (table[i][0] == ch && table[i][1] == ch && table[i][2] == ch) {
			return GameResult::user_win;
		}
		if (table[0][i] == ch && table[1][i] == ch && table[2][i] == ch) {
			return GameResult::user_win;
		}
		if (table[i][0] == enemy_ch && table[i][1] == enemy_ch && table[i][2] == enemy_ch) {
			return GameResult::bot_win;
		}
		if (table[0][i] == enemy_ch && table[1][i] == enemy_ch && table[2][i] == enemy_ch) {
			return GameResult::bot_win;
		}
	}

	if (table[0][0] == ch && table[1][1] == ch && table[2][2] == ch) {
		return GameResult::user_win;
	}
	if (table[0][2] == ch && table[1][1] == ch && table[2][0] == ch) {
		return GameResult::user_win;
	}
	if (table[0][0] == enemy_ch && table[1][1] == enemy_ch && table[2][2] == enemy_ch) {
		return GameResult::bot_win;
	}
	if (table[0][2] == ch && table[1][1] == ch && table[2][0] == ch) {
		return GameResult::bot_win;
	}

	bool isTableFull = true;
	for (int i = 0; i < WIDTH_OF_TABLE; ++i) {
		for (int j = 0; j < LENGTH_OF_TABLE; ++j) {
			if (table[i][j] == '.') {
				isTableFull = false;
				break;
			}
		}
		if (!isTableFull) {
			break;
		}
	}
	if (isTableFull) {
		return GameResult::draw;
	}

	return GameResult::nullres;
}

bool isBoxEmpty(char table[WIDTH_OF_TABLE][LENGTH_OF_TABLE], int mesh, int column) {
	if (table[column][mesh] != '.') {
		return false;
	}
	else {
		return true;
	}
}

void opponent_makes_move(char table[WIDTH_OF_TABLE][LENGTH_OF_TABLE], GameVariant player_gamevariant) {
	int mesh = random(0, 3);
	int column = random(0, 3);

	if (isBoxEmpty(table, mesh, column)) {
		if (player_gamevariant == GameVariant::cross) {
			table[column][mesh] = 'O';
		}
		if (player_gamevariant == GameVariant::circle) {
			table[column][mesh] = 'X';
		}
	}
	else {
		opponent_makes_move(table, player_gamevariant);
	}
}

void gamevariant_saytype(GameVariant gamevariant) {
	if (gamevariant == GameVariant::cross) {
		cout << "You're cross." << endl;
	}
	if (gamevariant == GameVariant::circle) {
		cout << "You're circle." << endl;
	}
	
	if (gamevariant != GameVariant::cross && gamevariant != GameVariant::circle) {
		gamevariant_saytype(gamevariant);
	}
}

bool tableIsFull(char table[WIDTH_OF_TABLE][LENGTH_OF_TABLE]) {
	for (int i = 0; i < table[i][0]; i++) {
		for (int j = 0; j < table[0][j]; j++) {
			if (table[i][j] != 'O' && table[i][j] != 'X') {
				return false;
			}
		}
	}
	return true;
}

bool tableIsFullWith(char table[WIDTH_OF_TABLE][LENGTH_OF_TABLE], char ch) {
	for (int i = 0; i < table[i][0]; i++) {
		for (int j = 0; j < table[0][j]; j++) {
			if (table[i][j] != ch) {
				return false;
			}
		}
	}
	return true;
}

GameVariant choosing_variant() {
	int rand_num = random(1, 2);
	switch (rand_num)
	{
	case 1:
		return GameVariant::cross;
		break;
	case 2:
		return GameVariant::circle;
		break;
	default:
		break;
	}
}

int main() {
	// MAIN TABLE.
	char table[WIDTH_OF_TABLE][LENGTH_OF_TABLE] = { {'.','.','.'}, {'.','.','.'}, {'.','.','.'} };
	
	bool gameIsOver = false;
	GameResult gameresult = nullres;
	GameVariant gamevariant = choosing_variant();

	gamevariant_saytype(gamevariant);

	while (gameIsOver != true) {
		int mesh;
		int column;

		getTable(table);

		cout << "Enter mesh: ";
		cin >> mesh;
		if (mesh < 0 || mesh > 2) {
			cout << "Wrong column, try again." << endl;
		}
		else {
			cout << "Enter column: ";
			cin >> column;
			if (column < 0 || column > 2) {
				cout << "Wrong mesh, try again." << endl;
			}
			else {
				if (isBoxEmpty(table, mesh, column)) {
					if (gamevariant == GameVariant::cross) {
						table[column][mesh] = 'X';
						gameresult = check_if_someone_win(table, gamevariant);
						if (gameresult != GameResult::nullres) {
							gameIsOver = true;
						}
						opponent_makes_move(table, gamevariant);
						gameresult = check_if_someone_win(table, gamevariant);
						if (gameresult != GameResult::nullres) {
							gameIsOver = true;
						}
					}
					if (gamevariant == GameVariant::circle) {
						table[column][mesh] = 'O';
						gameresult = check_if_someone_win(table, gamevariant);
						if (gameresult != GameResult::nullres) {
							gameIsOver = true;
						}
						opponent_makes_move(table, gamevariant);
						gameresult = check_if_someone_win(table, gamevariant);
						if (gameresult != GameResult::nullres) {
							gameIsOver = true;
						}
					}
				}
				else {
					cout << "This box (" << mesh << " mesh, " << column << " column) isn't empty." << endl;
				}
			}
		}
		if (tableIsFullWith(table, '.')) {
			gameIsOver = true;
		}
	}

	getTable(table);

	switch (gameresult) {
		case GameResult::user_win:
			cout << "You won!" << endl;
			break;
		case GameResult::bot_win:
			cout << "Bot won!" << endl;
			break;
		case GameResult::draw:
			cout << "Draw!" << endl;
			break;
		case GameResult::nullres:
			cout << "Null." << endl;
			break;
	}

	return 0;
}