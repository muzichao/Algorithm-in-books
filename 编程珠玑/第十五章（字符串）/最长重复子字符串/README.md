### 最长重复子序列

#### 题目

给定一个文本作为输入，查找其中最长的重复子字符串。

#### 示例

字符串为：“Ask not what your country can do for you, but what you can do for your country”。

最长的重复字符串为：“can do for you”。

#### 解法-构造后缀数组

使用称为“后缀数组”的简单数据结构。这个结构是一个字符指针数组，记为pStr，每个元素都指向字符串中某个位置开始的子字符串。

```cpp
/* 构造后缀数组 */
vector<const char*> pStr;
const char *str = s.c_str();
for (int i = 0; i < s.size(); i++)
{
    pStr.push_back(str);
    str++;
}
```

例如：输入字符串为：“banana”，则：

+ pStr[0]: banana
+ pStr[1]: anana
+ pStr[2]: nana
+ pStr[3]: ana
+ pStr[4]: na
+ pStr[5]: a

#### 解法-后缀数组排序

后缀数组中的每个元素都指向一个字符串，如果某个长字符串在数组中串行两次，那么它将出现在量不同的后缀中，依次可以对数组进行排序以找到相同的后缀。

因为数组的每个元素都相当于一个字符串，因此按照字符串的方式进行比较排序，如下所示：

比较函数如下所示：

```cpp
bool StringCompare(const char *pa, const char *pb)
{
    while (*pa != '\0' && *pb != '\0' && *pa == *pb)
    {
        pa++;
        pb++;
    }

    if (*pa == '\0' && *pb != '\0') /* 小于 */
        return true;
    else if (*pb == '\0') /* 大于等于 */
        return false;
    else
        return *pa < *pb;
}
```

调用方式如下所示：

```cpp
/* 对后缀数组进行排序 */
sort(pStr.begin(), pStr.end(), StringCompare);
```

对“banana”的后缀数组进行排序后如下所示：

+ pStr[0]: a
+ pStr[1]: ana
+ pStr[2]: anana
+ pStr[3]: banana
+ pStr[4]: na
+ pStr[5]: nana

通过比较相邻元素，可以找到最长的重复子字符串：“ana”

#### 解法-获取最长重复子串

对后缀数组中的相邻的元素进行比较，找到最长的重复字符串。

```cpp
int LengthOfCommon(const char *p1, const char *p2)
{
    int length = 0;
    while (p1[length] != '\0' && p2[length] != '\0' && p1[length] == p2[length])
        length++;

    return length;
}
```

调用方式如下所示：

```cpp
/* 依次比较后缀数组的两个相邻子字符串 */
int currentMaxLength = 0;
int currentIndex = 1;
for (int i = 1; i < pStr.size(); i++)
{
    int length = LengthOfCommon(pStr[i-1], pStr[i]);
    if (length > currentMaxLength)
    {
        currentMaxLength = length;
        currentIndex = i;
    }
}

/* 提取公共子字符串 */
string result;
for (int i = 0; i < currentMaxLength; i++)
{
    result += pStr[currentIndex][i];
}
```

#### 流程

1. 构造后缀数组
2. 对后缀数组进行排序
3. 对后缀数组相邻元素进行比较，查找最长重复子串
4. 提取最长重复子串

#### 复杂度分析

假设输入字符串的长度为n，则：

+ 空间复杂度
    空间复杂度为O(n)，因为后缀数组保存的并不是n个子字符串，而是指向这n个字符串的指针。

+ 时间复杂度：
    1. 构建后缀数组的时间复杂度为O(n)
    2. 假设使用快速排序，时间复杂度为O(knlgn)，其中k为字符串的平均比较次数，一般重复子字符串的长度不会特别大，因此k较小。
    3. 查找最长重复子字符串的时间复杂度为O(kn)

综上：空间复杂度为O(n)，时间复杂度为O(nlgn)

#### 实验

以英文版的《简爱》作为输入字符串，总共1059723个字符，最长的重复子串为：
“I am disposed to be gregarious and communicative to-night”。

运行时间为：0.358s
