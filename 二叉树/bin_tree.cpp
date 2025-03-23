// 二叉树层级遍历
// https://leetcode.cn/problems/binary-tree-level-order-traversal/
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// 普通版本
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> ans;
    if (root)
    {
        queue<TreeNode *> q;
        map<TreeNode *, int> levels;
        q.push(root);
        levels[root] = 0;

        while (!q.empty())
        {
            TreeNode *cur = q.front();
            q.pop();
            int level = levels[cur];

            if (ans.size() == level)
            { // 说明到了新的一层，这个是一级的
                ans.push_back({});
            }
            ans[level].push_back(cur->val);

            if (cur->left)
            {
                q.push(cur->left);
                levels[cur->left] = level + 1;
            }
            if (cur->right)
            {
                q.push(cur->right);
                levels[cur->right] = level + 1;
            }
        }
    }
    return ans;
}

// 优化版本
vector<vector<int>> levelOrders(TreeNode *root)
{
    vector<vector<int>> ans;
    TreeNode *queue[2001];
    int l = 0, r = 0;
    if (root != nullptr)
    {
        l = r = 0;
        queue[r++] = root;
        while (l < r)
        {
            int size = r - l;
            vector<int> ret;
            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = queue[l++];
                ret.push_back(cur->val);
                if (cur->left)
                {
                    queue[r++] = cur->left;
                }
                if (cur->right)
                {
                    queue[r++] = cur->right;
                }
            }
            ans.push_back(ret);
        }
    }
    return ans;
}

// 锯齿遍历
// https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/description/
vector<vector<int>> zigzaglevelOrder(TreeNode *root)
{
    vector<vector<int>> ans;
    TreeNode *queue[2001];
    int l = 0, r = 0;
    bool reverse = false;
    if (root != nullptr)
    {
        l = r = 0;
        queue[r++] = root;
        while (l < r)
        {
            int size = r - l;
            vector<int> ret;
            // reverse  ==false 左->右 l ... r-1 收集size
            // reverse  ==true 右->左  r-1 ... l 收集size
            for (int i = reverse ? r - 1 : l, j = reverse ? -1 : 1, k = 0; k < size; k++, i += j)
            {
                TreeNode *cur = queue[i];
                ret.push_back(cur->val);
            }
            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = queue[l++];
                if (cur->left)
                {
                    queue[r++] = cur->left;
                }
                if (cur->right)
                {
                    queue[r++] = cur->right;
                }
            }
            reverse = !reverse;
            ans.push_back(ret);
        }
    }
    return ans;
}

// 最大特殊宽度
// https://leetcode.cn/problems/maximum-width-of-binary-tree/description/
int widthOfBinaryTree(TreeNode *root)
{
    int max = 0, l = 0, r = 0;
    TreeNode *queue[3001];
    // 防止值越界，因为值可能很大
    unsigned long long index[3001];
    l = r = 0;
    index[r] = 1;
    queue[r++] = root;
    while (l < r)
    {
        int size = r - l;
        // 最右－最左
        if (max < index[r - 1] - index[l] + 1)
            max = index[r - 1] - index[l] + 1;
        for (int i = 0; i < size; i++)
        {
            TreeNode *cur = queue[l++];
            // 左右同时处理
            if (cur->left)
            {
                // 记录对应的index
                index[r] = index[l - 1] * 2 + 1;
                queue[r++] = cur->left;
            }
            if (cur->right)
            {
                index[r] = index[l - 1] * 2 + 2;
                queue[r++] = cur->right;
            }
        }
    }
    return max;
}
// 最高深度
// https://leetcode.cn/problems/maximum-depth-of-binary-tree/description/
int maxDepth(TreeNode *root)
{
    return root == nullptr ? 0 : max(maxDepth(root->left), maxDepth(root->right)) + 1;
}
// 最低深度
// https://leetcode.cn/problems/minimum-depth-of-binary-tree/
int minDepth(TreeNode *root)
{
    // 如果是空就结束
    if (root == nullptr)
        return 0;
    // 说明找到了一个叶子节点返回
    if (root->left == nullptr && root->right == nullptr)
        return 1;
    //    这里一定要定义在这里，因为我是为了找左边最小和右边最小，这个值要保证每次调用不被影响
    int ldeep = INT16_MAX;
    int rdeep = INT16_MAX;
    if (root->left)
    {
        ldeep = minDepth(root->left);
    }
    if (root->right)
    {
        rdeep = minDepth(root->right);
    }
    // 比较两边最小的一个
    return min(ldeep, rdeep) + 1;
}

// 二叉树序列化和反序列化
// https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/
// Encodes a tree to a single string.
string serialize(TreeNode *root)
{
    string str = "";
    TreeNode *queue[10001];
    int l = 0, r = 0;
    if (root != nullptr)
    {
        l = r = 0;
        queue[r++] = root;
        str.append(to_string(root->val));
        str.append("|");
        while (l < r)
        {
            int size = r - l;
            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = queue[l++];
                if (cur->left)
                {
                    queue[r++] = cur->left;
                    str.append(to_string(cur->left->val));
                    str.append("|");
                }
                else
                {
                    str.append("#");
                    str.append("|");
                }
                if (cur->right)
                {
                    queue[r++] = cur->right;
                    str.append(to_string(cur->right->val));
                    str.append("|");
                }
                else
                {
                    str.append("#"); // 用于恢复二叉树
                    str.append("|");
                }
            }
        }
    }
    return str;
}

int index = 0;
string qu_value(string data){
    string ret="";
    while (index<data.size()&&data[index]!='|')
    {
        ret+=data[index++];
    }
    index++;
    return ret;
}
// Decodes your encoded data to tree.
TreeNode *deserialize(string data)
{
    TreeNode *root;
    TreeNode *queue[10001];
    int r = 0, l = 0;
    if (data.size() == 0)
        return nullptr;
    string strs=qu_value(data);
    root = new TreeNode(stoi(strs));
    queue[r++] = root;
    while (index < data.size())
    {
        int size = r - l;
        for (int i = 0; i < size; i++)
        {
            TreeNode *cur = queue[l++];
            strs=qu_value(data);
            if(strs.empty())break;
            if (strs!= "#")
            {
                cur->left = new TreeNode(stoi(strs));
                queue[r++] = cur->left;
            }
            strs=qu_value(data);
            if(strs.empty())break;
             if (strs!= "#")
            {
                cur->right = new TreeNode(stoi(strs));
                queue[r++] = cur->right;
            }
        }
    }
    return root;
}

// 利用先序和中序构建二叉树
// https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
TreeNode * f(vector<int>& preorder,int l1,int r1, vector<int>& inorder,int l2,int r2, map<int,int>& index_map){
    if(r1<l1)return nullptr;
    // 第一个肯定是头结点
    TreeNode *head=new TreeNode(preorder[l1]);
    if(l1==r1)return head;
    int find=index_map[preorder[l1]];
    // 前序往后数find位的值，对应的是中序中位置往前的位置
    head->left=f(preorder,l1+1,l1+find-l2,inorder,l2,find-1,index_map);
    // 上面位往后数到结束的值，对应的是中序往后的结束的位置
    head->right=f(preorder,l1+find-l2+1,r1,inorder,find+1,r2,index_map);
    return head;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    map<int,int> index_map;
    // 加速查找中序遍历中，在什么位置
    for(int i=0;i<inorder.size();i++){
        index_map[inorder[i]]=i;
    }
    return f(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1,index_map);
}
// 验证完全二叉树
// https://leetcode.cn/problems/check-completeness-of-a-binary-tree/
 bool isCompleteTree(TreeNode* root) {
    TreeNode *queue[105];
    int l = 0, r = 0;
    bool leaf = false,ret=true;
    if (root != nullptr)
    {
        l = r = 0;
        queue[r++] = root;
        while (l < r)
        {
            int size = r - l;
           
            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = queue[l++];
                // 右子树不等于空，但是左子树是空，是不能出现这种情况的
                // 已经出现了左子树是空的情况，那么接下来的所有节点都不能有孩子
                if((cur->right!=nullptr&&cur->left==nullptr)||(leaf&&(cur->left!=nullptr||cur->right!=nullptr)))ret=false;
                if (cur->left)
                {
                    queue[r++] = cur->left;
                }
                if (cur->right)
                {
                    queue[r++] = cur->right;
                }
                if(cur->left==nullptr||cur->right==nullptr){
                    leaf=true;
                }
            }
        }
    }
    return ret;
 }
//  求完全二叉树的节点个数 2的h次方-1等于节点数h层高的
// https://leetcode.cn/problems/count-complete-tree-nodes/
// 找节点高度
int mostleft(TreeNode *root,int num){
    TreeNode *k=root;
    while(k){
        k=k->left;
        num++;
    }
    return num-1;
}

int countf(TreeNode * root,int level,int h){
    // 如果当前高度等于了总高度，那就说明只有一个根节点，就是1
   if(level==h)return 1;
//   查看当前节点的右节点高度是否等于总节点，如果等，说明这个节点的右边一定是满二叉树，而这颗满二叉子树的数量就等于总深度减掉当前深度，的2的这么多次方减一，但是由于算上我自己，总数就是2的这么多次方
// 然后就算右边的数量
   if(mostleft(root->right,level+1)==h){
      return (1<<(h-level))+countf(root->right,level+1,h);
   }else{
    // 如果右边没有插到底，说明右边这课子树一定是满的，那么数量就和上面类似，但是要减一层。继续递归左边就
      return (1<<(h-level-1))+countf(root->left,level+1,h);
   }
}
int countNodes(TreeNode* root) {
        if(root==nullptr)return 0;
        return countf(root,1,mostleft(root,1));
}


TreeNode *generateRandomTree(int numNodes)
{
    if (numNodes <= 0)
        return nullptr;

    vector<TreeNode *> nodes;
    for (int i = 1; i <= numNodes; ++i)
    {
        nodes.push_back(new TreeNode(i));
    }

    for (int i = 1; i < numNodes; ++i)
    {
        TreeNode *parent = nodes[rand() % i];
        if (!parent->left)
        {
            parent->left = nodes[i];
        }
        else if (!parent->right)
        {
            parent->right = nodes[i];
        }
        else
        {
            --i;
        }
    }
    return nodes[0];
}

// 打印二叉树结构
void printTree(TreeNode *root, int space = 0, int count = 5)
{
    if (!root)
        return;
    space += count;
    printTree(root->right, space);
    cout << root->val << endl;
    printTree(root->left, space);
}

// 打印层次遍历结果
template <typename T>
void print2DVector(const vector<vector<T>> &vec)
{
    cout << "Level Order Traversal Result:" << endl;
    for (const auto &level : vec)
    {
        for (const auto &val : level)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main()
{
    int numNodes = 100; // 生成 100 个节点的二叉树
    TreeNode *root = generateRandomTree(numNodes);
    // 打印二叉树结构
    cout << "Binary Tree Structure:" << endl;
    // printTree(root);

    // 调用 levelOrder 方法
    vector<vector<int>> result = levelOrder(root);
    cout << serialize(root) << endl;
    // 输出层次遍历结果
    // print2DVector(result);
}