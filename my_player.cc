#include <stdlib.h>
#include <map>
#include <set>
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;



/* convert player number to board symbols */
static char num2sym(char input) {
	switch (input) {
		case '0':
			return 'X';
		case '1':
			return 'O';
		case '.':
			return ' ';
		default:
			return input;
	}
}

/* given a board, this function returns EVERY free space on that board */
static set<char> getFreeSpaces(char board[24]) {
	set<char> free_spaces;
	char current_space = 'A';
	for(int i = 0; i < 24; i++) {
		if(board[i] == '.') {
			free_spaces.insert(current_space);
		}
		current_space++;
	}
	return free_spaces;
}

/* given the player and the board state,
returns the number of pieces of that player on currently board state */
static int piecesOnTheBoard(unsigned player, char board[24]) {
	int number_of_players_pieces_on_the_board = 0;
	char player_char = ' ';
	if(player == 1) {
		player_char = '1';
	} else if(player == 0) {
		player_char = '0';
	}
	for(int i = 0; i < 24; i++) {
		if(board[i] == player_char) {
			number_of_players_pieces_on_the_board++;
		}

	}
	return number_of_players_pieces_on_the_board;
}

static bool hasPlayerOnly3Pieces(unsigned player, int number_of_unplaced_pieces, char board[24]) {
	bool has_only_three_pieces = false;
	int number_of_players_pieces_on_the_board = piecesOnTheBoard(player, board);

	if(number_of_unplaced_pieces == 0 && number_of_players_pieces_on_the_board == 3) {
		cout << "ATTTTTTENNNNNNTION u just have 3 pieces!";

	}
	return true;
}

/* given the map of a board(keys = nodes, values = edges) and which nodes are
not occupied, this function returns every possible move the player can make*/
static map<char, set<char>> getPossibleMoves(map<char, set<char>> all_possibilities, set<char> free_spaces, int number_of_unplaced_pieces) {
	map<char, set<char>> possible_moves = all_possibilities;
	if(number_of_unplaced_pieces == 0) {
		cout << "Attention! Player has only 3 pieces. Therefore he/she can move freely through the board!";
		return all_possibilities;
	}

	//debugging-loop
	/*cout << "\nbefore removing occupied spaces\n";
	for(map<char,set<char>>::iterator entry = all_possibilities.begin(); entry != all_possibilities.end(); ++entry) {
		cout << entry->first << " --> (";
		for(set<char>::iterator it = entry->second.begin(); it != entry->second.end(); ++it) {
			cout << *it << ',';
		}
		cout << ")\n";
	}*/

	//loops to filter the occupied spaces out
	for(map<char,set<char>>::iterator entry = all_possibilities.begin(); entry != all_possibilities.end(); ++entry) {
		for(auto fs = begin(free_spaces); fs != end(free_spaces); ++fs) {
			for(auto it = begin(entry->second); it != end(entry->second); ++it) {
				if(*fs == *it) {
					break;
				}
				else {
					if(free_spaces.find(*it) == free_spaces.end()) {
						entry->second.erase(it);
					}
				}
			}
		}
	}

	//debugging-loop
	/*cout << "\nafter removing occupied space s\n";
	for(map<char,set<char>>::iterator entry = all_possibilities.begin(); entry != all_possibilities.end(); ++entry) {
		cout << entry->first << " --> (";
		for(set<char>::iterator it = entry->second.begin(); it != entry->second.end(); ++it) {
			cout << *it << ',';
		}
		cout << ")\n";
	}*/


	return possible_moves;
}


int main(void) {
	/* current game state is delivered via file descriptor 3 */
	FILE *state_input = fdopen(3, "r");
	/* we output our move via file descriptor 4 */
	FILE *move_output = fdopen(4, "w");

	if (!state_input || !move_output) {
		fprintf(stderr, "error accessing file descriptors\n");
		exit(1);
	}

	//My variables
	set<char> a = {'B', 'J'};
	set<char> b = {'A', 'C', 'E'};
	set<char> c = {'B', 'O'};
	set<char> d = {'E', 'K'};
	set<char> e = {'B', 'D', 'F', 'H'};
	set<char> f = {'E', 'N'};
	set<char> g = {'H', 'L'};
	set<char> h = {'E', 'G', 'I'};
	set<char> i = {'H', 'M'};
	set<char> j = {'A', 'K', 'V'};
	set<char> k = {'D', 'J', 'L', 'S'};
	set<char> l = {'G', 'K', 'P'};
	set<char> m = {'I', 'N', 'R'};
	set<char> n = {'F', 'M', 'O', 'U'};
	set<char> o = {'C', 'N', 'X'};
	set<char> p = {'L', 'Q'};
	set<char> q = {'P', 'R', 'T'};
	set<char> r = {'M', 'Q'};
	set<char> s = {'K', 'T'};
	set<char> t = {'Q', 'S', 'U', 'W'};
	set<char> u = {'N', 'T'};
	set<char> v = {'J', 'W'};
	set<char> w = {'V', 'X'};
	set<char> x = {'O', 'W'};

	map<char, set<char>> all_possibilities = {
		{'A', a}, {'B', b}, {'C', c}, {'D', d}, {'E', e}, {'F', f},
		{'G', g}, {'H', h}, {'I', i}, {'J', j}, {'K', k}, {'L', l},
		{'M', m}, {'N', n}, {'O', o}, {'P', p}, {'Q', q}, {'R', r},
		{'S', s}, {'T', t}, {'U', u}, {'V', v}, {'W', w}, {'X', x}
	};

	while (1) {
		/**Game's state variables*/
		unsigned current_player;
		unsigned unplaced_pieces[2];
		char board[24];
		char piece_move, piece_put, piece_kill;
		char newline;
		int matches;

		/* Initialize game's state variables */
		matches = fscanf(state_input, "%u %u %u%c", &current_player,
						 &unplaced_pieces[0], &unplaced_pieces[1], &newline);
		if (matches != 4) {
			fprintf(stderr, "error while reading the game state\n");
			break;
		}
		matches = fscanf(state_input, "%24c%c", board, &newline);
		if (matches != 2) {
			fprintf(stderr, "error while reading the board state\n");
			break;
		}

		/* Now pretty-print the board and ask the user for a move. */
		if (unplaced_pieces[0]) {
			printf("Player 0: ");
			for (unsigned i = 0; i < unplaced_pieces[0]; i++)
				printf("%c", num2sym('0'));
			printf("\n");
		}
		if (unplaced_pieces[1]) {
			printf("Player 1: ");
			for (unsigned i = 0; i < unplaced_pieces[1]; i++)
				printf("%c", num2sym('1'));
			printf("\n\n");
		}
		printf("Current board situation on the left,\n");
		printf("letters for identifying the places on the right:\n");
		printf("\n");
		printf("%c----------%c----------%c            A----------B----------C\n",
			   num2sym(board[0]), num2sym(board[1]), num2sym(board[2]));
		printf("|          |          |            |          |          |\n");
		printf("|   %c------%c------%c   |            |   D------E------F   |\n",
			   num2sym(board[3]), num2sym(board[4]), num2sym(board[5]));
		printf("|   |      |      |   |            |   |      |      |   |\n");
		printf("|   |   %c--%c--%c   |   |            |   |   G--H--I   |   |\n",
			   num2sym(board[6]), num2sym(board[7]), num2sym(board[8]));
		printf("|   |   |     |   |   |            |   |   |     |   |   |\n");
		printf("%c---%c---%c     %c---%c---%c            J---K---L     M---N---O\n",
			   num2sym(board[9]), num2sym(board[10]), num2sym(board[11]),
			   num2sym(board[12]), num2sym(board[13]), num2sym(board[14]));
		printf("|   |   |     |   |   |            |   |   |     |   |   |\n");
		printf("|   |   %c--%c--%c   |   |            |   |   P--Q--R   |   |\n",
			   num2sym(board[15]), num2sym(board[16]), num2sym(board[17]));
		printf("|   |      |      |   |            |   |      |      |   |\n");
		printf("|   %c------%c------%c   |            |   S------T------U   |\n",
			   num2sym(board[18]), num2sym(board[19]), num2sym(board[20]));
		printf("|          |          |            |          |          |\n");
		printf("%c----------%c----------%c            V----------W----------X\n",
			   num2sym(board[21]), num2sym(board[22]), num2sym(board[23]));
		printf("\n");
		printf("Player %d's move (%c).\n", current_player,
			   num2sym((char)current_player + '0'));
		piecesOnTheBoard(current_player, board);
		map<char, set<char>> filtered_moves = getPossibleMoves(all_possibilities,getFreeSpaces(board), unplaced_pieces[current_player]);

		/* Unless we have unplaced pieces, ask which piece to move. */
		if (unplaced_pieces[current_player]) {
			piece_move = ' ';
		} else {
			printf("  Which piece do you want to move:    ");
			fflush(stdout);
			matches = fscanf(stdin, "%c%c", &piece_move, &newline);
			if (matches != 2) break;
		}

		/* Ask where to place the piece. */
		printf("  Where do you want to put the piece: ");
		fflush(stdout);
		matches = fscanf(stdin, "%c%c", &piece_put, &newline);
		if (matches != 2) break;

		/* Remove a piece from your opponent? */
		printf("You can now remove a piece from your opponent.\n");
		printf("Enter nothing if this is not appropriate according to the rules.\n");
		printf("  Which piece do you want to remove:  ");
		fflush(stdout);
		matches = fscanf(stdin, "%c", &piece_kill);
		if (piece_kill != '\n')
			matches = fscanf(stdin, "%c", &newline);
		if (matches != 1) break;
		printf("Thank you for your move.\n");
		printf("\n");

		/* Output our move as three characters, followed by a newline.
		 * The first character specifies the piece to move or a space if an
		 * unplaced piece is used.
		 * The second character specifies the place to put the piece.
		 * The third character specifies an opponent's piece to remove, or a
		 * space if this is not appropriate. */
		fprintf(move_output, "%c%c%c\n", piece_move, piece_put, piece_kill);

		/* Flush the buffer so the MCP actually receives our move. */
		fflush(move_output);
	}

	/* cleanup */
	fclose(state_input);
	fclose(move_output);

	/* in all cases we get here, an error happened */
	return 1;
}
