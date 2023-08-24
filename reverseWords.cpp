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

void reverseWords() {
    string input = "  the sky    is  blue  ";
    cout << input << endl;
    int slowIndex = 0;
    int fastIndex = 0;
    // 先得到一个去除掉前后空格 和 中间多余空格的字符串
    for (; fastIndex < input.size(); fastIndex++) {
        if (!isspace(input[fastIndex])) {
            if (slowIndex != 0) {
                input[slowIndex++] = ' ';
            }
            // 只要在内部就一直移动
            while (fastIndex < input.size() && input[fastIndex] != ' ') {
                input[slowIndex++] = input[fastIndex++];
            }

        }
    }
    input.resize(slowIndex);
    cout << input << endl;
    // 反转
    int start = 0;
    for (int i = 0; i <= input.size(); i++) {
        // 要考虑最后的情况
        if (isspace(input[i]) || i==input.size()) {
            reverse(input.begin() + start, input.begin() + i);
            start = i + 1;
        }
    }
    cout << input << endl;
    // 自己也能够实现反转
    for (int i = 0; i < input.size()/2 ; i++) {
        swap(input[i], input[input.size() - i -1]);
    }
    //reverse(input.begin(), input.end());
    cout << input << endl;
}
