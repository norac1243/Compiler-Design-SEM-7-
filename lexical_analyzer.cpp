#include <iostream>
#include <conio.h>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;
string sym_table[100][3];
int m = 0; // number of rows

// 2nd column of the sym_table is the type in the symbol table.
// op -> operator
// id -> identifier
// int -> int (handles negative???)
// float -> float
// keyword -> keyword

void feed_in_table(string str, int count, string sym_type)
{
	int index, flag_in_tab = 0;
	for (int i = 0; i < m; i++)
	{
		if (str == sym_table[i][0])
		{
			flag_in_tab = 1;
			index = i;
			break;
		}
		else
			flag_in_tab = 0;
	}
	if (flag_in_tab == 0)
	{
		sym_table[m][0] = str;
		sym_table[m][1] = to_string(count);
		sym_table[m][2] = sym_type;
		index = m;
		m++;
	}
	if (sym_type == "keyword")
		cout << sym_table[index][2] << sym_table[index][0] << ">";
	if (sym_type == "op" || sym_type == "int")
		cout << "<" << sym_table[index][0] << ">";
	if (sym_type == "id")
		cout << "<id" << sym_table[index][1] << "," << sym_table[index][0] << ">";

	// print_token(index);
}

int is_operator_func(char input)
{
	char operator_arr[20] = {'+', '-', '/', '*', '=', '>', '<'};
	int flag = 0;
	for (int j = 0; j < 5; j++)
	{
		if (input == operator_arr[j]) // checks for operator
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

int is_keyword_func(string input)
{
	string keyword_arr[900] = {"if", "else", "else if", "int", "float", "double"};
	int flag = 0;
	for (int j = 0; j < 5; j++)
	{
		if (input == keyword_arr[j]) // checks for operator
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

int main()
{
	string string_input, check_string, string_passed;
	int op_count = 1, id_count = 1, next;
	// is_op = 0, is_alphabet = 0,
	cout << setw(15) << "LEXICAL ANALYSER FOR" << endl
		 << "-------------------  C LANGUAGE -------------------" << endl
		 << "enter expression:" << endl;
	getline(cin, string_input);
	int n = string_input.length();
	for (int i = 0; i < n; i++)
	{
		if (is_operator_func(string_input[i]) == 1) // operator
		{
			string_passed = string_input[i];
			// check if increment or decrement operator
			next = i + 1;
			if (string_input[next] == string_input[i]) // is increment or decrement or double equal for checking stuff in an if loop
			{
				string_passed += string_input[next];
				i++; // skips string_input[next]
			}
			feed_in_table(string_passed, op_count, "op");
			// cout << string_passed << " -> op" << op_count << endl;
			op_count++;
		}
		else if (isalpha(string_input[i])) // an alp
		{
			string_passed = "";
			int next_is_alphabet = 0;
			int k = 0;
			do
			{
				string_passed += string_input[i];
				k++;
				next = i + 1;
				if (isalpha(string_input[next]))
				{
					next_is_alphabet = 1;
					i++;
				}
				else
					next_is_alphabet = 0;
			} while (next_is_alphabet == 1);
			if (is_keyword_func(string_passed) == 1)
				feed_in_table(string_passed, id_count, "keyword");
			else
				feed_in_table(string_passed, id_count, "id");
			// cout << " -> id" << id_count << endl;
			id_count++;
		}
		else if (string_input[i] == ' ') //
		{
			continue;
		}
	}
	for (int i = 0; i < m; i++)
	{
		cout << sym_table[i][0] << " | count" << sym_table[i][1] << " | " << sym_table[i][2] << endl;
	}
	_getch();
	return 0;
}
