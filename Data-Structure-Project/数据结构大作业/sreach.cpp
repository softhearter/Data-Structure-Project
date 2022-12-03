#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

struct Files//文件名和id
{
	string file_name;
	int file_id;
};

bool creat_files(vector<Files>& myfile)//给文件命名和定义id
{
	string name[10] = { "apple.txt","cherry.txt","grape.txt","mangosteen.txt","orange.txt","peach.txt","pear.txt","pineapple.txt","pomelo.txt","watermelon.txt" };
	for (int i = 0; i < 10; i++)
	{
		Files temp;
		temp.file_id = i;
		temp.file_name = name[i];
		myfile.push_back(temp);
	}
	if (myfile.size() != 10)
	{
		cout << "文件命名和命名id失败" << endl;
		return 0;
	}
	cout << "文件命名和命名id成功" << endl;
	return 1;
}

bool creat_Dictionary(vector<Files> myfile,vector<string>&All_Flie_Dictionary)
{
	ifstream infile;
	for (int i = 0; i < 10; i++)
	{
		infile.open(myfile[i].file_name);
		if (!infile.is_open())
		{
			cout << myfile[i].file_name << "文件打开失败" << endl;
			return 0;
		}
		string ch;
		while (infile>>ch)
		{
			int size_all = All_Flie_Dictionary.size();
			int flag_all = 0;
			for (int j = 0; j < size_all; j++)
			{
				if (All_Flie_Dictionary[j] == ch)
				{
					flag_all = 1;
					break;
				}
			}
			if (flag_all == 0)
			{
				All_Flie_Dictionary.push_back(ch);
			}
		}
		infile.close();
	}
	cout << "字典创建成功" << endl;
	return 1;
}



int main()
{
	vector<Files>myfile;//文件的命名和id；
	creat_files(myfile);//文件的命名和id；

	vector<string>All_Flie_Dictionary;//创建所有文档的字典
	creat_Dictionary(myfile, All_Flie_Dictionary);//创建字典

	int size = All_Flie_Dictionary.size();
	cout << "所有的字典" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << All_Flie_Dictionary[i]<< endl;
	}
}