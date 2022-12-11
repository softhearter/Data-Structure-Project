#include <iostream>
#include <string>
#include<math.h>
using namespace std;

#define Max 0x7FFFFF

class Graph
{
    int ver_num;
    double** adjMat;
    string* ver_name;
    string** path;//最短路径

public:
    Graph(int n, double m[10][10], string* name) //初始化
    {
        ver_num = n;
        ver_name = new string[ver_num];
        path = new string * [ver_num];
        adjMat = new double* [ver_num];
        for (int i = 0; i < ver_num; i++)
        {
            ver_name[i] = name[i];
            path[i] = new string[ver_num];
            adjMat[i] = new double[ver_num];
        }
        for (int i = 0; i < ver_num; i++)
        {
            for (int j = 0; j < ver_num; j++)
            {
                adjMat[i][j] = 1 / m[i][j];
                if (adjMat[i][j] == 0)adjMat[i][j] = Max;
                path[i][j] = "";
            }
        }
    }

    int getIndex(string a)
    {
        for (int i = 0; i < ver_num; i++)
            if (ver_name[i] == a)
                return i;
        return -1;
    }

    void Dijkstra(string start)
    {
        //初始化
        bool* isVisited = new bool[ver_num];  //是否处理过
        double* distance = new double[ver_num];    //到各顶点的最小路径值的数组
        for (int i = 0; i < ver_num; i++)
        {
            distance[i] = 0;
        }
        int start_index = getIndex(start);
        for (int i = 0; i < ver_num; i++)
        {
            path[start_index][i] = start + " ";
            isVisited[i] = false;
            distance[i] = adjMat[start_index][i];  //开始为每个点到每个点的路径值
        }
        distance[start_index] = 0;
        isVisited[start_index] = true;
        //遍历
        for (int i = 0; i < ver_num - 1; i++)
        {
            double min = Max;
            int index = -1;
            for (int j = 0; j < ver_num; j++)//找最短路径的节点
            {
                if (isVisited[j] == false && min > distance[j])
                {
                    index = j;
                    min = distance[j];
                }
            }
            if (index != -1)//找到了
            {
                isVisited[index] = true;
                path[start_index][index] += ver_name[index] + " ";//加入最短路径
                for (int k = 0; k < ver_num; k++)
                {
                    if (isVisited[k] == false && min + adjMat[index][k] < distance[k])//更新其余节点最短路径
                    {
                        distance[k] = min + adjMat[index][k];
                        path[start_index][k] = path[start_index][index];
                    }
                }
            }
        }
        //整理赋值
        for (int i = 1; i < ver_num; i++)
        {
            if (distance[i] >= Max)
                continue;
            adjMat[start_index][i] = distance[i];
        }
    }
    void duicheng()//对矩阵进行对称处理
    {
        for (int i = 0; i < ver_num; i++)
        {
            for (int j = i; j < ver_num; j++)
            {
                adjMat[j][i] = adjMat[i][j];
            }
        }
    }

    void print()//输出最短路径值矩阵和最短路径
    {
        duicheng();
        adjMat[0][0] = 0;
        for (int i = 0; i < ver_num; i++)
        {
            for (int j = 0; j < ver_num; j++)
            {
                cout << adjMat[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
        for (int i = 0; i < ver_num; i++)
        {
            int index = getIndex(ver_name[i]);
            cout << ver_name[i] << ": ";
            for (int j = 0; j < ver_num; j++)
            {
                cout << "-->" << ver_name[j] << "=[ ";
                cout << path[index][j] << "]";
            }
            cout << endl;
        }
    }
};

int main()
{
    double matrix[10][10] =    //概率矩阵
    {
        {1.0000,0.8530,0.8636,0.1771,0.2546,0.1262,0.2162,0.0488,0.2061,0.1165},
        {0.8530,1.0000,0.2819,0.4287,0.3330,0.3598,0.8237,0.7063,0.9565,0.4772},
        {0.8636,0.2819,1.0000,0.0429,0.8887,0.0297,0.5160,0.7141,0.7820,0.9492},
        {0.1771,0.4287,0.0429,1.0000,0.4003,0.0611,0.7951,0.2877,0.2106,0.5884},
        {0.2546,0.3330,0.8887,0.4003,1.0000,0.9987,0.0640,0.5897,0.8763,0.6273},
        {0.1262,0.3598,0.0297,0.0611,0.9987,1.0000,0.9034,0.9996,0.2579,0.2076},
        {0.2162,0.8237,0.5160,0.7951,0.0640,0.9034,1.0000,0.3385,0.2499,0.6091},
        {0.0488,0.7063,0.7141,0.2877,0.5897,0.9996,0.3385,1.0000,0.4253,0.8842},
        {0.2061,0.9565,0.7820,0.2106,0.8763,0.2579,0.2499,0.4253,1.0000,0.0953},
        {0.1165,0.4772,0.9492,0.5884,0.6273,0.2076,0.6091,0.8842,0.0953,1.0000}
    };
    string name[10] =  //网页
    {
        "1","2","3","4","5","6","7","8","9","10"
    };
    int n = 10;
    Graph MyGraph(n, matrix, name);
    for (int i = 0; i < 10; i++)
        MyGraph.Dijkstra(name[i]);
    MyGraph.print();
    return 0;
}