#include<iostream>
#include <fstream>
#include<vector>
using namespace std;

const int Max = 999999999;//定义最大值

struct Dictionary
{
	string data;
	string code;
};
struct HuffmanNode	// 哈夫曼树结点的定义
{
	string data; // 待编码的符号		
	double weight;		// 符号出现的频率 
	int parent, lchild, rchild;	// 父结点、左、右孩子结点的位置
};


class HuffmanTree
{
private:
	vector<HuffmanNode> hufftree;	// 树中所有结点的存储空间
	vector<vector<int>> code; //存放code
	int leaf_num;						// 叶子结点数
	int size;                   //哈夫曼树的总大小
	void SelectSmall(int& least, int& less, int i)//选择一组数据中最小的和次小的数
	{
		int s1 = Max;
		int s2 = Max;
		least = less = 0;
		for (int j = 0; j < i; j++)
		{
			if (s1 > hufftree[j].weight && hufftree[j].parent == -1)
			{
				s2 = s1;
				least = less;
				s1 = hufftree[j].weight;
				less = j;

			}
			else if (s2 > hufftree[j].weight && hufftree[j].parent == -1)
			{
				s2 = hufftree[j].weight;
				least = j;
			}
		}
	}

public:
	HuffmanTree(vector<HuffmanNode>& leafs)//构造函数
	{
		leaf_num = leafs.size();
		size = 2 * leaf_num - 1;
		hufftree.resize(size);
		for (int i = 0; i < leaf_num; i++)	 // 初始化n个二叉树
		{
			hufftree[i].data = leafs[i].data;
			hufftree[i].weight = leafs[i].weight;
			hufftree[i].parent = hufftree[i].lchild = hufftree[i].rchild = -1;
		}
		for (int i = leaf_num; i < size; i++)
		{
			int least, less;				//最小、次小的根结点下标
			SelectSmall(least, less, i);	// 找到最小、次小的根结点下标,只能找根结点，叶子结点必须去掉
			//每次根结点都会变，传leafs是错的
			hufftree[least].parent = hufftree[less].parent = i;
			hufftree[i].parent = -1;
			hufftree[i].lchild = least;
			hufftree[i].rchild = less;
			hufftree[i].weight = hufftree[least].weight + hufftree[less].weight;
		}
	}
	bool File_out_code()//输出对应的编码文件
	{
		ofstream OutFile("Code_dictionary.txt", ios::out | ios::binary);
		if (!OutFile.is_open())
		{
			return 0;
		}
		for (int i = 0; i < leaf_num; i++)
		{
			OutFile << hufftree[i].data << " ";
			int s = code[i].size();
			for (int j = 0; j < s; j++)
			{
				OutFile << char(code[i][j] + '0');
			}
			OutFile << endl;
		}
		return 1;
	}

	vector<int>GetCode(int i)//huffman编码算法
	{
		vector<int> temp_code;		// 第i个符号的编码向量
		int p = i;				// p是当前结点的下标
		int parent = hufftree[i].parent;	// parent是当前结点的父结点的下标
		while (parent != -1)		// 只有根结点的parent域为-1
		{
			if (hufftree[parent].lchild == p)
				temp_code.insert(temp_code.begin(), 0);	// 在编码向量首部插入0
			else
				temp_code.insert(temp_code.begin(), 1);	// 在编码向量首部插入1
			p = parent;
			parent = hufftree[parent].parent;	// 沿父指针上溯
		}
		return temp_code;
	}
	void GetAllCode()
	{
		for (int i = 0; i < leaf_num; i++)
		{
			code.push_back(GetCode(i));
		}
	}

	void Decode(vector<int>& source, vector<string>& result)//huffman译码算法
	{
		//string target = "";		// 译码的目标：原信息符号串
		int root = hufftree.size() - 1;
		int p = root;
		for (unsigned int i = 0; i < source.size(); i++)
		{
			if (source[i] == 0)
			{
				p = hufftree[p].lchild;	// 逢0向左孩子下行
			}
			else
			{
				p = hufftree[p].rchild;	// 逢1向右孩子下行
			}
			if (hufftree[p].lchild == -1 && hufftree[p].rchild == -1)
			{
				//target = target + hufftree[p].data;
				result.push_back(hufftree[p].data);
				p = root;
			}
		}
	}
};
//整理权重


bool read_Huffman_weight(vector<HuffmanNode>& leafs)
{
	ifstream infile;//读取文件
	infile.open("All_word_weight.txt", ios::in);
	if (!infile.is_open())
	{
		return 0;
	}
	string buf1;
	int buf2;
	int i = 0;
	while (infile >> buf1, infile >> buf2)
	{
		HuffmanNode temp;
		temp.data = buf1;
		temp.weight = buf2;
		temp.lchild = temp.lchild = temp.rchild = -1;
		leafs.push_back(temp);
	}
	return 1;
}
//读取整理好的权重


bool creat_Dictionary(vector<Dictionary>&dictionary)
{
	ifstream infile;//读取文件
	infile.open("Code_dictionary.txt", ios::in);
	if (!infile.is_open())
	{
		return 0;
	}
	//第一种读取方法，
	string buf1;
	string buf2;
	int i = 0;
	while (infile >> buf1, infile >> buf2)
	{
		Dictionary temp;
		temp.data = buf1;
		temp.code = buf2;
		dictionary.push_back(temp);
	}
	return 1;
}
//创建字典


string find_s(vector<Dictionary> dictionary, string target)
{
	int size = dictionary.size();
	for (int i = 0; i < size; i++)
	{
		if (dictionary[i].data == target)
		{
			return dictionary[i].code;
		}
	}
	return "-1";
}
//比对压缩


bool zip(vector<Dictionary> dictionary)//压缩
{
	ifstream infile;
	infile.open("pear.txt", ios::in);
	ofstream oufile("1.txt", ios::out | ios::binary);
	if (!infile.is_open() && !oufile.is_open())
	{
		return 0;
	}
	string buf;
	while (infile >> buf)
	{
		string temp = find_s(dictionary, buf);
		oufile << temp ;
	}
	return 1;
}
// 压缩

int main()
{
	vector<Dictionary>dictionary;//字典；
	vector<HuffmanNode>leafs;
	if (!read_Huffman_weight(leafs))//读取最基本的权重
	{
		cout << "读取权重文件失败" << endl;
		return 0;
	}

	HuffmanTree mytree(leafs);
	mytree.GetAllCode();

	if (!mytree.File_out_code())//编码后整理出编码；
	{
		cout << "输出编码本失败" << endl;
		return 0;
	}

	if (!creat_Dictionary(dictionary))//编码后整理出编码；
	{
		cout << "创建字典失败" << endl;
		return 0;
	}	

	if (!zip(dictionary))//压缩文件
	{
		cout << "文件压缩失败" << endl;
		return 0;
	}
	
	/*
	
	int size = dictionary.size();

	for (int i = 0; i < size; i++)
	{
		cout << dictionary[i].data << " " << dictionary[i].code << endl;
	}
	
	*/

	return 0;
}

