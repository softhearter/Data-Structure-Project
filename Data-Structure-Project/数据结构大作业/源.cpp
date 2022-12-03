/**
 * 文档按照文件读取的方式写入,我自己暂时没办法独立写一个中文分词出来，目前只支持英文文档。
 * 倒排表通过multimap建立。
**/
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <sstream>
using namespace std;
//存储倒排列表信息包括:TF,pos



struct DocMes
{
    int TF = 0;      //词频
    string pos = "";     //在文档出现的位置
};
typedef map<string, map<int, DocMes>> IndexMap;  //定义multiMap类型通过单词找到对应的表 IndexMap[词][j] 代表词在id为j的文档的何处；
typedef map<int, DocMes> invertMap;//倒排列表通过int找到


string intToString(int a)
{
    string res;
    stringstream ss;
    ss << a;
    ss >> res;
    return res;
}



//索引建立，在与代码同文件夹的1.txt 2.txt 3.txt读入文档，分词，记录词语与词语对应倒排列表信息

void CreateIndex(IndexMap& index)
{
    string path[10] = { "apple.txt","cherry.txt","grape.txt","mangosteen.txt","orange.txt","peach.txt","pear.txt","pineapple.txt","pomelo.txt","watermelon.txt" };
    //读本地txt文档
    ifstream fileIn;
    for (int i = 0; i <= 9; i++)
    {
        string filepath = path[i];
        fileIn.open(filepath);
        string temp;
        int posNum = 0;
        while (fileIn >> temp)
        {
            posNum++;//记录位置
            //judge(temp);  //处理temp
            //i值为文档的编号
            index[temp][i].TF++;
            index[temp][i].pos += intToString(posNum) + " , ";
        }
        fileIn.close();
    }
}

//查询处理
void queryProcess(IndexMap& index)
{
    string query;
    cout << "Look up your words:" << endl;
    while (true)
    {
        cout << ">>";
        cin >> query;
        if (index.find(query) == index.end())
        {
            cout << "ERROR: Can't find " << query << " ! ,please check up your words" << endl;
            continue;
        }

        invertMap::iterator iter;//用迭代器读取每一个数据
        iter = index[query].begin();
        while (iter != index[query].end())
        {
            cout << iter->first << ".txt : Tf=" << iter->second.TF << " ; pos = < " << iter->second.pos << " >" << endl;
            iter++;
        }
    }
}

int main() {
    IndexMap invertIndex;
    cout << "Creating Indexs:######" << endl;
    CreateIndex(invertIndex);
    cout << "Creat Indexs successfully!" << endl;
    queryProcess(invertIndex);
    getchar();
    return 0;
}