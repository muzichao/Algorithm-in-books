#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
* LongestCommonSubsequence 最长公共子序列
* strA：序列A  输入
* strB：序列B  输入
* return：     输出
* 说明：未使用额外的标记表
*/
string LongestCommonSubsequence(string strA, string strB)
{
	string result; // 最长公共子序列

	vector<vector<int>> subLCS;
	vector<int> currentRow(strB.size() + 1, 0);
	subLCS.push_back(currentRow); // 初始化第一行为0

	/*计算最长公共子序列表*/
	for (int i = 1; i <= strA.size(); i++)
	{
		for (int j = 1; j <= strB.size(); j++)
		{
			currentRow[j] = (strA[i-1] == strB[j-1]) ? (subLCS[i-1][j-1] + 1) : max(currentRow[j-1], subLCS[i-1][j]);
		}
		subLCS.push_back(currentRow);
	}

	/* 根据最长公共子序列表查找最长公共子串 */
	int i = strA.size();
	int j = strB.size();
	while (i > 0 && j > 0)
	{
		/* 查找上一个公共字母 */
		while (i > 0 && subLCS[i-1][j] == subLCS[i][j]) 
			i--;
		if (strA[i] != strB[j])
		{
			while (j > 0 && subLCS[i][j-1] == subLCS[i][j])
				j--;
		}

		result = strA[i-1] + result; // 此时i和j必定指向一个相同的字母
		i--;
		j--;
	}

	return result;
}

int main()
{
	string strA = "ABCBDAB";
	string strB = "BDCABA";

	cout << strA.c_str() << endl;
	cout << strB.c_str() << endl;
	cout << LongestCommonSubsequence(strA, strB).c_str() << endl;

	return 0;
}