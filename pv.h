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
    ListNode():val_(0),next_(nullptr){}
    ListNode(int value):val_(value),next_(nullptr){}
    ListNode(int value, ListNode* next):val_(value),next_(next){}
public:
    int val_;
    ListNode* next_;
};
void printList(ListNode* head) {
    while(head->next_!= nullptr)
    {
        std::cout<<head->val_<<"\t";
        head=head->next_;
    }
    std::cout<<head->val_<<std::endl;
}
