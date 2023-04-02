#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
void stringSplit(string str, const const char split,vector<string>& res)
{
	istringstream iss(str);	// 输入流
	string token;			// 接收缓冲区
	while (getline(iss, token, split))	// 以split为分隔符
	{
		res.push_back(token);
	}
}
