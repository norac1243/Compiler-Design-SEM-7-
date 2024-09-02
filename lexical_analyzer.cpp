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
		cout << "<" << sym_table[index][2] << "," << sym_table[index][0] << ">";
	if (sym_type == "op" || sym_type == "int")
		cout << "<" << sym_table[index][0] << ">";
	if (sym_type == "id")
		cout << "<id" << sym_table[index][1] << "," << sym_table[index][0] << ">";
	if (sym_table[index][0] == ")" || sym_table[index][0] == "}" || sym_table[index][0] == ";")
		cout << endl;
}

int is_operator_func(char input)
{
	char operator_arr[25] = {'+', '-', '/', '*', '=', '>', '<', '!', '&', '|', '^', ',', '.', ':', '"', '%', '~', '}', '{', '(', ')', ';'};
	for (char op : operator_arr)
	{
		if (input == op) // checks for operator
			return 1;
	}
	return 0;
}

int is_keyword_func(string input)
{
	string keyword_arr[900] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
							   "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
							   "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
							   "void", "volatile", "while", "alignas", "alignof", "and", "and_eq", "asm", "bitand", "bitor",
							   "class", "compl", "concept", "const_cast", "delete", "dynamic_cast", "explicit", "export",
							   "friend", "inline", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr",
							   "operator", "private", "protected", "public", "reinterpret_cast", "static_assert", "static_cast",
							   "template", "this", "thread_local", "throw", "try", "typeid", "typename", "using", "virtual",
							   "wchar_t", "xor", "xor_eq"};
	for (string key : keyword_arr)
	{
		if (input == key) // checks for operator
			return 1;
	}
	return 0;
}

int main()
{
	string string_input, check_string, string_passed, input_line;
	int op_count = 1, id_count = 1, keyword_count = 1, next;
	// is_op = 0, is_alphabet = 0,
	cout << setw(15) << "LEXICAL ANALYSER FOR" << endl
		 << "-------------------  C LANGUAGE -------------------" << endl
		 << "Enter Code, type 'EOF' to stop:" << endl;
	// getline(cin, string_input);
	while (getline(cin, input_line) && input_line != "EOF")
	{
		string_input += input_line + " ";
	}
	int n = string_input.length();

	cout << endl
		 << "LEXICAL ANALYSIS PHASE:" << endl;
	for (int i = 0; i < n; i++)
	{
		if (is_operator_func(string_input[i]) == 1) // operator
		{
			string_passed = string_input[i];
			next = i + 1;
			if (string_input[next] == string_input[i]) // is increment or decrement or double equal for checking stuff in an if loop
			{
				string_passed += string_input[next];
				i++; // skips string_input[next]
			}
			feed_in_table(string_passed, op_count, "op");
			op_count++;
		}
		else if (isalpha(string_input[i])) // an identifer or keyword
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
			{
				feed_in_table(string_passed, keyword_count, "keyword");
				keyword_count++;
			}
			else
			{
				feed_in_table(string_passed, id_count, "id");
				id_count++;
			}
		}
		else if (string_input[i] == ' ') // to handle whitespaces.
		{
			continue;
		}
	}
	cout << endl
		 << "SYMBOL TABLE: \n --------------------";
	for (int i = 0; i < m; i++)
	{
		cout << endl
			 << setw(10) << sym_table[i][0] << " | " << setw(10) << sym_table[i][2] << sym_table[i][1] << " | ";
	}
	_getch();
	return 0;
}
