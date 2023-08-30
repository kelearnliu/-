#include <iostream>
#include <memory>
#include <pv.h>

using namespace std;
class Node {
public:
    Node() {
        std::cout << "Node constructor" << std::endl;
    }

    ~Node() {
        std::cout << "Node destructor" << std::endl;
    }

    // 使用 std::weak_ptr 打破循环引用
//    std::weak_ptr<Node> next;
    std::shared_ptr<Node> next;
};

int main() {
    std::shared_ptr<Node> node1 = std::make_shared<Node>();
    std::shared_ptr<Node> node2 = std::make_shared<Node>();

    node1->next = node2;
    node2->next = node1;

    cout<<"node1:"<<node1.use_count()<<endl;
    cout<<"node2:"<<node2.use_count()<<endl;

    // node1 和 node2 之间使用 std::weak_ptr 打破循环引用


    vector<size_t> arr({1,2,3,4,5,111,8,9,111,10,11});
    TreeNode* root = buildTree(arr,0);
    cout<<root->left->left->val<<endl;
    cout<<root->left->right->val<<endl;
    return 0;
}
