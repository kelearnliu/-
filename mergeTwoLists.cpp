//
// Created by MI on 2023/8/24.
//

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
#include <stack>
#include <iterator>
#include <complex>
#include <algorithm>
#include <queue>
using namespace std;


// 合并两个链表
class ListNode {
public:
    ListNode():val(0),next(nullptr) {}
    ListNode(int value) :val(value), next(nullptr) {}
    ListNode(int value, ListNode* n) :val(value), next(n) {}
public:
    int val;
    ListNode* next;
};

void merge()
{
    vector<int> A{ 0,1,2,3,4,5,6 };
    vector<int> B{ 10000, 10001,10002,10003,1004 };
    ListNode* headA = new ListNode(A[0]);
    ListNode* dummyA = new ListNode(A[0],headA);

    ListNode* headB = new ListNode(B[0]);
    ListNode* dummyB = new ListNode(B[0],headB);
    for (int i = 1; i < A.size(); i++)
    {
        ListNode* tmp = new ListNode(A[i]);
        headA->next = tmp;
        headA = headA->next;
    }
    headA->next = nullptr;
    for (int i = 1; i < B.size(); i++)
    {
        ListNode* tmp= new ListNode(B[i]);
        headB->next = tmp;
        headB = headB->next;
    }
    headB->next = nullptr;

    ListNode* l1 = dummyA->next;
    ListNode* l2 = dummyB->next;
    int a = 2, b = 5;

    int a1 = a -1;
    while (a1--)
    {
        l1 = l1->next;
    }

    ListNode* tmp = l1->next;

    l1->next = l2;
    while (l2->next)
    {
        l2 = l2->next;
    }

    cout << tmp->val << endl;
    int interval = b - a;
    cout << "interval"<< interval << endl;
    while (interval-- && tmp->next)
    {
        cout << "before" << tmp->val;
        tmp = tmp->next;
        cout << "after" << tmp->val << endl;
    }

    cout << tmp->val << endl;
    l2 -> next = tmp->next;

    cout << l2->val << endl;
    while (l2->next)
    {
        l2 = l2->next;
    }

    while (dummyA->next)
    {
        cout << dummyA->next->val << endl;
        dummyA = dummyA->next;
    }
    return;
}