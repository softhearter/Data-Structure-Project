#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int main()
{
	vector<string> inputExpre;
	stack<string> result;		// 结果
	stack<string> symbol;       // 符号
	stack<string> tmp;          //过渡使用
	string temp;
	while (cin>>temp)
	{
		if (temp == "#")
		{
			break;
		}
		else
		{
			inputExpre.push_back(temp);
		}
	}

	int inputExpre_len = inputExpre.size();

	for (int i = 0; i < inputExpre_len; i++)
	{
		if (inputExpre[i] == "|" || inputExpre[i] == "&" || inputExpre[i] == "(")
		{
			symbol.push(inputExpre[i]);
		}
		else if (inputExpre[i] == ")")
		{
			while (!symbol.empty() && symbol.top() != "(")
			{
				tmp.push(symbol.top());
				symbol.pop();
			}
			symbol.pop();
		}
		else
		{
			tmp.push(inputExpre[i]);
		}
	}
	int size = symbol.size();
	for (int i = 0; i < size; i++)
	{
		tmp.push(symbol.top());
		symbol.pop();
	}

	size = tmp.size();

	for (int i = 0; i < size; i++)
	{
		result.push(tmp.top());
		tmp.pop();
	}

	size = tmp.size();
	for (int i = 0; i < size; i++)
	{
		result.push(tmp.top());
		tmp.pop();
	}
	
	size = result.size();
	for (int i = 0; i < size; i++)
	{
		cout << result.top() << " ";
		result.pop();
	}

	return 0;
}