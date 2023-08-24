//
// Created by MI on 2023/8/24.
//
#include <iostream>
#include <vector>
#include "pv.h"
using namespace std;

int main()
{
    ListNode t4(4);
    ListNode t3(3,&t4);
    ListNode t2(2,&t3);
    ListNode t1(1,&t2);
    auto* head = new ListNode(0,&t1);
    printList(head);
    int k=3;

    auto* dummyNode = new ListNode(-1,head);
    cout<<"dummyNode_val:"<<dummyNode->next_->val_<<endl;
    auto* slow=new ListNode(0,head);
    auto* fast=new ListNode(0,head);
    // n是总长度
    int n=1;
    while(head->next_!= nullptr)
    {
        n++;
        head=head->next_;
    }
    cout<<"length:"<<n<<endl;

    k %=n;
    if(k==0)
    {
        printList(dummyNode->next_);
        return 0;
    }

    int count = n-k-1;
//    count-=1;
    while (count--)
    {
        slow=slow->next_;
        fast=fast->next_;
    }
    fast=fast->next_;
    // 新的头结点
    auto* newDummyNode = new ListNode(0,fast->next_);

    // 让fast找到最后一个元素 并把它的指针指向dummyNode的下一个指针
    while (fast->next_->next_!= nullptr)
    {
        fast=fast->next_;
    }
    // fast->next=最后一个节点
    fast->next_->next_ =dummyNode->next_;
    slow->next_->next_= nullptr;
    printList(newDummyNode->next_);
    return 0;
}