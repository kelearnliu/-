#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
template <typename T>
void printVector(T& vec){
    for(auto t:vec)
    {
        cout<<t<<"\t";
    }
    cout<<endl;
}
//https://www.runoob.com/w3cnote/ten-sorting-algorithm.html

// 1.冒泡排序法
// 时间复杂度：最好O(n) 最差O(n^2) 平均O(n^2)
// 空间复杂度：O(1)
void bubble_sort(vector<int>& arr){
    cout<<"bubble_sort"<<endl;
    int len  = arr.size();
    for(int i=0;i<len-1;i++){
        // 把最大的浮到最后面去 外层每一次多一次 内层就可以少一次
        // 因为已经浮到后面去了
        for(int j=0; j<len-1-i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
        cout<<"after "<<i<<" times:";
        printVector(arr);
    }

}

// 2.选择排序 无论数据分布如何 总是O(n^2) 好处是不占额外的空间
// 时间复杂度：全是O(n^2)
// 空间复杂度：O(1)
void selection_sort(vector<int>& arr){
    cout<<"selection_sort"<<endl;
    for(int i=0;i<arr.size()-1;i++){
        int min = i;
        for(int j=i+1;j<arr.size();j++){
            if(arr[j]<arr[min]){
                min = j;
            }
        }
        swap(arr[min],arr[i]);
        cout<<"after "<<i<<" times:";
        printVector(arr);
    }
}

// 3.插入排序：左边是有序的，从右边抽出来放到左边有序的序列中
// 先抽出来 再插入进去
// 时间复杂度和空间复杂度   同冒泡
void insertion_sort(vector<int>& arr){
    cout<<"insertion_sort"<<endl;
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i -1;
        while(j>=0 && key<arr[j]){
            arr[j+1] = arr[j];
            j--;
        }
        // 上面减去了 所以要增加一位
        arr[j+1] = key;
        cout<<"after "<<i<<" times:";
        printVector(arr);
    }
}

// 4.希尔排序 https://zhuanlan.zhihu.com/p/122472667
// 就是递减增量排序算法，整个序列基本有序时，才能够实现高效排序
// 每一次分的组数是不断减小的，最后一次的间隔就是1，那么就是选择排序了
// 时间复杂度：最差O(n^2)  最好O(n* logn) 平均O(n*(logn)^2)  这些值和步长有关
// 空间复杂度：O(1)
void shell_sort(vector<int> array) {
    cout<<"shell_sort"<<endl;
    int length = array.size();
    int h = 1;
    while (h < length / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < length; i++) {
            // 这里是以h的间距为一组 组内进行交换
            for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
                std::swap(array[j], array[j - h]);
            }
            cout<<"h= "<<h<<"\t";
            printVector(array);
        }
        h = h / 3;
    }
}

// 5.归并排序
// 时间复杂度比较稳定： O(n*logn)
// 空间复杂度：O(n) 存放排序的序列

// 6.快速排序 选择一个枢纽值 根据这个值进行左右排序 递归进行
// 比归并的常数因子要小，所以更快
// 时间复杂度：最好O(n*logn) 最差O(n^2)每次选的都是最大或者最小 平均O(n*logn)
// 空间复杂度：O(1)
//严蔚敏《数据结构》标准分割函数
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准
    int i = low - 1;     // 初始化较小元素的索引
    cout<<"pivot:"<<pivot<<"\t";
    // 遍历数组，将小于等于基准的元素放在左侧，大于基准的元素放在右侧
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    // 将基准元素放在正确的位置
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}
static int count1=0;
void quick_sort(vector<int>& A, int low, int high) //快排母函数
{
//    cout<<"quick_sort"<<endl;
    if (low < high)
    {
        int pivot = partition(A, low, high);
        quick_sort(A, low, pivot - 1);
        quick_sort(A, pivot + 1, high);
        cout<<"after "<<count1<<"times"<<"\t";
        printVector(A);
        count1++;
    }
}

// 7.堆排序
//时间复杂度：O(n*logn)
//空间复杂度：O(1)
void heap_sort(std::vector<int>& arr);
void buildMaxHeap(std::vector<int>& arr);
void heapify(std::vector<int>& arr, int heapSize, int index);
// 堆排序的主要函数
void heap_sort(std::vector<int>& arr) {
    int n = arr.size();
    // 构建最大堆
    buildMaxHeap(arr);

    // 依次将堆顶元素（最大值）放到数组末尾，并调整堆
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 构建最大堆的辅助函数
void buildMaxHeap(std::vector<int>& arr) {
    int n = arr.size();

    // 从最后一个非叶子节点开始，依次向前调整堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// 调整堆的辅助函数
void heapify(std::vector<int>& arr, int heapSize, int index) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    // 比较根节点和左右子节点，找出最大值的索引
    if (leftChild < heapSize && arr[leftChild] > arr[largest]) {
        largest = leftChild;
    }

    if (rightChild < heapSize && arr[rightChild] > arr[largest]) {
        largest = rightChild;
    }

    // 如果最大值不是根节点，则交换它们，并递归调整被交换的子树
    if (largest != index) {
        std::swap(arr[index], arr[largest]);
        heapify(arr, heapSize, largest);
    }
}

int main() {
    vector<int> arr ={61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62 };
    cout<<"original arr:";
    printVector(arr);
    bubble_sort(arr);
    cout<<endl;


    cout<<"original arr:";
    arr ={61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62 };
    printVector(arr);
    selection_sort(arr);
    cout<<endl;

    cout<<"original arr:";
    arr ={61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62 };
    printVector(arr);
    insertion_sort(arr);
    cout<<endl;

    cout<<"original arr:";
    arr ={61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62 };
    printVector(arr);
    shell_sort(arr);
    cout<<endl;

    cout<<"original arr:";
    arr ={61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62 };
    printVector(arr);
    quick_sort(arr,0,arr.size()-1);
    cout<<endl;

    cout<<"original arr:";
    arr ={61, 17, 29, 22, 34, 60, 72, 21, 50, 1, 62 };
    printVector(arr);
    heap_sort(arr);
    cout<<endl;
    printVector(arr);


    return 0;
}
