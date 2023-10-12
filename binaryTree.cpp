//#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "pv.h"

using namespace std;



vector<vector<size_t>> levelIter(TreeNode* root)
{
    if(!root) return{{}};

    vector<vector<size_t>> result;
    vector<size_t> res;
    queue<TreeNode*> que;
    que.push(root);
    while (!que.empty())
    {
        size_t size = que.size();
        for (int i = 0; i < size; ++i) {
            TreeNode* node = que.front();
            res.push_back(node->val);
            que.pop();
            if(node->left) que.push(node->left);
            if(node->right) que.push(node->right);
        }
        result.push_back(res);
        res.clear();
    }
    return result;
}

int main()
{
    //        1
    //      2  3
   //     4 5 6 7
    vector<size_t> a{1,2,3,4,5,6,7};
    TreeNode* head = buildTree(a,0);

    vector<size_t> pre = preOrderIter(head);
    printVec(pre);
    vector<size_t> in = inOrderIter(head);
    printVec(in);
    vector<size_t> last = lastOrderIter(head);
    printVec(last);

    printVVec(levelIter(head));


    return 0;
}