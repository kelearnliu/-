//
// Created by MI on 2023/8/24.
//
#include <iostream>
#include <vector>
#include "pv.h"
using namespace std;

ListNode t4(4);
ListNode t3(3,&t4);
ListNode t2(2,&t3);
ListNode t1(1,&t2);
auto* head = new ListNode(0,&t1);

void method1()
{
    printList(head);
    int k=3;
    auto* dummyNode = new ListNode(-1,head);
    cout << "dummyNode_val:" << dummyNode->next->val << endl;
    auto* slow=new ListNode(0,head);
    auto* fast=new ListNode(0,head);
    // n是总长度
    int n=1;
    while(head->next != nullptr)
    {
        n++;
        head=head->next;
    }
    cout<<"length:"<<n<<endl;

    k %=n;
    if(k==0)
    {
        printList(dummyNode->next);
        return;
    }

    int count = n-k-1;
//    count-=1;
    while (count--)
    {
        slow=slow->next;
        fast=fast->next;
    }
    fast=fast->next;
    // 新的头结点
    auto* newDummyNode = new ListNode(0,fast->next);

    // 让fast找到最后一个元素 并把它的指针指向dummyNode的下一个指针
    while (fast->next->next != nullptr)
    {
        fast=fast->next;
    }
    // fast->next=最后一个节点
    fast->next->next =dummyNode->next;
    slow->next->next= nullptr;
    printList(newDummyNode->next);
}

void method2()
{
    printList(head);
    // p0是用来首尾相连的 p1是用来表示新链表的尾巴的 p2是表示新链表的头结点的
    ListNode *iter = head;
    int n=1;
    int k=3;
    while(iter->next!= nullptr)
    {
        n++;
        iter=iter->next;
    }
    k%=n;
    if(k==0) return;

    iter->next = head;
    int interval=n-k;
    while (interval--)
    {
        iter = iter->next;
    }
    ListNode* ret = iter->next;
    iter->next = nullptr;
    printList(ret);
}
int main()
{
//    cout<<"method1"<<endl;
//    method1();
    cout<<"method2"<<endl;
    method2();
    return 0;
}