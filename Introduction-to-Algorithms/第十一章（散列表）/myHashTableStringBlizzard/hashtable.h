#include <string>
// #define NULL 0

typedef std::string hashNodeType;

struct Node
{
    unsigned int nHashA;
    unsigned int nHashB;
    Node *next; // 指向Node的指针

    Node (unsigned int nHashAA, unsigned int nHashBB) // 析构函数
    {
        this->nHashA = nHashAA;
        this->nHashB = nHashBB;
        this->next = NULL;
    }
};

class hashtable
{
public:
    hashtable(const int iHashTableSize); // 构造函数
    ~hashtable(); // 析构函数
    unsigned int HashFun(hashNodeType val, unsigned int iHashType); // 哈希函数
    bool InsertHashTable(hashNodeType val); // 插入哈希表
    bool FindHashTable(hashNodeType val); // 查找哈希表
    int SizeHashTable(); // 哈希表数据个数
    void ShowNodeLinkSize(); // 统计哈希表每个节点的长度
private:
    int iHashTableSize; // 哈希表大小
    int iHashTableDataCount; // 哈希表数据个数
    Node **pHashTable; // 指向哈希表的指针
    unsigned int cryptTable[0x500];

    void InitCryptTable();
};

