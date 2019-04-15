#include<iostream>
#include <algorithm>
using namespace std;

//Ã°ÅİÅÅĞò
void sort_maopao(int* arr, unsigned int length) {
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

//Ñ¡ÔñÅÅĞò
void sort_select(int* arr, unsigned int length) {
	unsigned int minIdx;
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

//²åÈëÅÅĞò
void sort_insert(int* arr, unsigned int length) {
	int curValue;
	unsigned int preIdx;

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

//Ï£¶ûÅÅĞò
void sort_shell(int* arr, unsigned int length) {
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

//¹é²¢ÅÅĞò
void merge(int* left, unsigned int l_len, int* right, unsigned int r_len, int * data) {
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
	delete temp;
}

void sort_merge(int* arr, unsigned int length) {
	unsigned int step = 1;
	while (step < length) {
		for (unsigned int i = 0; i < length - step; i += 2 * step) {
			merge(arr + i, step, arr + i + step, min(length - i - step, step), arr + i);
		}
		step *= 2;
	}
}

//¿ìËÙÅÅĞò
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
	
	for (int i = 0; i < length; ++i) {
		cout << arr[i] << " ";
	}
	cout << "\n";

	sort_quick(arr, j);
	sort_quick(arr + j + 1, length - j - 1);
}

//¶ÑÅÅĞò
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

//¼ÆÊıÅÅĞò
void sort_counting(int* arr, int length) {
	int max = INT_MIN;
	for (int i = 0; i < length; ++i) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	int* counts = new int[max + 1](); //³õÊ¼»¯Îª0
	
	for (int i = 0; i < length; ++i) {
		counts[arr[i]]++;
	}
	int curIdx = 0;
	for (int i = 0; i <= max; i++) {
		cout << i << " " << counts[i] << "\n";
		while (counts[i] > 0) {
			arr[curIdx++] = i;
			counts[i]--;
		}
	}
	delete counts;
}

//Í°ÅÅĞò
void sort_bucket(int* arr, int length) {
}

//»ùÊıÅÅĞò
void sort_radix(int* arr, int length) {
}

//Ö÷º¯Êı
int main() {
	int arr[] = {1, 2, 3, 34,734,233,0,543,31,23};
	unsigned int length = sizeof(arr) / sizeof(int);

	//sort_maopao(arr, length);  //Ã°ÅİÅÅĞò
	//sort_select(arr, length);  //Ñ¡ÔñÅÅĞò
	//sort_insert(arr, length);  //²åÈëÅÅĞò
	//sort_shell(arr, length);  //Ï£¶ûÅÅĞò
	//sort_merge(arr, length);  //¹é²¢ÅÅĞò
	//sort_quick(arr, length);  //¿ìËÙÅÅĞò
	//sort_heap(arr, length);  //¶ÑÅÅĞò
	//sort_counting(arr, length);  //¼ÆÊıÅÅĞò
	//sort_bucket(arr, length);  //Í°ÅÅĞò
	//sort_radix(arr, length);  //»ùÊıÅÅĞò

	for (int i = 0; i < length; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}
