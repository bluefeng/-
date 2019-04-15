#include<iostream>
#include <algorithm>
using namespace std;

//冒泡排序
void sort_maopao(int* arr, int length) {
    for (int i = 0; i < length - 1; ++i) {
        bool sort = false;
        for (int j = 0; j < length - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                sort = true;
            }
        }
        if (!sort) {
            break;
        }
    }
}

//选择排序
void sort_select(int* arr, int length) {
    int minIdx;
    int temp;
    for (int i = 0; i < length - 1; ++i) {
        minIdx = i;
        for (int j = i + 1; j < length; ++j) {
            if (arr[minIdx] > arr[j]) {
                minIdx = j;
            }
        }
        if (i != minIdx) {
            temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

//插入排序
void sort_insert(int* arr, int length) {
    int curValue;
    int preIdx;

    for (int i = 1; i < length; ++i) {
        preIdx = i - 1;
        curValue = arr[i];
        while (preIdx >= 0 && curValue < arr[preIdx]) {
            arr[preIdx + 1] = arr[preIdx];
            --preIdx;
        }
        arr[preIdx + 1] = curValue;
    }
}

//希尔排序
void sort_shell(int* arr, int length) {
    for (int group = length / 2; group > 0; group = group / 2) {
        for (int i = group; i < length; ++i) {
            int j = i;
            int curValue = arr[i];
            while (j - group >= 0 && curValue < arr[j - group]) {
                arr[j] = arr[j - group];
                j = j - group;
            }
            arr[j] = curValue;
        }
    }
}

//归并排序
void merge(int* left, int l_len, int* right, int r_len, int * data) {
    int length = l_len + r_len;
    if (length <= 0) return;
    int * temp = new int[length];
    int l = 0, r = 0;
    while (l < l_len && r < r_len) {
        if (left[l] <= right[r]) {
            temp[l + r] = left[l];
            ++l;
        }
        else {
            temp[l + r] = right[r];
            ++r;
        }
    }
    if (l < l_len) {
        memcpy(temp + l + r, left + l, (l_len - l) * sizeof(int));
    }
    else if(r < r_len) {
        memcpy(temp + l + r, right + r, (r_len - r) * sizeof(int));
    }
    memcpy(data, temp, length * sizeof(int));
    delete[] temp;
}

void sort_merge(int* arr, int length) {
    int step = 1;
    while (step < length) {
        for (int i = 0; i < length - step; i += 2 * step) {
            merge(arr + i, step, arr + i + step, min(length - i - step, step), arr + i);
        }
        step *= 2;
    }
}

//快速排序
void sort_quick(int* arr, int length) {
    if (length <= 0) return;
    int i = 0;
    int j = length;
    int key = arr[i];
    while (true) {
        while (arr[++i] < key) {
            if (i == length - 1)
                break;
        }
        while (arr[--j] > key) {
            if (j == 0)
                break;
        }
        if (i >= j) break;

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    int temp = arr[0];
    arr[0] = arr[j];
    arr[j] = temp;

    sort_quick(arr, j);
    sort_quick(arr + j + 1, length - j - 1);
}

//堆排序
void max_heapify(int* arr, int length) {
    int dad = 0;
    int son = dad * 2 + 1;
    int end = length - 1;
    while (son <= end) {
        if (son + 1 <= end && arr[son] < arr[son + 1])
            ++son;
        if (arr[dad] > arr[son])
            return;
        else {
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}
void sort_heap(int* arr, int length) {
    for (int i = length / 2 - 1; i >= 0; --i) {
        max_heapify(arr + i, length - i);
    }
    for (int i = length - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        max_heapify(arr, i);
    }
}

//计数排序
void sort_counting(unsigned int* arr, int length) {
    int max = 0;
    for (int i = 0; i < length; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    int* counts = new int[max + 1](); //初始化为0
    
    for (int i = 0; i < length; ++i) {
        counts[arr[i]]++;
    }
    int curIdx = 0;
    for (int i = 0; i <= max; i++) {
        while (counts[i] > 0) {
            arr[curIdx++] = i;
            counts[i]--;
        }
    }
    delete[] counts;
}
void sort_counting(int* arr, int length){
    if (length <= 1) return;
    int pcount = 0;
    for (int i = 0; i < length; ++i){
        if (arr[i] < 0){
            pcount++;
        }
    }
    if (pcount > 0){
        int* parr = new int[pcount + 1]();
        int* narr = new int[length - pcount + 1]();
        for(int i = 0; i < length; ++i){
            if (arr[i] < 0){
                parr[++parr[0]] = -arr[i];
            }else{
                narr[++narr[0]] = arr[i];
            }
        }
        sort_counting((unsigned int*)parr + 1, parr[0]);
        sort_counting((unsigned int*)narr + 1, narr[0]);
        int curIdx = 0;
        for(int i = parr[0]; i > 0 ; --i){
            arr[curIdx++] = -parr[i];
        }
        for(int i = 1; i <= narr[0] ; ++i){
            arr[curIdx++] = narr[i];
        }
        delete[] parr;
        delete[] narr;
    }else{
        sort_counting((unsigned int*)arr, length);
    }
}

//桶排序
void sort_bucket(int* arr, int length) {
    if (length <= 1) return;
    
    int minV = arr[0];
    int maxV = arr[0];
    for(int i = 1; i < length; ++i){
        if (arr[i] < minV){
            minV = arr[i];
        }else if (arr[i] > maxV){
            maxV = arr[i];
        }
    }
    
    const int BucketSize = 5;
    
    const int bucketCount = (maxV - minV) / BucketSize + 1;
    
    int** buckets = new int* [bucketCount];
    for (int i = 0; i < bucketCount; ++i){
        buckets[i] = new int[length + 1]();
    }
    
    for (int i = 0; i < length; ++i){
        int* curBucket = buckets[(arr[i] - minV) / BucketSize];
        curBucket[++curBucket[0]] = arr[i];
    }
    
    int curIdx = 0;
    for (int i = 0; i < bucketCount; ++i){
        if (buckets[i][0] <= 0) continue;
        sort_insert(buckets[i] + 1, buckets[i][0]);  // 使用插入排序对桶内数据进行排序
        for (int j = 1; j <= buckets[i][0]; ++j){
            arr[curIdx++] = buckets[i][j];
        }
    }
    
    delete[] buckets;
}

//基数排序
void sort_radix(unsigned int* arr, int length) {
    if (length <= 1) return;
    
    int maxDigit = 1;  //位数
    int p = 10;
    for(int i = 0; i < length; ++i){
        while(arr[i] >= p)
        {
            p *= 10;
            ++maxDigit;
        }
    }
    int i, j, k;
    int radix = 1;
    int* tmp = new int[length];
    int* count = new int[10];
    for (i = 1; i <= maxDigit; ++i){
        for (j = 0; j < 10; ++j)
            count[j] = 0;
        for (j = 0; j < length; ++j){
            k = (arr[j] / radix) % 10;
            count[k]++;
        }
        for (j = 1; j < 10; ++j)
            count[j] = count[j - 1] + count[j];
        for (j = length - 1; j >= 0; --j){
            k = (arr[j] / radix) % 10;
            tmp[--count[k]] = arr[j];
        }
        memcpy(arr, tmp, length * sizeof(int));
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;
}
void sort_radix(int* arr, int length){
    if (length <= 1) return;
    int pcount = 0;
    for (int i = 0; i < length; ++i){
        if (arr[i] < 0){
            pcount++;
        }
    }
    if (pcount > 0){
        int* parr = new int[pcount + 1]();
        int* narr = new int[length - pcount + 1]();
        for(int i = 0; i < length; ++i){
            if (arr[i] < 0){
                parr[++parr[0]] = -arr[i];
            }else{
                narr[++narr[0]] = arr[i];
            }
        }
        sort_radix((unsigned int*)parr + 1, parr[0]);
        sort_radix((unsigned int*)narr + 1, narr[0]);
        int curIdx = 0;
        for(int i = parr[0]; i > 0 ; --i){
            arr[curIdx++] = -parr[i];
        }
        for(int i = 1; i <= narr[0] ; ++i){
            arr[curIdx++] = narr[i];
        }
        delete[] parr;
        delete[] narr;
    }else{
        sort_radix((unsigned int*)arr, length);
    }
}


//主函数
int main() {
    int arr[] = {1, 2, 3, 34,734,233,0,543,31,23, -1, -4};
    int length = sizeof(arr) / sizeof(int);

    sort_maopao(arr, length);  //冒泡排序
    //sort_select(arr, length);  //选择排序
    //sort_insert(arr, length);  //插入排序
    //sort_shell(arr, length);  //希尔排序
    //sort_merge(arr, length);  //归并排序
    //sort_quick(arr, length);  //快速排序
    //sort_heap(arr, length);  //堆排序
    //sort_counting(arr, length);  //计数排序
    //sort_bucket(arr, length);  //桶排序
    //sort_radix(arr, length);  //基数排序

    for (int i = 0; i < length; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    system("pause");
    return 0;
}
