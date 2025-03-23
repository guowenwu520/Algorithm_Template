
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <algorithm>
#include <climits>
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
// 搜索树找最近公共祖先
// https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
// 左边都小于它，右边都大于它。
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    int min_v = min(p->val, q->val);
    int max_v = max(p->val, q->val);
    if (root == nullptr)
        return nullptr;
    while (root && root->val != q->val && root->val != p->val) // 要不就是等于某个值的是祖先，因为大于它一定在它右边，小于它一定在它左边
    {
        if (root->val > min_v && root->val < max_v) // 两个值之间的一定是公共祖先
            break;
        root = root->val < min_v ? root->right : root->left;
    }
    return root;
}
// 普通树查找最近公共祖先
// https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
TreeNode *lowestCommonAncestor2(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (root == nullptr || root == p || root == q)
    {
        return root;
    }
    TreeNode *l = lowestCommonAncestor2(root->left, p, q);
    TreeNode *r = lowestCommonAncestor2(root->right, p, q);
    if (l == nullptr && r == nullptr)
        return nullptr;
    if (l != nullptr && r != nullptr)
        return root;
    return l != nullptr ? l : r;
}
// 路径和
// https://leetcode.cn/problems/path-sum-ii/

void dfs(TreeNode *cur, int mun, int targetSum, vector<int> &ret, vector<vector<int>> &ans)
{
    if (cur->left == nullptr && cur->right == nullptr)
    {
        if (mun + cur->val == targetSum)
        {
            ret.push_back(cur->val);
            ans.push_back(ret);
            ret.pop_back();
        }
    }
    else
    {
        ret.push_back(cur->val);
        if (cur->left)
        {
            dfs(cur->left, mun + cur->val, targetSum, ret, ans);
        }
        if (cur->right)
        {
            dfs(cur->right, mun + cur->val, targetSum, ret, ans);
        }
        ret.pop_back();
    }
}

vector<vector<int>> pathSum(TreeNode *root, int targetSum)
{
    vector<vector<int>> ans;
    vector<int> ret;
    if (root == nullptr)
        return ans;
    dfs(root, 0, targetSum, ret, ans);
    return ans;
}

// 验证平衡二叉树，每个点的左右树相差不超过1
// https://leetcode.cn/problems/ping-heng-er-cha-shu-lcof/description/
bool isbalance = true;
int bfsHeight(TreeNode *cur)
{
    if (!isbalance || cur == nullptr)
        return 0;
    int lh = bfsHeight(cur->left);
    int rh = bfsHeight(cur->right);
    if (abs(lh - rh) > 1)
        isbalance = false;
    return max(lh, rh) + 1;
}
bool isBalanced(TreeNode *root)
{
    isbalance = true;
    bfsHeight(root);
    return isbalance;
}
// 验证搜索二叉树，中序遍历的结果完全递增就是搜索二叉树（左中右）
// https://leetcode.cn/problems/validate-binary-search-tree/
bool ret = true;
long long val = 0;
void centr_p(TreeNode *cur)
{
    if (cur == nullptr || !ret)
        return;
    centr_p(cur->left);
    if (cur->val > val)
        val = cur->val;
    else
        ret = false;
    centr_p(cur->right);
}
bool isValidBST(TreeNode *root)
{
    ret = true;
    val = LLONG_MIN;
    centr_p(root);
    return ret;
}
// 修剪搜索二叉树
//  https://leetcode.cn/problems/trim-a-binary-search-tree/description/
TreeNode *trimBST(TreeNode *root, int low, int high)
{
    if (root == nullptr)
        return nullptr;
    if (root->val < low) // 如果小于最小值，说明合适的值在右边找
        return trimBST(root->right, low, high);
    if (root->val > high) // 如果大于最大值，说明合适的值在左边找
        return trimBST(root->left, low, high);
    // 找到合适的值保留，然后继续去左边，右边找合适的值
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}
// 二叉树打家劫舍问题，不能偷相邻的节点
// https://leetcode.cn/problems/house-robber-iii/
int yes, no;//偷不偷当前节点
int rob(TreeNode *root)
{
    if (root == nullptr)//没得偷
    {
        yes = 0;
        no = 0;
    }
    else
    {
        int y = root->val;//偷当前和不偷的收益
        int n = 0;
        rob(root->left);
        y += no;//偷这个节点，那我就不能偷子节点
        n += max(yes, no);//不偷当前节点，也可以偷或者不偷，选最好的
        rob(root->right);
        y += no;
        n += max(yes, no);
        yes = y;
        no = n;
    }
    return max(yes,no);
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

int main()
{
    int numNodes = 100; // 生成 100 个节点的二叉树
    TreeNode *root = generateRandomTree(numNodes);
    // 打印二叉树结构
    cout << "Binary Tree Structure:" << endl;
}