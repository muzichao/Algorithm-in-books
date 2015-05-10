#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

#define iMaxLength  100

/**
* MinimumPath 计算最短路径
* pathMatrix： 输入矩阵  输入
* row：        矩阵行数  输入
* col：        矩阵列数  输入
* return：     最短路径  输出
*/
int MinimumPath(vector<vector<int>> &pathMatrix, int row, int col)
{
	vector<vector<int>> minPath; // 保存最短路径表

	/*初始化第一行*/
	vector<int> firstPath(col, iMaxLength);
	firstPath[0] = 0;
	minPath.push_back(firstPath);

	for (int i = 1; i < row; i++)
	{
		vector<int> lastMinPath = minPath[i-1]; // 上一行的计算结果
		vector<int> currentMinPath; // 当前行将要计算的结果
		for (int j = 0; j < col; j++)
		{
			/*找到 i 行 j 列的最小值*/
			int currentMinData = iMaxLength;
			for (int k = 0; k < col; k++)
			{
				currentMinData = min(currentMinData, lastMinPath[k] + pathMatrix[j][k]);
			}
			currentMinPath.push_back(currentMinData);
		}
		minPath.push_back(currentMinPath);
	}
	return minPath[row-1][col-1];
}

/**
* ReadFile 从txt文件中读取数据矩阵
* pathMatrix：输出矩阵          输出
* fileName：  文件名的绝对路径  输入
* row：       矩阵行数          输入
* col：       矩阵列数          输入
*/
template<typename T> void ReadFile(vector<vector<T>> &pathMatrix, string fileName, int row, int col)
{
	fstream file;
	file.open(fileName, ios::in);

	/*逐个读入数据*/
	for (int i = 0; i < row; i++)
	{
		vector<T> oneRowData(col, 0);
		for (int j = 0; j < col; j++)
		{
			file >> oneRowData[j];
		}
		pathMatrix.push_back(oneRowData);
	}
	file.close();
}

int main()
{
	string fileName = "lengthOfPath.txt";
	int row = 10;
	int col = 10;

	vector<vector<int>> pathMatrix;
	ReadFile<int>(pathMatrix, fileName, row, col);
	cout << "Minimum Path = " << MinimumPath(pathMatrix, row, col) << endl;

	cout << pathMatrix[8][9] << endl;
	return 0;
}