//
// Created by wxy on 2023/8/13.
//
#pragma once
#include <iostream>
#include <vector>

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
