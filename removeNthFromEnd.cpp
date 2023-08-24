//
// Created by MI on 2023/8/24.
//
#include <iostream>
#include <algorithm>
#include <complex>
using namespace std;

struct ListNode1 {
    int val;
    ListNode1* next;
    ListNode1() :val(0), next(nullptr) {}
    ListNode1(int value) :val(value), next(nullptr) {}
    ListNode1(int value, ListNode1* next): val(value),next(next){}
};

void printList(ListNode1*  head) {
    while (head)
    {
        cout << head->val << endl;
        head = head->next;
    }
}
void removeNthFromEnd() {
    ListNode1 tail(1, nullptr);
    ListNode1 third(2, &tail);
    ListNode1 second(3, &third);
    ListNode1 first(4, &second);
    ListNode1* head = &first;


    int n = 2;
    printList(head);
    ListNode1* dummy = new ListNode1(0, head);
    ListNode1* first1 = head;
    ListNode1* second1 = dummy;
    while (n--) {
        first1 = first1->next;
    }
    while (first1)
    {
        first1 = first1->next;
        second1 = second1->next;
    }
    second1->next = second1->next->next;
    ListNode1* ans = dummy->next;
    delete dummy;
    printList(ans);

}