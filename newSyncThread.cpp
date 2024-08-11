#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

std::mutex mtx;
std::condition_variable cv;
bool flag{false};

using namespace std;

int main()
{
    cout<<"aaa"<<endl;
    return 0;
}