#include<iostream>
#include<fstream>
using namespace std;
void display_instruction();
char** input_board(ifstream& fin1, char** board);
void boardDisplay(char** board);
void user_name(char user[], const int size);
void user_w(char user_word[], const int size);
int word_size(char user_word[], const int size);
void board_display_in_pause(char** board);
bool check_word_in_dic(char user_word[]);
bool compare_array(char user_word[], char* d_word);
int length(char* d_word);
int Row_Forward(char**& board, char user_word[], int user_word_length);
int Row_Backward(char**& board, char user_word[], int user_word_length);
int Column_Forward(char**& board, char user_word[], int user_word_length);
int Column_Backward(char**& board, char user_word[], int user_word_length);
int Diognal_Forward(char**& board, char user_word[], int user_word_length);
int Diognal_Backward(char**& board, char user_word[], int user_word_length);
int Diognal_Forward_Reverse(char**& board, char user_word[], int user_word_length);
int Diognal_Backward_Reverse(char**& board, char user_word[], int user_word_length);
int main()
{
	cout << "-----------------------------------------------WORD SEARCH PUZZLE------------------------------------------------------" << endl;

	display_instruction();
	char input = 0;
	const int size = 30;
	char user[size] = { '\0' };
	char user_word[size] = { '\0' };
	char level;
	char choice;
	do
	{

		do
		{
			cout << "Enter Your Choice:" << endl;
			cin >> choice;
			if (choice != 'n' && choice != 'p' && choice != 'r' && choice != 'L' && choice != 'h' && choice != 'e')
			{
				cout << "Please Enter Choice from Given Menu." << endl;
			}
			else
			{
				break;
			}
		} while (1);
		//	cin.ignore();

		int score = 0;
		int lives = 3;
		do
		{
			//New Game
			if (choice == 'n')
			{
				char** board = NULL;
				cin.ignore();
				user_name(user, size);
				cout << endl;
				ifstream fin("board.txt");
				board = input_board(fin, board);
				cout << "Board:" << endl;
				boardDisplay(board);
				cout << endl;
				user_w(user_word, size);
				cout << endl;
				int user_word_length = 0;
				//user enter word length
				user_word_length = word_size(user_word, size);
				//cout << "Lenght is:" << user_word_length;
				system("cls");
				cout << "Do You want To Pause Game or Continue?" << endl;
				cout << "Press p for pause." << endl;
				cout << "Press c for Continue." << endl;
				cin >> choice;
				if (choice == 'p')
				{
					//board Display
					board_display_in_pause(board);
					//Taking Option from user
					cout << "Do you Want To Exit Or Resume Game?" << endl;
					cout << "Press r to Resume Game." << endl;
					cout << "Press e For Exit." << endl;
					cin >> choice;
					if (choice == 'e')
					{
						cout << "------------------------------------Bye Bye------------------------------------------------------" << endl;
						cout << "------------------------------------Thanks for playing-------------------------------------------";
						break;
					}
					else
					{
						cin.ignore();
						cout << endl;
						cout << "Board:" << endl;
						boardDisplay(board);
						cout << endl;
						user_w(user_word, size);
						cout << endl;
						if (!(check_word_in_dic(user_word)))
						{
							//if word not found break;
							cout << "-----------------------------Word Not Found!----------------------------------------" << endl;
							break;
						}
						else
						{
							int lives = 3;
							bool flag = 0;
							//after finding word we have to ask for level of finding word
							cout << "Word Founded SuccessFully in dictionary" << endl;
							cout << "Now Press L for Level." << endl;
							cin >> level;
							cout << "\n\t At Start:" << endl;
							cout << "\n\t Score = " << score << "\t Lives = " << lives << endl;
							cout << "Press e for easy mode" << endl;
							cout << "Press i for intermediate mode" << endl;
							cout << "Press h for Hard mode" << endl;
							cin >> choice;
							//now according to choice we find word in that positioning
							//work of finding word in position and lives and score work
							//Now check on board
							if (choice == 'e')
							{
								int flag = 0;
								flag = Row_Forward(board, user_word, user_word_length);
								if (flag != 1)
								{
									flag = Column_Forward(board, user_word, user_word_length);
								}
								if (flag != 1)
								{
									cout << "Word Not found in Dictionary!" << endl;
									lives--;
								}
								if (flag == 1)
								{
									score = score + 10;
								}
							}
							else if (choice == 'i')
							{
								int Flag = 0;
								Flag = Row_Forward(board, user_word, user_word_length);
								if (Flag != 1)
								{
									Flag = Row_Backward(board, user_word, user_word_length);
								}
								if (Flag != 1)
								{
									Flag = Column_Forward(board, user_word, user_word_length);
								}
								if (Flag != 1)
								{
									Flag = Column_Backward(board, user_word, user_word_length);
								}
								if (Flag != 1)
								{
									cout << "Word Not Found on Board\n";
									lives--;
								}
								if (Flag == 1)
								{
									score = score + 10;
								}
							}
							else if (choice == 'h')
							{
								int Flag = 0;
								Flag = Row_Forward(board, user_word, user_word_length);
									if (Flag != 1)
									{
										Flag = Row_Backward(board, user_word, user_word_length);
									}
									if (Flag != 1)
									{
										Flag = Column_Forward(board, user_word, user_word_length);
									}
									if (Flag != 1)
									{
										Flag = Column_Backward(board, user_word, user_word_length);
									}
								if (Flag != 1)
								{
									Flag = Diognal_Forward(board, user_word, user_word_length);
								}
								if (Flag != 1)
								{
									Flag = Diognal_Backward(board, user_word, user_word_length);
								}
								if (Flag != 1)
								{
									Flag = Diognal_Forward_Reverse(board, user_word, user_word_length);
								}
								if (Flag != 1)
								{
									Flag = Diognal_Backward_Reverse(board, user_word, user_word_length);
								}
								if (Flag != 1)
								{
									cout << "Word Not Found on Board\n";
									lives--;
								}
								if (Flag == 1)
								{
									score = score + 10;
								}
							}
							if (lives == 0)
							{
								break;
							}
							//fin.close();
						}
						cout << "\n\t Score = " << score << "\t Lives = " << lives << endl;
						ofstream fout("highrecord.txt");
						fout << "High Record is:" << score;
					}
				}
				//If he dont want to pause game then we direct check word in dictionary and find word in board
				else
				{
					if (!(check_word_in_dic(user_word)))
					{
						cout << "----------------------------------Word Not Found!--------------------------------" << endl;
						break;
					}
					else
					{
						//int score = 0;
						//int lives = 3;
						bool flag = 0;
						cout << "Word Founded SuccessFully in dictionary" << endl;
						cout << " Now Press L for Level." << endl;
						cin >> level;
						cout << "\n\t At Start:" << endl;
						cout << "\n\t Score = " << score << "\t Lives = " << lives << endl;
						cout << "Press e for easy mode" << endl;
						cout << "Press i for intermediate mode" << endl;
						cout << "Press h for Hard mode" << endl;
						cin >> choice;
						//now according to choice we find word in that positioning
						//work of finding word in position and lives and score work
						if (choice == 'e')
						{
							int flag = 0;
							flag = Row_Forward(board, user_word, user_word_length);
							if (flag != 1)
							{
								flag = Column_Forward(board, user_word, user_word_length);
							}
							if (flag != 1)
							{
								cout << "Word Not found in Dictionary!" << endl;
								lives--;
							}
							if (flag != 1)
							{
								score = score + 10;
							}
						}
						else if (choice == 'i')
						{
							int Flag = 0;
							Flag = Row_Forward(board, user_word, user_word_length);
							if (Flag != 1)
							{
								Flag = Row_Backward(board, user_word, user_word_length);
							}
							if (Flag != 1)
							{
								Flag = Column_Forward(board, user_word, user_word_length);
							}
							if (Flag != 1)
							{
								Flag = Column_Backward(board, user_word, user_word_length);
							}
							if (Flag != 1)
							{
								cout << "Word Not Found on Board\n";
								lives--;
							}
							if (Flag == 1)
							{
								score = score + 10;
							}
						}
						else if (choice == 'h')
						{
							int Flag = 0;
							Flag = Row_Forward(board, user_word, user_word_length);
								if (Flag != 1)
								{
									Flag = Row_Backward(board, user_word, user_word_length);
								}
								if (Flag != 1)
								{
									Flag = Column_Forward(board, user_word, user_word_length);
								}
								if (Flag != 1)
								{
									Flag = Column_Backward(board, user_word, user_word_length);
							}
							if (Flag != 1)
							{
								Flag = Diognal_Forward(board, user_word, user_word_length);
							}
							if (Flag != 1)
							{
								Flag = Diognal_Backward(board, user_word, user_word_length);
							}
							if (Flag != 1)
							{
								Flag = Diognal_Forward_Reverse(board, user_word, user_word_length);
							}
							if (Flag != 1)
							{
								Flag = Diognal_Backward_Reverse(board, user_word, user_word_length);
							}
							if (Flag != 1)
							{
								cout << "Word Not Found on Board\n";
								lives--;
							}
							if (Flag == 1)
							{
								score = score + 10;
							}
						}
						if (lives == 0)
						{
							break;
						}
					}
					cout << "\n\t Score = " << score+10 << "\t Lives = " << lives << endl;
					ofstream fout("highrecord.txt");
					fout << "High Record is:" << score+10;
				}
			}
			cout << "Want to exit?    y/n" << endl;
			cin >> choice;
			if (choice=='y')
			{
				cout << "\t\n--------------------Thanks for playing-------------------------";
				break;
			}
		
		}while (1);
	

		//while work till user lives become 0 from 3
	} while (choice!='y');
}
void display_instruction()
{
	cout << "-----------------Main Menu------------------------\n";
	cout << "--------------Press n for new Game-----------------\n";
	cout << "--------------Press p for Pause Game-----------------\n";
	cout << "--------------Press r for resume Game--------------\n";
	cout << "--------------Press L for level Choices------------\n";
	cout << "--------------Press h for High score---------------\n";
	cout << "--------------Press e for exist--------------------\n";
}
char** input_board(ifstream& fin1, char** board)
{
	board = new char* [15];

	for (int i = 0; i < 15; i++)	//OUTER LOOP FOR ROWS
	{
		char* col = new char[15]{};	//WILL STORE DATA ROW BY ROW
		for (int j = 0; j < 15; j++)	//INNER LOOP FOR COLUMNS
		{
			fin1 >> col[j];
		}
		board[i] = col;
	}

	return board;
}
void boardDisplay(char** board)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}
void user_name(char user[], const int size)
{
	cout << "Enter Your Name:" << endl;
	cin.getline(user, size);
}
void user_w(char user_word[], const int size)
{
	cout << "Enter Word:" << endl;
	cin.getline(user_word, size);
}
int word_size(char user_word[], const int size)
{
	int l = 0;
	for (int i = 0; user_word[i] != '\0'; i++)
	{
		l++;
	}
	return l;
}
void board_display_in_pause(char** board)
{
	//board display in pausegame.txt
	ofstream fout("pause.txt");
	for (int r = 0; r < 15; r++)
	{
		for (int c = 0; c < 15; c++)
		{
			fout <<" "<< board[r][c];
		}
		fout << endl;
	}
}
bool check_word_in_dic(char user_word[])
{
	ifstream fin2("dictionary.txt");
	char* d_word = new char[30];
	while (!fin2.eof())
	{
		fin2 >> d_word;
		if (compare_array(user_word,d_word))
		{
			return true;
		}
	}
	return false;
}
bool compare_array(char user_word[],char* d_word)
{
	if (length(user_word) != length(d_word))
	{
		return false;
	}
	else
	{
		for (int i = 0; d_word[i] != '\0'; i++)
		{
			if (d_word[i] != user_word[i])
			{
				return false;
			}
		}
	}
	return true;
}
int length(char* d_word)
{
	int l = 0;

	for (int i = 0; d_word[i] != '\0'; i++)
	{
		l++;
	}

	return l;
}
int Row_Forward(char** &board,char user_word[], int user_word_length)
{
	int s = 15;
	int col_start = 0, col_end = 0;
	int flag = 0;
	for (int row = 0; row < s; row++)
	{
		flag = 0;
		col_start = 0;
		for (int col = 0; col < s; col++)
		{
			if (user_word[0]==board[row][col])
			{
				flag = 0;
				col_start = col;
				col_end = col;
				for (int i = 0; i < user_word_length; i++)
				{
					if (user_word[i]==board[row][col_end++])
					{
						flag = 1;
					}
					else
					{
						flag = 0;
						break;
					}
				}
			}
			if (flag==1)
			{
				break;
			}
			else
			{
				col_start = col_start + 1;
			}
		}
		if (flag == 1)
		{
			//cout << "World found on index " << Row << " and " << cca;
			cout << endl << user_word<< " Word found on Row in Forward Direction \nStart From Row ";
			cout << row << " and Column " << col_start << "\nEnd on Row " << row << " and Column " << col_end-1 << endl;
			break;
		}
	}
	return flag;

}
int Row_Backward(char** &board, char user_word[], int user_word_length)
{
	int s = 15;
	int col_start = 0, col_end = 0;
	int flag = 0;
	for (int row = 0; row < s; row++)
	{
		flag = 0;
		col_start = 0;
		for (int col = 0; col < s; col++)
		{
			if (user_word[0] == board[row][col])
			{
				flag = 0;
				col_start = col;
				col_end = col;
				for (int i = 0; i < user_word_length; i++)
				{
					if (user_word[i] == board[row][col_end--])
					{
						flag == 1;
					}
					else
					{
						flag = 0;
						break;
					}
				}
			}
			if (flag == 1)
			{
				break;
			}
			else
			{
				col_start = col_start + 1;
			}
		}
		if (flag == 1)
		{
			//cout << "World found on index " << Row << " and " << cca;
			cout << endl << user_word << " Word found on Row in Backward Direction \nStart From Row ";
			cout << row << " and Column " << col_start << "\nEnd on Row " << row << " and Column " << col_end + 1 << endl;
			break;
		}
	}
	return flag;
}
int Column_Forward(char** &board,char user_word[], int user_word_length)
{
	int s = 15;
	int col_start = 0, row_end = 0;
	int flag = 0;
	for (int row = 0; row < s; row++)
	{
		flag = 0;
		col_start = 0;
		for (int col = 0; col < s; col++)
		{
			if (user_word[0] == board[row][col])
			{
				flag = 0;
				col_start = col;
				row_end= row;
				for (int i = 0; i < user_word_length; i++)
				{
					if (user_word[i] == board[row_end++][col])
					{
						flag == 1;
					}
					else
					{
						flag = 0;
						break;
					}
				}
			}
			if (flag == 1)
			{
				break;
			}
			else
			{
				col_start = col_start + 1;
			}
		}
		if (flag == 1)
		{
			cout << endl << user_word << " World Found on Column in Forward Direction \nStart From Row ";
			cout << row << " and Column " << col_start<< "\nEnd on Row " << row_end - 1 << " and Column " << col_start << endl;

			break;
		}
	}
	return flag;
}
int Column_Backward(char** &board, char user_word[], int user_word_length)
{
	int s = 15;
	int flag = 0;
	int end_row = 0, col_start= 0;
	for (int Row = 0; Row < s; Row++)
	{
		flag = 0;
		col_start = 0;
		for (int col = 0; col < s; col++)
		{
			if (user_word[0] == board[Row][col])
			{
				end_row = Row;
				col_start = col;
				flag = 0;
				for (int i = 0; i <user_word_length; i++)
				{
					if (user_word[i] == board[end_row--][col])
					{
						flag = 1;
					}
					else
					{
						flag = 0;
						break;
					}
				}
			}
			if (flag == 1)
			{
				break;
			}
			else
			{
				col = col + 1;
			}
		}
		if (flag == 1)
		{
			cout << endl << user_word << " World Found on Column in Backward Direction\nStart From Row ";
			cout << Row << " and Column " << col_start << "\nEndnd on Row " << end_row + 1 << " and Column " << col_start << endl;
			break;
		}

	}
	return flag;
}
int Diognal_Forward(char** &board, char user_word[], int user_word_length)
{
	int s = 15;
	int flag = 0;
	int end_row = 0, end_col = 0, Col_start = 0;
	for (int row = 0; row < s; row++)
	{
		flag = 0;
		end_col = 0;
		for (int col = 0; col < s; col++)
		{
			if (user_word[0] == board[row][col])
			{
				end_row = row;
				end_col = col;
				Col_start= col;
				flag = 0;
				for (int i = 0; i < user_word_length; i++)
				{
					if (user_word[i] == board[end_row++][end_col++])
					{
						flag = 1;
					}
					else
					{
						flag = 0;
						break;
					}
				}
			}
			if (flag == 1)
			{
				break;
			}
			else
			{
				end_col = end_col + 1;
			}
		}
		if (flag == 1)
		{
			cout << endl << user_word << " World Found Diognaly in Forward Direction\nStart From Row ";
			cout << row << " and Column " << Col_start << "\nEnd on Row " << end_row - 1 << " and Column " << end_col - 1 << endl;
			break;
		}
	}
	return flag;

}
int Diognal_Backward(char** &board, char user_word[], int user_word_length)
{
	int s = 15;
	int flag = 0;
	int end_row = 0, end_col = 0, col = 0;
	for (int row = 0; row < s; row++)
	{
		flag = 0;
		end_col = 0;
		for (int col = 0; col < s; col++)
		{
			if (user_word[0] == board[row][col])
			{
				end_row = row;
				end_col = col;
				col = col;
				flag = 0;
				for (int i = 0; i < user_word_length; i++)
				{
					if (user_word[i] == board[end_row++][end_col--])
					{
						flag = 1;
					}
					else
					{
						flag = 0;
						break;
					}
				}
			}
			if (flag == 1)
			{
				break;
			}
			else
			{
				end_col = end_col + 1;
			}
		}
		if (flag == 1)
		{
			cout << endl << user_word << " World Found Diognaly in Forward Direction\nStart From Row ";
			cout << row << " and Column " << col << "\nEnd on Row " << end_row - 1 << " and Column " << end_col - 1 << endl;
			break;
		}
	}
	return flag;
}
int Diognal_Forward_Reverse(char** &board, char user_word[], int user_word_length)
{
	int s = 15;
	int flag = 0;
	int end_row = 0, end_col = 0, start_col = 0;
	for (int Row = 0; Row < s; Row++)
	{
		flag = 0;
		end_col = 0;
		for (int Col = 0; Col < s; Col++)
		{
			if (user_word[0] == board[Row][Col])
			{
				end_row = Row;
				end_col = Col;
				start_col = Col;
				flag = 0;
				for (int i = 0; i <s; i++)
				{
					if (user_word[i] == board[end_row--][end_col--])
					{
						flag = 1;
					}
					else
					{
						flag = 0;
						break;
					}
				}
			}
			if (flag == 1)
			{
				break;
			}
			else
			{
				end_col = end_col + 1;
			}
		}
		if (flag == 1)
		{
			cout << user_word << " World Found Reverse Diognaly in Forward Direction\nStart From Row ";
			cout << Row << " and Column " << start_col << "\nEnd on Row " << end_row + 1 << " and Column " << end_col + 1;
			break;
		}
	}
	return flag;
}
int Diognal_Backward_Reverse(char** &board, char user_word[], int user_word_length)
{
	int s = 15;
	int flag = 0;
	int end_row = 0, end_col = 0, start_col = 0;
	for (int Row = 0; Row < s; Row++)
	{
		flag = 0;
		end_col = 0;
		for (int Col = 0; Col < s; Col++)
		{
			if (user_word[0] == board[Row][Col])
			{
				end_row = Row;
				end_col = Col;
				start_col = Col;
				flag = 0;
				for (int i = 0; i < s; i++)
				{
					if (user_word[i] == board[end_row--][end_col--])
					{
						flag = 1;
					}
					else
					{
						flag = 0;
						break;
					}
				}
			}
			if (flag == 1)
			{
				break;
			}
			else
			{
				end_col = end_col + 1;
			}
		}
		if (flag == 1)
		{
			cout << user_word << " World Found Reverse Diognaly in Forward Direction\nStart From Row ";
			cout << Row << " and Column " << start_col << "\nEnd on Row " << end_row + 1 << " and Column " << end_col + 1;
			break;
		}
	}
	return flag;
}














