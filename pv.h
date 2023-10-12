//
// Created by wxy on 2023/8/13.
//
#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
using namespace std;
template <typename T>
void printVec(std::vector<T> t) {
    for (auto c : t)
        std::cout << c<<"\t";
    std::cout << std::endl;
}
template <typename T>
void printVVec(std::vector<std::vector<T>> t) {
    for (auto c : t) {
        printVec(c);
    }
}

class ListNode{
public:
    ListNode(): val(0), next(nullptr){}
    ListNode(int value): val(value), next(nullptr){}
    ListNode(int value, ListNode* next): val(value), next(next){}
public:
    int val;
    ListNode* next;
};
void printList(ListNode* head) {
    while(head->next != nullptr)
    {
        std::cout << head->val << "\t";
        head=head->next;
    }
    std::cout << head->val << std::endl;
}


class TreeNode{
public:
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(size_t value): val(value),left(nullptr),right(nullptr){}
    TreeNode(size_t value,TreeNode* left,TreeNode* right): val(value),left(left),right(right){}
public:
    size_t val;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* buildTree(std::vector<size_t>array, int index)
{
    TreeNode* root = nullptr;
    if(index<array.size() && array[index]!=111)
    {
        root= new TreeNode(array[index]);
        root->left= buildTree(array,2*index+1);
        root->right= buildTree(array,2*index+2);
    }
    return root;
}


// �������ı������� �ݹ�
void preOrderRec(TreeNode* root)
{
    if(!root)
        return;
    cout<<root->val<<endl;
    preOrderRec(root->left);
    preOrderRec(root->right);
}

void inOrderRec(TreeNode* root)
{
    if(!root)return;
    inOrderRec(root->left);
    cout<<root->val<<endl;
    inOrderRec(root->right);
}

void lastOrderRec(TreeNode* root)
{
    if(!root)return;
    lastOrderRec(root->left);
    lastOrderRec(root->right);
    cout<<root->val<<endl;
}


vector<size_t>  preOrderIter(TreeNode* root)
{
    if(!root) return {};
    stack<TreeNode*> stk;
    vector<size_t> res;
    stk.push(root);
    while (!stk.empty())
    {
        TreeNode* node =stk.top();
        stk.pop();
        res.push_back(node->val);
        if(node->left) stk.push(node->left);
        if(node->right) stk.push(node->right);
    }
    return res;
//    printVec(res);
}

vector<size_t>  inOrderIter(TreeNode* root)
{
    if(!root) return{};
    stack<TreeNode*> stk;
    vector<size_t> res;
    TreeNode* node = root;

    while (!stk.empty() || node != nullptr)
    {
        // ��
        while (node != nullptr)
        {
            stk.push(node);
            node=node->left;
        }
        // ��
        node = stk.top();
        stk.pop();

        // ����
        res.push_back(node->val);

        // ��
        node=node->right;
    }
    return res;
//    printVec(res);
}
// ������
vector<size_t> lastOrderIter(TreeNode* root)
{
    if(!root) return{};
    stack<TreeNode*> stk;
    vector<size_t> res;
    stk.push(root);
    while(!stk.empty()){
        TreeNode* node = stk.top();
        stk.pop();
        res.emplace_back(node->val);

        // ������ ˳����ջ  ��ô��ջ��ʱ����������� ��תһ�¾��������� Ҳ���Ǻ�������
        if(node->left) stk.emplace(node->left);
        if(node->right) stk.emplace(node->right);
        // �����right��left ����reverse  �Ǿ���ǰ�����
    }
    std::reverse(res.begin(), res.end());
    return res;
//    printVec(res);
}