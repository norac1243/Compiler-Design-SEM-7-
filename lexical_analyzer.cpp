#include<iostream>
#include<conio.h>
#include<string>
#include<cctype>
using namespace std;
char operator_arr[20] = { '+', '-', '/','*', '=' };
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

int main()
{
	string string_input, check_string;
	int is_op = 0, is_alphabet = 0,op_count = 1, id_count = 1, next;
	cin >> string_input;
	int n = string_input.length();
	for (int i = 0; i < n; i++)
	{
		is_op = is_operator_func(string_input[i]);
		if (is_op == 1)//operator
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
		if (is_op == 0)//ain't an operator
		{
			if (isalpha(string_input[i]))
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
			else //could be a digit 
			{

			}
		}
	}
	_getch();
	return 0;
}
