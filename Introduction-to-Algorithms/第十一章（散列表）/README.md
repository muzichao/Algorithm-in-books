### 哈希表

#### 定义

数据的存储位置与这个数据在某个函数下的值有关。

> 存储位置 = f(关键字)

査找时，根据这个确定的对应关系找到给定值key的映射f(key),若査找集合中存在这个记录，则必定在f(key)的位置上。

#### 结构

    typedef std::string hashNodeType;

    struct Node
    {
        hashNodeType nodeData;
        Node *next; // 指向Node的指针

        Node (hashNodeType val) // 析构函数
        {
            this->nodeData = val;
            this->next = NULL;
        }
    };

以上述节点的形式存储，数据和一个指向节点的指针构成一个节点。然后定义一个指针数组，用于构成哈希表的头。

#### 文件结构

1. myHashTableNumber 整数型哈希表
2. myHashTableString 字符串型哈希表
3. myHashTableStringBlizzard 参考暴雪算法的字符串型哈希表

