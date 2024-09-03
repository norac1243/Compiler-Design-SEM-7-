#include <iostream>
#include <conio.h>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

string sym_table[100][3];
int m = 0, op_count = 1, id_count = 1, keyword_count = 1, lit_count = 1, relop_count = 1, delimiter_count = 1, next; // number of rows

void handleCount(string sym_type)
{
	int count;
	if (sym_type == "keyword")
		count = keyword_count++;
	else if (sym_type == "op")
		op_count++;
	else if (sym_type == "float" || sym_type == "int")
		lit_count++;
	else if (sym_type == "relop")
		relop_count++;
	else if (sym_type == "delimiter")
		delimiter_count++;
	else if (sym_type == "id")
		id_count++;
}
void feed_in_table(string str, string sym_type)
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
		handleCount(sym_table[m][2]);
	}
	if (sym_type == "keyword")
		cout << "<" << sym_table[index][2] << "," << sym_table[index][0] << ">";
	else if (sym_type == "op" || sym_type == "int" || sym_type == "float" || sym_type == "relop" || sym_type == "delimiter")
	{
		cout << "<" << sym_table[index][0] << ">";
		if (str == ";" || str == "}" || str == ")")
			cout << endl;
	}
	else if (sym_type == "id")
	{
		cout << "<id" << sym_table[index][1] << "," << sym_table[index][0] << ">";
	}
}

int is_operator_func(char input)
{
	char operator_arr[30] = { '+', '-', '/', '*', '=', '!', '&', '|', '^', '.', ':', '\"', '%', '~', '[', ']', '>','<',';',',','\'','"','(',')','{','}' };
	for (char op : operator_arr)
	{
		if (input == op) // checks for operator
			return 1;
	}
	return 0;
}
int is_relop_func(string input)
{
	string rel_operator_arr[30] = {"==", "!=", "<=", ">="};
	for (string relop : rel_operator_arr)
	{
		if (input == relop) // checks for relational operator
			return 1;
	}
	return 0;
}

int is_delimiter_func(string input)
{
	string delimiter_arr[30] = {"/*","*/","//" };
	for (string delimiter: delimiter_arr)
	{
		if (input == delimiter) // checks for operator
			return 1;
	}
	return 0;
}


int is_keyword_func(string input)
{
	string keyword_arr[900] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
		"enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
		"short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
		"void", "volatile", "while", "alignas", "alignof", "and", "and_eq", "asm", "bitand", "bitor",
		"class", "compl", "concept", "const_cast", "delete", "dynamic_cast", "explicit", "export",
		"friend", "inline", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr",
		"operator", "private", "protected", "public", "reinterpret_cast", "static_assert", "static_cast",
		"template", "this", "thread_local", "throw", "try", "typeid", "typename", "using", "virtual",
		"wchar_t", "xor", "xor_eq", "true", "false" };
	for (string key : keyword_arr)
	{
		if (input == key) // checks for operator
			return 1;
	}
	return 0;
}

bool is_integer(string str)
{
	for (char c : str)
	{
		if (!isdigit(c))
			return false;
	}
	return true;
}

bool is_float(const string &str)
{
	int dot_count = 0;
	for (char c : str)
	{
		if (c == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return false; // More than one dot is invalid
		}
		else if (!isdigit(c))
		{
			return false; // Invalid character for float
		}
	}
	return dot_count == 1; // Must have exactly one dot
}

int main()
{
	string string_input, check_string, string_passed, input_line,newstring;
	// is_op = 0, is_alphabet = 0,
	cout << setw(35) << "LEXICAL ANALYSER FOR" << endl
		<< "-------------------  C LANGUAGE -------------------" << endl
		<< "Enter Code, type 'EOF' to stop:" << endl
		<< "--------------------------------------------------------------------------------------------------" << endl;
	// getline(cin, string_input);
	while (getline(cin, input_line) && input_line != "EOF")
	{
		string_input += input_line + " ";
	}
	int n = string_input.length();

	cout << "--------------------------------------------------------------------------------------------------" << endl
		<< "LEXICAL ANALYSIS PHASE (TOKENS):" << endl
		<< endl;
	for (int i = 0; i < n; i++)
	{
		if (is_operator_func(string_input[i]) == 1) // operators and relational operator
		{
			string_passed = string_input[i];
			next = i + 1;
			int is_relop = 0, is_delimiter = 0;
			if (next < n && (string_input[next] == string_input[i]) &&
				(string_input[i] == '+' || string_input[i] == '-')) // is increment or decrement or double equal for checking stuff in an if loop
			{
				string_passed += string_input[next];
				i++; // skips string_input[next]
			}
			else if (next < n && (string_input[i] == '>' || string_input[i] == '<' || string_input[i] == '!' || string_input[i] == '='))
			{
				newstring = string_passed + string_input[next];
				if (is_relop_func(newstring))
				{
					i++;  string_passed = newstring;
				}
				is_relop = 1;

			}
			else if (next < n && (string_input[i] == ';' || string_input[i] == ',' || string_input[i] == '\'' || string_input[i] == '"' || string_input[i] == '(' || string_input[i] == ')' || string_input[i] == '{' || string_input[i] == '}'))
			{
				newstring = string_passed + string_input[next];
				if (is_delimiter_func(newstring))
				{
					i++;  string_passed = newstring;
				}
				is_delimiter = 1;
			}
			if (is_relop == 1)
			{
				feed_in_table(string_passed, "relop");
			}
			else if (is_delimiter == 1)
			{
				feed_in_table(string_passed, "delimiter");
			}
			else
			{
				feed_in_table(string_passed, "op");
			}
		}
		else if (isdigit(string_input[i])) // numbers or more specifically literals
		{
			string_passed = "";

			while (isdigit(string_input[i]) || string_input[i] == '.')
			{
				string_passed += string_input[i];
				i++;
			}
			i--;
			if (is_float(string_passed))
				feed_in_table(string_passed, lit_count, "float");
			else if (is_integer(string_passed))
				feed_in_table(string_passed, lit_count, "int");
			else
				cout << "<Invalid number literal: " << string_passed << ">";
			lit_count++;
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
	cout << "--------------------------------------------------------------------------------------------------" << endl
		<< "SYMBOL TABLE:" << endl
		<< "------------------------------------------" << endl
		<< setw(15) << "Name" << " | " << setw(22) << "Type" << " |" << endl
		<< "------------------------------------------";

	for (int i = 0; i < m; i++)
	{
		if (sym_table[i][2] == "int")
		{
			cout << endl
				<< setw(15) << sym_table[i][0] << " | " << setw(15) << "literal " << sym_table[i][1] << " (" << sym_table[i][2] << ")" << " |";
		}
		else if (sym_table[i][2] == "float")
		{
			{
				cout << endl
					<< setw(15) << sym_table[i][0] << " | " << setw(13) << "literal " << sym_table[i][1] << " (" << sym_table[i][2] << ")" << " |";
			}
		}
		else
		{
			cout << endl
				<< setw(15) << sym_table[i][0] << " | " << setw(20) << sym_table[i][2] << " " << sym_table[i][1] << " |";
		}
	}
	cout << endl
		<< "--------------------------------------------------------------------------------------------------" << endl;
	_getch();
	return 0;
}
