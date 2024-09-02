#include<iostream>
#include<conio.h>
#include<string>
#include<cctype>
#include<iomanip>
using namespace std;
char operator_arr[20] = { '+', '-', '/','*', '=', '>', '<'};
string sym_table[100][3],keyword_arr[900] = {"if", "else", "else if", "int", "float", "double" };
int m = 1, next_in_table= 0; //number of rows 

// 2nd column of the sym_table is the type in the symbol table.
// op -> operator
// id -> identifier 
// int -> int (handles negative???)
// float -> float 
// keyword -> keyword

void print_token(int index)
{
	//called at every term in instruction.	
}


void feed_in_table(string str, int count, string sym_type)
{
	int index, flag_in_tab = 0;
	for (int i = 0; i < m; i++)
	{
		if (str != sym_table[i][0])
			flag_in_tab = 0;
		else
		{
			flag_in_tab = 1;
			index = i;
			break;
		}
	}
	if (flag_in_tab == 0)
	{
		sym_table[next_in_table][0] = str;
		sym_table[next_in_table][1] = to_string(count);
		sym_table[next_in_table][2] = sym_type;
		index = next_in_table;
	}
	if (sym_type == "keyword")
		cout << "<keyword," << sym_table[index][0] << ">" ;
	else if (sym_type == "operator")
		cout << "<" << sym_table[index][0] << ">";
	else if (sym_type == "identifier")
		cout << "<id" << sym_table[index][1] <<","<< ">";
	print_token(index);
}


int is_operator_func(char input)
{
	int flag = 0;
	for (int j = 0; j < 5; j++)
	{
		if (input == operator_arr[j]) //checks for operator 
		{
			flag = 1;
		}
	}
	return flag;
}


int check_if_keyword()
{

}

int main()
{
	string string_input, check_string;
	int is_op = 0, is_alphabet = 0,op_count = 1, id_count = 1, next;
	cout << setw(15) << "LEXICAL ANALYSER FOR" << "-------------------  C LANGUAGE -------------------";
	cin >> string_input;
	int n = string_input.length();
	for (int i = 0; i < n; i++)
	{
		if (is_operator_func(string_input[i]) == 1)//operator
		{
			//check if increment or decrement operator
			next = i + 1;
			if (string_input[next] == string_input[i]) // is increment or decrement 
			{
				cout << string_input[i] << string_input[next] << " -> op" << op_count<<endl;
				i++; //skips string_input[next] 
			}
			else 
			{
				cout << string_input[i] << " -> op" << op_count<< endl;
			}
			op_count++;
		}
		else if (isalpha(string_input[i]))//ain't an operator
		{
				int next_is_alphabet = 0;
				int k = 0;
				do {
					cout << string_input[i];
					k++;
					next = i + 1;
					if (isalpha(string_input[next]))
					{
						next_is_alphabet = 1;
						i++; 
					}
					else
						next_is_alphabet = 0;
				} while (next_is_alphabet==1);

				cout << " -> id" << id_count <<endl;
				id_count++;
			}
			
		}

	_getch();
	return 0;
}
