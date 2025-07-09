#include <iostream>
#include <cstdint>
#include <string>
#include <stack>
#include <cfloat>
using namespace std;

int32_t operator_precedence1 = 1;
int32_t operator_precedence2 = 2;
int32_t operator_precedence0 = 0;

int32_t priority_determination(int8_t data);
string infix_suffix(string str);
bool bracket_matching(string str);
string suffix_computation(string str);
string whitespace_checking(string str);
bool operator_judgment(int8_t data);
string parenthesis_operator_completion(string str);

bool bracket_matching(string str) {
	stack<int8_t> bracket;
	for (string::size_type i = 0; i < str.size(); i++) {
		if (str[i] == ')') {
			if (bracket.empty())
				return false;
			else 
				bracket.pop();
		}
		else if (str[i] == '(') 
			bracket.push(str[i]);
	}
	return bracket.empty();
}

string infix_suffix(string str) {
	stack<int8_t> precedence;
	string suffix_expression;
	for (string::size_type i = 0; i < str.size(); i++) {
		if (operator_judgment(str[i])) {
			if (precedence.empty()) {
				precedence.push(str[i]);
				suffix_expression += " ";
				continue;
			}
			while (priority_determination(precedence.top()) >= priority_determination(str[i])) {
				//cout << "while_suffix_expression:" << suffix_expression << endl;
				suffix_expression += precedence.top();
				//cout << "if_if_while_delete : " << precedence.top() << endl;
				precedence.pop();
				//cout << "while_if_suffix_expression:" << suffix_expression << endl;
				if (precedence.empty())
					break;
				if (precedence.top() == '(')
					break;
			}
			precedence.push(str[i]);
			suffix_expression += " ";
			//cout << precedence.top() << endl;
			continue;
		}
		if (str[i] == '(') 
			precedence.push(str[i]);
		if (str[i] == ')') {
			while (precedence.top() != '(') {
				suffix_expression += precedence.top();
				//cout << "if_delete : " << precedence.top() << endl;
				precedence.pop();
			}	
			precedence.pop();
		}
		if (str[i] == '(' || str[i] == ')')
			continue;
		suffix_expression += str[i];
	}
	//cout << precedence.size() << endl;
	int32_t num = precedence.size();
	for (int32_t i = 0; i < num; i++) {
		//cout << i << endl;
		//cout << precedence.top() << endl;
		suffix_expression += precedence.top();
		precedence.pop();
	}
	return suffix_expression;
}

string suffix_computation(string str) {
	for (string::size_type i = 1; i < str.size(); i++) {
		if (operator_judgment(str[i - 1]) && str[i] == ' ') 
			str.erase(i, 1);
			//cout << str << endl;
	}
	//cout << str << endl;;
	//return "";
	stack<double> data;
	string expression;
	for (string::size_type i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			if (-DBL_MAX > stod(expression) || stod(expression) > DBL_MAX)
				return "";
			data.push(stod(expression));
			expression = "";
			//cout << data.top() << endl;
			continue;
		}
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			//cout << "qqqqqqq" << endl;
			if (expression.empty() == false)
				if (-DBL_MAX < stod(expression) && stod(expression) < DBL_MAX)
					data.push(stod(expression));
				else
					return "";
			expression = "";
			//cout << data.top() << endl;
			double num1 = data.top();
			data.pop();
			double num2 = data.top();
			data.pop();

			if (-DBL_MAX > num1 + num2 || num1 + num1 > DBL_MAX)
				return "";
			else if (-DBL_MAX > num1 * num2 || num1 * num2 > DBL_MAX)
				return "";
			else if (-DBL_MAX > num2 - num1 || num2 - num1 > DBL_MAX)
				return "";

			if (str[i] == '+')
				data.push(num1 + num2);
			else if (str[i] == '*')
				data.push(num1 * num2);
			else if (str[i] == '-')
				data.push(num2 - num1);
			else if (str[i] == '/')
				if (num1 != 0)
					data.push(num2 / num1);
				else return "";
			continue;
		}
		expression += str[i];
	}
	if (data.size() != 1)
		return "";
	return to_string(data.top());
}

int32_t priority_determination(int8_t data) {
	if (data == '+' || data == '-')
		return operator_precedence1;
	if (data == '*' || data == '/')
		return operator_precedence2;
	if (data == '(' || data == ')')
		return operator_precedence0;
	return -1;
}

string computation(string str) {
	if (!bracket_matching(str)) {
		cout << "括号不对配喵!" << endl;
		return "";
	}
	str = parenthesis_operator_completion(str);

	str = whitespace_checking(str);
	//cout << infix_suffix(str) << endl;
	if (suffix_computation(infix_suffix(str)) == "")
		return "错误啦";
	return suffix_computation(infix_suffix(str));
}

string whitespace_checking(string str) {
	int32_t size_num = str.size();
	for (string::size_type i = 1; i < str.size(); i++) {
		if (str[i] == ' ')
			str.erase(i--, 1);
	}
	if (size_num != str.size()) 
		cout << "看来你输入的可能有点问题哦,我给你改改,给你看看" << endl << str << endl;
	return str;
}

bool operator_judgment(int8_t data) {
	if (data == '+' || data == '-' || data == '*' || data == '/')
		return true;
	return false;
}

string parenthesis_operator_completion(string str) {
	string new_str = str;
	int32_t bracket_pointer = 1;
	for (string::size_type i = 1; i < str.size(); i++,bracket_pointer++) {
		if (!isdigit(str[i - 1]) || !isdigit(str[i + 1]))
			continue;
		if (!operator_judgment(str[i - 1]) && str[i] == '(')
			new_str.insert(bracket_pointer++, "*");
		else if (!operator_judgment(str[i + 1]) && str[i] == ')')
			new_str.insert(++bracket_pointer, "*");
	}
	//cout << new_str << endl;
	return new_str;
}

int32_t main() {
	cout << "1退出哦" << endl;
	cout << "输入表达式!:" << endl;
	string expression;
	while (getline(cin,expression)) {
		if (expression.size() >= 250) {
			cout << "你这也长了罢!" << endl << "绝对不行!!!" << endl;
			continue;
		}

		if (expression == "1") {
			cout << "退出成功!" << endl;
			return 0;
		}
		string results = computation(expression);
		if (results == "")
			cout << "错误啦!";
		cout << results << endl;
	}
	return 0;
}