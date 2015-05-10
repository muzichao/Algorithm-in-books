#include <iostream>

using namespace std;

/**
 * match s2 in s1
 * @param  s1        string1 point
 * @param  s2        string2 poing
 * @param  iLengthS1 string1 length
 * @param  iLengthS2 string2 length
 * @return           true or false
 */
bool StringMatch(const char *s1, const char *s2, const int iLengthS1, const int iLengthS2)
{
    for (int i = 0; i < iLengthS1; ++i)
    {
        int flag = 0;
        while (s1[(i + flag) % iLengthS1] == s2[flag] && flag < iLengthS2)
        {
            flag++;
        }
        if (flag == iLengthS2)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    string str1 = "ABCDEABCDEF";
    string str2 = "EFAB";

    const char *s1 = str1.c_str();
    const char *s2 = str2.c_str();

    cout << StringMatch(s1, s2, str1.size(), str2.size()) << endl;

    return 0;
}
