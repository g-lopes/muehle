#include <stdlib.h>
#include <map>
#include <set>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <string.h>


using namespace std;

/* returns a set with all positions occupied by given the player */
static set<char> getPlayerPositions(unsigned player, char board[24]) {
	set<char> player_positions;
	char current_space = 'A';
	char player_char = ' ';
	if(player == 1) {
		player_char = '1';
	} else if(player == 0) {
		player_char = '0';
	}
	for(int i = 0; i < 24; i++) {
		if(board[i] == player_char) {
			player_positions.insert(current_space);
		}
		current_space++;
	}

	//debugging-loop
	/*cout << '\n' << "Player occupies the following positions: ";
	for(set<char>::iterator it = player_positions.begin(); it != player_positions.end(); ++it) {
		cout << *it << ',';
	}
	cout << '\n';
	*/


	return player_positions;
}

/* returns true if the player made a mill */
static bool millsOnTheBoard(set<char> player_positions, char board[24], char piece_move, char piece_put, unsigned player) {
	char player_char = ' ';
	if(player == 1) {
		player_char = '1';
	} else if(player == 0) {
		player_char = '0';
	}

	bool made_new_mill = false;

	set<char> current_mills_identifiers;
	set<char> future_mills_identifiers;

	char current_board[24];
	char future_board[24];
	strncpy (current_board, board, sizeof(current_board));
	strncpy (future_board, board, sizeof(future_board));

	int current_number_of_mills = 0;
	int future_number_of_mills = 0;


	int piece_destination = piece_put - 'A';
	int piece_origin = piece_move - 'A';

	if(piece_move == ' ') {
		future_board[piece_destination] = player_char;
	} else {
		future_board[piece_destination] = player_char;
		future_board[piece_origin] = '.';
	}

	set<char> player_future_positions = getPlayerPositions(player, future_board);

	//debuging-loop
	/*cout << "\ncurrent board = ";
	for(int i = 0; i < 24; i++) {
		cout << current_board[i] << ',';
	}
	cout << "\n";
	cout << "\n future board = ";
	for(int i = 0; i < 24; i++) {
		cout << future_board[i] << ',';
	}
	cout << "\n";*/


	set<set<char>> all_mills = {
		{'A','B','C'},
		{'D','E','F'},
		{'G','H','I'},
		{'J','K','L'},
		{'M','N','O'},
		{'P','Q','R'},
		{'S','T','U'},
		{'V','W','X'},
		{'A','J','V'},
		{'D','K','S'},
		{'G','L','P'},
		{'B','E','H'},
		{'Q','T','W'},
		{'I','M','R'},		{'A','B','C'},
		{'A','B','C'},
		{'A','B','C'},
		{'F','N','U'},
		{'C','O','X'}
	};

	//search currently mills
	for(set<char>::iterator it = player_positions.begin(); it != player_positions.end(); ++it) {
		switch(*it) {
			case 'A': if(current_board[1] == player_char && current_board[2] == player_char) {
									cout << '\n' << " A1  CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('b');
									current_number_of_mills++;
								}
								 if(current_board[9] == player_char && current_board[21] == player_char)
								{
									cout << '\n' << " AAA  CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('j');
									current_number_of_mills++;
								}
								break;
			case 'B': if(current_board[4] == player_char && current_board[7] == player_char)
								{
									current_number_of_mills++;
									cout << '\n' << " BBB  CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('e');
								}
								break;
			case 'C': if((current_board[14] == player_char && current_board[23] == player_char))
								{
									current_number_of_mills++;
									cout << '\n' << " CCC  CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('o');
								}
								break;
			case 'D': if(current_board[10] == player_char && current_board[18] == player_char) {
									cout << '\n' << " DD2  CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('s');
									current_number_of_mills++;
								}
								if(current_board[4] == player_char && current_board[5] == player_char)
								{
									current_number_of_mills++;
									cout << '\n' << " DDD  CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('f');
								}
								break;
			case 'F': if(current_board[13] == player_char && current_board[20] == player_char)
								{
									current_number_of_mills++;
									cout << '\n' << "  FFF CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('u');
								}
								break;
			case 'G': if(current_board[7] == player_char && current_board[8] == player_char) {
									cout << '\n' << " GGGG  CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('h');
									current_number_of_mills++;
								}
								if(current_board[11] == player_char && current_board[14] == player_char)
								{
									current_number_of_mills++;
									cout << '\n' << " GGGG  CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('l');
								}
								break;
			case 'I': if(current_board[12] == player_char && current_board[17] == player_char)
								{
									current_number_of_mills++;
									cout << '\n' << "  III CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('m');
								}
								break;
			case 'J': if((current_board[10] == player_char && current_board[11] == player_char))
								{
									current_number_of_mills++;
									cout << '\n' << "  JJJ CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('k');
								}
								break;
			case 'M': if(current_board[13] == player_char && current_board[14] == player_char)
								{
									current_number_of_mills++;
									cout << '\n' << "  MMM CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('n');
								}
								break;
			case 'P': if(current_board[16] == player_char && current_board[17] == player_char)
								{
									current_number_of_mills++;
									cout << '\n' << "  PPP CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('q');
								}
								break;
			case 'Q': if(current_board[19] == player_char && current_board[22] == player_char)
								{
									current_number_of_mills++;
									cout << '\n' << "  QQQ CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('w');
								}
								break;
			case 'S': if((current_board[19] == player_char && current_board[20] == player_char))
								{
									current_number_of_mills++;
									cout << '\n' << "  SSS CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('t');
								}
								break;
			case 'V': if(current_board[22] == player_char && current_board[23] == player_char)
								{
									current_number_of_mills++;
									cout << '\n' << "  VVV CONGRATS! MILL DETECTED !!!!" << '\n';
									current_mills_identifiers.insert('x');
								}
								break;

		}
	}

	//search new mills
	for(set<char>::iterator it = player_future_positions.begin(); it != player_future_positions.end(); ++it) {
		switch(*it) {
			case 'A': if(future_board[1] == player_char && future_board[2] == player_char)
								{
									future_mills_identifiers.insert('b');
									future_number_of_mills++;
									cout << "\n AAA111 \n";
								}
								if(future_board[9] == player_char && future_board[21] == player_char)
								{
									future_mills_identifiers.insert('j');
									future_number_of_mills++;
									cout << "\n AAA222 \n";
								}								break;
			case 'B': if(future_board[4] == player_char && future_board[7] == player_char)
								{
									future_mills_identifiers.insert('e');
									future_number_of_mills++;
									cout << "\n BBB \n";
								}
								break;
			case 'C': if((future_board[14] == player_char && future_board[23] == player_char))
								{
									future_mills_identifiers.insert('o');
									future_number_of_mills++;
									cout << "\n CCC \n";
								}
								break;
			case 'D': if(future_board[10] == player_char && future_board[18] == player_char)
								{
									future_mills_identifiers.insert('s');
									future_number_of_mills++;
									cout << "\n DDD22222 \n";
								}
								if(future_board[4] == player_char && future_board[5] == player_char)
								{
									future_mills_identifiers.insert('f');
									future_number_of_mills++;
									cout << "\n DDD \n";
								}
								break;
			case 'F': if(future_board[13] == player_char && future_board[20] == player_char)
								{
									future_mills_identifiers.insert('u');
									future_number_of_mills++;
									cout << "\n FFF \n";
								}
								break;
			case 'G': if(future_board[7] == player_char && future_board[8] == player_char)
								{
									future_mills_identifiers.insert('h');
									future_number_of_mills++;
									cout << "\n G22222 \n";
								}
								if(future_board[11] == player_char && future_board[15] == player_char)
								{
									future_mills_identifiers.insert('l');
									future_number_of_mills++;
									cout << "\n GGG \n";
								}
								break;
			case 'I': if(future_board[12] == player_char && future_board[17] == player_char)
								{
									future_mills_identifiers.insert('m');
									future_number_of_mills++;
									cout << "\n III \n";
								}
								break;
			case 'J': if(future_board[10] == player_char && future_board[11] == player_char)
								{
									future_mills_identifiers.insert('k');
									future_number_of_mills++;
									cout << "\n JJJ \n";
								}
								break;
			case 'M': if(future_board[13] == player_char && future_board[14] == player_char)
								{
									future_mills_identifiers.insert('n');
									future_number_of_mills++;
									cout << "\n MMM \n";
								}
								break;
			case 'P': if(future_board[16] == player_char && future_board[17] == player_char)
								{
									future_mills_identifiers.insert('q');
									future_number_of_mills++;
									cout << "\n PPP \n";
								}
								break;
			case 'Q': if(future_board[19] == player_char && future_board[22] == player_char)
								{
									future_mills_identifiers.insert('w');
									future_number_of_mills++;
									cout << "\n QQQ \n";
								}
								break;
			case 'S': if(future_board[19] == player_char && future_board[20] == player_char)
								{
									future_mills_identifiers.insert('t');
									future_number_of_mills++;
									cout << "\n SSS \n";
								}
								break;
			case 'V': if(future_board[22] == player_char && future_board[23] == player_char)
								{
									future_mills_identifiers.insert('x');
									future_number_of_mills++;
									cout << "\n VVV \n";
								}
								break;
		}
	}


	//conditions that decide wheter a new mill will be created or not
	/*if(future_number_of_mills > current_number_of_mills) {
		made_new_mill = true;
	}*/
	for(set<char>::iterator it = future_mills_identifiers.begin(); it != future_mills_identifiers.end(); ++it){
		if(!(current_mills_identifiers.find(*it) != current_mills_identifiers.end())){
			cout << '\n' << "Yuhuuuuuuuuuuuuuu u have correctly detected the creation of a new mill! Have ur self a beer!" << '\n';
			made_new_mill = true;
		} else {
			cout << "\n BUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU" << "\n";
		}
	}
	//debuging-print
	/*cout << "\n" << "current number of mills = " << current_number_of_mills;
	cout << "\n" << " future number of mills = " << future_number_of_mills << "\n";*/

	//debugging-print
	cout << "\n current_mills_identifiers = ";
	for(set<char>::iterator it = current_mills_identifiers.begin(); it != current_mills_identifiers.end(); ++it){
		cout << *it << ',';
	}
	cout << "\n";
	cout << "\n future_mills_identifiers = ";
	for(set<char>::iterator it = future_mills_identifiers.begin(); it != future_mills_identifiers.end(); ++it){
		cout << *it << ',';
	}
	cout << "\n";


	return made_new_mill;
}

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

/* returns true if the total number of pieces of the given player is 3 and
they are all on board. false otherwise */
static bool hasPlayerOnly3Pieces(unsigned player, int number_of_unplaced_pieces, char board[24]) {
	int number_of_players_pieces_on_the_board = piecesOnTheBoard(player, board);

	if(number_of_unplaced_pieces == 0 && number_of_players_pieces_on_the_board == 3) {
		return true;
	}
	return false;
}

/* given the map of a board(keys = nodes, values = edges) and which nodes are
not occupied, this function returns every possible move the player can make*/
static map<char, set<char>> getPossibleMoves(map<char, set<char>> all_possibilities, set<char> free_spaces, bool is_free_to_move) {
	map<char, set<char>> possible_moves = all_possibilities;

	if(is_free_to_move) {
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

	possible_moves = all_possibilities;

	//debugging-loop
	/*cout << "\nreturned map: \n";
	for(map<char,set<char>>::iterator entry = possible_moves.begin(); entry != possible_moves.end(); ++entry) {
		cout << entry->first << " --> (";
		for(set<char>::iterator it = entry->second.begin(); it != entry->second.end(); ++it) {
			cout << *it << ',';
		}
		cout << ")\n";
	}*/



	return possible_moves;
}

static char pickRandomPiece(set<char> player_positions) {
	int max_random_number = player_positions.size();
	char randomPiece = *next(player_positions.begin(), (rand() % max_random_number));
	return randomPiece;
}

//TODO: this function is very similar to the one above... study a way to unify them.
static char chooseRandomPosition(set<char> free_spaces) {
	int max_random_number = free_spaces.size();
	char randomPosition = *next(free_spaces.begin(), (rand() % max_random_number));
	return randomPosition;
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

	srand (time(NULL));

	while (1) {
		/**Game's state variables*/
		unsigned current_player;
		unsigned unplaced_pieces[2];
		char board[24];
		char piece_move, piece_put, piece_kill;
		char newline;
		int matches;

		set<char> possible_moves_set;

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


	  bool is_free_to_move = hasPlayerOnly3Pieces(current_player, unplaced_pieces[current_player], board);

		/* Unless we have unplaced pieces, ask which piece to move. */
		if (unplaced_pieces[current_player]) {
			piece_move = ' ';
		} else {
			printf("  Which piece do you want to move:    ");
			fflush(stdout);

			newline = '\n';
			piece_move = pickRandomPiece(getPlayerPositions(current_player, board));


			possible_moves_set = getPossibleMoves(all_possibilities, getFreeSpaces(board), is_free_to_move).at(piece_move);

			/* if the size of the set is zero, this means that there are no movements
			available for the chosen piece_move.so we need to choose another one */
			while(possible_moves_set.size() == 0) {
				piece_move = pickRandomPiece(getPlayerPositions(current_player, board));
				possible_moves_set = getPossibleMoves(all_possibilities, getFreeSpaces(board), is_free_to_move).at(piece_move);
			}
			cout << piece_move << '\n';

		}

		/* Ask where to place the piece. */
		printf("  Where do you want to put the piece: ");
		fflush(stdout);

		/* decide wheter the player is placing a piece into the game,
		or just moving a piece which was already on the board. this is important,
		because when placing a new piece, the destination can be any empty space,
		and when moving an existing piece, the destination is restricted */
		if(unplaced_pieces[current_player]) {
			piece_put = chooseRandomPosition(getFreeSpaces(board));
		} else {
			piece_put = chooseRandomPosition(possible_moves_set);
		}
		cout << piece_put << "\n";
		newline = '\n';

		millsOnTheBoard(getPlayerPositions(current_player, board), board, piece_move, piece_put, current_player);
		//millsOnTheBoard(getPlayerPositions(current_player, board), board, current_player);



		/* Remove a piece from your opponent? */
		printf("You can now remove a piece from your opponent.\n");
		printf("  Which piece do you want to remove:  ");
		fflush(stdout);
		matches = fscanf(stdin, "%c", &piece_kill);
		if (piece_kill != '\n')
			matches = fscanf(stdin, "%c", &newline);
		if (matches != 1) break;
		printf("\n");

		fprintf(move_output, "%c%c%c\n", piece_move, piece_put, piece_kill);
		fflush(move_output);
	}

	fclose(state_input);
	fclose(move_output);

	return 1;
}
