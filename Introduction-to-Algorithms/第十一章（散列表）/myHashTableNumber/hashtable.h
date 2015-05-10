#define NULL 0

struct Node
{
    int value; // 值
    Node *next; // 指向Node的指针

    Node (int val) // 析构函数
    {
        this->value = val;
        this->next = NULL;
    }
};

class hashtable
{
public:
    hashtable(const int iHashTableSize); // 构造函数
    ~hashtable(); // 析构函数
    int HashFun(int val); // 哈希函数
    bool InsertHashTable(int val); // 插入哈希表
    bool FindHashTable(int val); // 查找哈希表
    int SizeHashTable(); // 哈希表数据个数
    void ShowNodeLinkSize(); // 统计哈希表每个节点的长度
private:
    int iHashTableSize; // 哈希表大小
    int iHashTableDataCount; // 哈希表数据个数
    Node **pHashTable; // 指向哈希表的指针
};

