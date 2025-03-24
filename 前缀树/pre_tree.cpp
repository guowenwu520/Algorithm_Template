// 前缀树又叫字典树，英文名trie：
// 每个样本 都从头节点开始 根据 前缀字符或者前缀数字 建出来的一棵大树，就是前缀树
// 没有路就新建节点；已经有路了，就复用节点

// 前缀树的使用场景：需要根据前缀信息来查询的场景
// 前缀树的优点：根据前缀信息选择树上的分支，可以节省大量的时间
// 前缀树的缺点：比较浪费空间，和总字符数量有关，字符的种类有关
// 前缀树的定制：pass、end等信息
// 节点使用p记录经过的次数，e记录以这个节点结尾的数
// https://leetcode.cn/problems/implement-trie-prefix-tree/
#include <iostream>
#include <string>
using namespace std;
// 不推荐
class Trie
{
    struct PreTree
    {
        int p;
        int e;
        char v;
        int count;
        PreTree *childs[26];
        PreTree(char v_ = ' ') : v(v_)
        {
            p = 0;
            e = 0;
            count = 0;
        }
    };

public:
    PreTree *root;
    Trie()
    {
        root = new PreTree();
    }

    void insert(string word)
    {
        PreTree *cur = root;
        cur->p++;
        for (int i = 0; i < word.size(); i++)
        {
            bool isE = false;
            for (int j = 0; j < cur->count; j++)
            {
                if (cur->childs[j]->v == word[i])
                {
                    isE = true;
                    cur->childs[j]->p++;
                    if (i == word.size() - 1)
                        cur->childs[j]->e++;
                    cur = cur->childs[j];
                    // cout<<cur->v<<" "<<cur->p<<" "<<cur->e<<" old"<<endl;
                    break;
                }
            }
            if (!isE)
            {
                cur->childs[cur->count] = new PreTree(word[i]);
                cur = cur->childs[cur->count++];
                cur->p++;
                if (i == word.size() - 1)
                    cur->e++;
                // cout<<cur->v<<" "<<cur->p<<" "<<cur->e<<endl;
            }
        }
    }

    bool search(string word)
    {
        PreTree *cur = root;
        for (int i = 0; i < word.size(); i++)
        {
            bool isE = false;
            for (int j = 0; j < cur->count; j++)
            {
                if (cur->childs[j]->v == word[i])
                {
                    isE = true;
                    cur = cur->childs[j];
                    break;
                }
            }
            if (!isE)
            {
                return false;
            }
        }
        if (cur->e != 0)
            return true;
        return false;
    }

    bool startsWith(string prefix)
    {
        PreTree *cur = root;
        for (int i = 0; i < prefix.size(); i++)
        {
            bool isE = false;
            for (int j = 0; j < cur->count; j++)
            {
                if (cur->childs[j]->v == prefix[i])
                {
                    isE = true;
                    cur = cur->childs[j];
                    break;
                }
            }
            if (!isE)
            {
                return false;
            }
        }
        return true;
    }
};

// 使用静态数组来实现，推荐

    const int MAXN = 10000;
class Trie2
{
    int tree[MAXN][26]={};
    int end[MAXN]={};
    int pass[MAXN]={};
    int cnt;

public:
    Trie2()
    {
        // 0位置不用
        cnt = 1;
    }

    void insert(string word)
    {
        int cur = 1;
        pass[cur]++;
        for (int i = 0; i < word.size(); i++)
        {
            int path = word[i] - 'a';
            //   没有见过节点
            if (tree[cur][path] == 0)
            {
                // 添加节点
                tree[cur][path] = ++cnt;
            }
            //   走到下一个节点
            cur = tree[cur][path];
            pass[cur]++;
        }
        end[cur]++;
    }

    bool search(string word)
    {
        int cur = 1;
        for (int i = 0; i < word.size(); i++)
        {
            int path = word[i] - 'a';
            //   没有见过节点
            if (tree[cur][path] == 0)
            {
                return false;
            }
            //   走到下一个节点
            cur = tree[cur][path];
        }
        return end[cur];
    }

    bool startsWith(string prefix)
    {
        int cur = 1;
        for (int i = 0; i < prefix.size(); i++)
        {
            int path = prefix[i] - 'a';
            //   没有见过节点
            if (tree[cur][path] == 0)
            {
                return false;
            }
            //   走到下一个节点
            cur = tree[cur][path];
        }
        return pass[cur];
    }
    void delete_w(string word)
    {
        if (search(word))
        {
            int cur = 1;
            for (int i = 0; i < word.size(); i++)
            {
                int path = word[i] - 'a';
                //   当前节点下的这个孩子的pass－1
                if (--pass[tree[cur][path]] == 0)
                {
                    tree[cur][path] = 0;
                    return;
                }
                //   走到下一个节点
                cur = tree[cur][path];
            }
            end[cur]--;
        }
    }
};

int main()
{
    Trie2 *trie = new Trie2();
    trie->insert("apple");
    cout << trie->search("apple") << endl;   // 返回 True
    cout << trie->search("app") << endl;     // 返回 False
    cout << trie->startsWith("app") << endl; // 返回 True
    trie->insert("app");
    cout << trie->search("app") << endl;
    return 0;
}