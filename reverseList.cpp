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



struct ListNode1 {
    int val;
    ListNode1* next;
    ListNode1() :val(0), next(nullptr) {}
    ListNode1(int value) :val(value), next(nullptr) {}
    ListNode1(int value, ListNode1* next): val(value),next(next){}
};

void reverseList() {
    ListNode1 tail(1,nullptr);
    ListNode1 third(2, &tail);
    ListNode1 second(3, &third);
    ListNode1 first(4, &second);
    ListNode1* head = &first;
    //while (head)
    //{
    //	cout << "正在访问:" << head->val << endl;
    //	head = head->next;
    //}

    // 反转
    ListNode1* tmp;
    ListNode1* pre = nullptr;
    ListNode1* cur = head;
    while (cur)
    {
        tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    while (pre)
    {
        cout << "正在访问:" << pre->val << endl;
        pre = pre->next;
    }
}

int main()
{
    reverseList();
    return 0;
}