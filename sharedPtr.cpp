//#include <iostream>
//#include <memory>
//#include <pv.h>
//
//using namespace std;
//class Node {
//public:
//    Node() {
//        std::cout << "Node constructor" << std::endl;
//    }
//
//    ~Node() {
//        std::cout << "Node destructor" << std::endl;
//    }
//
//    // 使用 std::weak_ptr 打破循环引用
////    std::weak_ptr<Node> next;
//    std::shared_ptr<Node> next;
//};
//
//int main() {
//    std::shared_ptr<Node> node1 = std::make_shared<Node>();
//    std::shared_ptr<Node> node2 = std::make_shared<Node>();
//
//    node1->next = node2;
//    node2->next = node1;
//
//    cout<<"node1:"<<node1.use_count()<<endl;
//    cout<<"node2:"<<node2.use_count()<<endl;
//
//    // node1 和 node2 之间使用 std::weak_ptr 打破循环引用
//
//
//    vector<size_t> arr({1,2,3,4,5,111,8,9,111,10,11});
//    TreeNode* root = buildTree(arr,0);
//    cout<<root->left->left->val<<endl;
//    cout<<root->left->right->val<<endl;
//    return 0;
//}

#include <iostream>
using namespace std;

template<class T>
class sharedPtr{
public:
    // 默认构造函数
    sharedPtr():_ptr(new T),_useCnt(new size_t(0)){}

    // 构造函数
    explicit sharedPtr(T* p):_ptr(p),_useCnt(new size_t)
    {
        if(p)
            *_useCnt=1;
        else
            *_useCnt=0;
    }

    // 拷贝构造
    sharedPtr(const sharedPtr& rhs)
    {
        _ptr=rhs._ptr;
        _useCnt=rhs._useCnt;
        (*_useCnt)++;
    }
    // 赋值构造运算
    sharedPtr& operator=(const sharedPtr& rhs)
    {
        // 两个不一样的时候才计算
        if(this != &rhs)
        {
            // 本指针要不为空
            if(_ptr)
            {
                // 右边计数减一
                --(*_useCnt);
                if(*_useCnt==0)
                {
                    delete _ptr;
                    delete _useCnt;
                }
            }
            _ptr=rhs._ptr;
            _useCnt=rhs._useCnt;
            (*_useCnt)++;
        }
        return *this;
    }

    //析构函数
    ~sharedPtr()
    {
        // 当前指针为空或者为1？ 不应该是0么
        // 是1因为要减了 1减了以后就是0 就要delete指针了
        if(!_ptr || (*_useCnt==1))
        {
            delete _ptr;
            delete _useCnt;
        }
        else
            --(*_useCnt);
    }

//    // 指针解析
//    T operator->()
//    {
//        return *_ptr;
//    }
    size_t use_count() const
    {
        return *_useCnt;
    }

public:
    // 一枚指针+一个计数器
    T* _ptr;
    size_t* _useCnt;
};

int main()
{
    sharedPtr<int> p1(new int(1));
    cout<<"p1 count: "<<p1.use_count()<<endl;

    sharedPtr<int> p2(p1);
    cout<<"p1 count: "<<p1.use_count()<<endl;
    cout<<"p2 count: "<<p2.use_count()<<endl;

    sharedPtr<int> p4;
    cout<<"p4 count: "<<p4.use_count()<<endl;

    p4=p1;
    cout<<"p1 count: "<<p1.use_count()<<endl;
    cout<<"p4 count: "<<p4.use_count()<<endl;

    sharedPtr<int> p5=p1;
    cout<<"p1 count: "<<p1.use_count()<<endl;
    cout<<"p5 count: "<<p5.use_count()<<endl;
    return 0;
}






