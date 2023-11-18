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

// 1.ð������
// ʱ�临�Ӷȣ����O(n) ���O(n^2) ƽ��O(n^2)
// �ռ临�Ӷȣ�O(1)
void bubble_sort(vector<int>& arr){
    cout<<"bubble_sort"<<endl;
    int len  = arr.size();
    for(int i=0;i<len-1;i++){
        // �����ĸ��������ȥ ���ÿһ�ζ�һ�� �ڲ�Ϳ�����һ��
        // ��Ϊ�Ѿ���������ȥ��
        for(int j=0; j<len-1-i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
        cout<<"after "<<i<<" times:";
        printVector(arr);
    }

}

// 2.ѡ������ �������ݷֲ���� ����O(n^2) �ô��ǲ�ռ����Ŀռ�
// ʱ�临�Ӷȣ�ȫ��O(n^2)
// �ռ临�Ӷȣ�O(1)
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

// 3.�����������������ģ����ұ߳�����ŵ���������������
// �ȳ���� �ٲ����ȥ
// ʱ�临�ӶȺͿռ临�Ӷ�   ͬð��
void insertion_sort(vector<int>& arr){
    cout<<"insertion_sort"<<endl;
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i -1;
        while(j>=0 && key<arr[j]){
            arr[j+1] = arr[j];
            j--;
        }
        // �����ȥ�� ����Ҫ����һλ
        arr[j+1] = key;
        cout<<"after "<<i<<" times:";
        printVector(arr);
    }
}

// 4.ϣ������ https://zhuanlan.zhihu.com/p/122472667
// ���ǵݼ����������㷨���������л�������ʱ�����ܹ�ʵ�ָ�Ч����
// ÿһ�ηֵ������ǲ��ϼ�С�ģ����һ�εļ������1����ô����ѡ��������
// ʱ�临�Ӷȣ����O(n^2)  ���O(n* logn) ƽ��O(n*(logn)^2)  ��Щֵ�Ͳ����й�
// �ռ临�Ӷȣ�O(1)
void shell_sort(vector<int> array) {
    cout<<"shell_sort"<<endl;
    int length = array.size();
    int h = 1;
    while (h < length / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < length; i++) {
            // ��������h�ļ��Ϊһ�� ���ڽ��н���
            for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
                std::swap(array[j], array[j - h]);
            }
            cout<<"h= "<<h<<"\t";
            printVector(array);
        }
        h = h / 3;
    }
}

// 5.�鲢����
// ʱ�临�ӶȱȽ��ȶ��� O(n*logn)
// �ռ临�Ӷȣ�O(n) ������������

// 6.�������� ѡ��һ����Ŧֵ �������ֵ������������ �ݹ����
// �ȹ鲢�ĳ�������ҪС�����Ը���
// ʱ�临�Ӷȣ����O(n*logn) ���O(n^2)ÿ��ѡ�Ķ�����������С ƽ��O(n*logn)
// �ռ临�Ӷȣ�O(1)
//��ε�������ݽṹ����׼�ָ��
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // ѡ�����һ��Ԫ����Ϊ��׼
    int i = low - 1;     // ��ʼ����СԪ�ص�����
    cout<<"pivot:"<<pivot<<"\t";
    // �������飬��С�ڵ��ڻ�׼��Ԫ�ط�����࣬���ڻ�׼��Ԫ�ط����Ҳ�
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    // ����׼Ԫ�ط�����ȷ��λ��
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}
static int count1=0;
void quick_sort(vector<int>& A, int low, int high) //����ĸ����
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

// 7.������
//ʱ�临�Ӷȣ�O(n*logn)
//�ռ临�Ӷȣ�O(1)
void heap_sort(std::vector<int>& arr);
void buildMaxHeap(std::vector<int>& arr);
void heapify(std::vector<int>& arr, int heapSize, int index);
// ���������Ҫ����
void heap_sort(std::vector<int>& arr) {
    int n = arr.size();
    // ��������
    buildMaxHeap(arr);

    // ���ν��Ѷ�Ԫ�أ����ֵ���ŵ�����ĩβ����������
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// �������ѵĸ�������
void buildMaxHeap(std::vector<int>& arr) {
    int n = arr.size();

    // �����һ����Ҷ�ӽڵ㿪ʼ��������ǰ������
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// �����ѵĸ�������
void heapify(std::vector<int>& arr, int heapSize, int index) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    // �Ƚϸ��ڵ�������ӽڵ㣬�ҳ����ֵ������
    if (leftChild < heapSize && arr[leftChild] > arr[largest]) {
        largest = leftChild;
    }

    if (rightChild < heapSize && arr[rightChild] > arr[largest]) {
        largest = rightChild;
    }

    // ������ֵ���Ǹ��ڵ㣬�򽻻����ǣ����ݹ����������������
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
