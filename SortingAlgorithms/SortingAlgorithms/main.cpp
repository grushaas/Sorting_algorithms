#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <algorithm>

int getRandomNumber(int min, int max) {
	// srand(time(NULL));

	int num = min + rand() % (max - min + 1);

	return num;
}

void printArr(unsigned int arr[], unsigned const int size) {
	for (int i = 0; i < size; i++) {
		std::cout << i << ": " << arr[i] << std::endl;
	}
}

void bubbleSort(unsigned int arr[], unsigned const int size) {
	long count = 0;
	srand(time(0));
	// double start_time = clock();
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				count++;
			}
		}
	}
	// double end_time = clock();
	// double deltaTime = end_time - start_time;

	std::cout << "Permutations: " << count << std::endl;
	std::cout << "Execution time: " << clock() / 1000.0 << std::endl;
}

void insertionSort(unsigned int arr[], unsigned const int size) {
	long count = 0;
	srand(time(0));

	for (int i = 1; i < size; ++i) {
		int tmp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > tmp) {
			arr[j + 1] = arr[j];
			arr[j] = tmp;
			j--;
			count++;
		}
	}

	std::cout << "Permutations: " << count << std::endl;
	std::cout << "Execution time: " << clock() / 1000.0 << std::endl;
}

int partition(unsigned int a[], int start, int end, unsigned long &count) {
	int pivot = a[end];
	int pIndex = start;

	for (int i = start; i < end; ++i) {
		if (a[i] <= pivot) {
			std::swap(a[i], a[pIndex]);
			pIndex++;
			count++;
		}
	}

	std::swap(a[pIndex], a[end]);

	return pIndex;
}

void quickSort(unsigned int a[], int start, int end, unsigned long &count) {
	srand(time(0));
	if (start >= end) {
		return;
	}

	int pivot = partition(a, start, end, count);
	quickSort(a, start, pivot - 1, count);
	quickSort(a, pivot + 1, end, count);

	
}

void choicesSort(unsigned int arr[], unsigned const int size, unsigned long &count) {
	for(int i = 0; i < size; ++i) {
		int temp = arr[0];
		for (int j = i + 1; j < size; j++) {
			if (arr[i] > arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;

				count++;
			}
		}
	}
}

void merge(int* arr[], int* left[], int leftSize, int* right[], int rightSize) {
	int i = 0, j = 0, k = 0;
	while (i < leftSize && j < rightSize) {
		if (left[i] <= right[j]) {
			arr[k++] = left[i++];
		}
		else {
			arr[k++] = right[j++];
		}
	}
	while (i < leftSize) {
		arr[k++] = left[i++];
	}
	while (j < rightSize) {
		arr[k++] = right[j++];
	}
}

//Доделать
void recursiveMergeSort(int* arr[], int left, int right) {
	if (left >= right) {
		return;
	}

	int mid = left + (right - left) / 2;
	recursiveMergeSort(arr, left, mid);
	recursiveMergeSort(arr, mid + 1, right);

	int* leftArr = new int[mid - left + 1];
	int* rightArr = new int[right - mid];

	for (int i = 0; i < mid - left; i++) {
		int* number = arr[left + i];
		leftArr[i] = number;
		leftArr[i] = arr[left + i];
	}
	for (int i = 0; i < right - mid; i++) {
		rightArr[i] = arr[mid + 1 + i];
	}
	merge(arr, &leftArr, mid - left + 1, &rightArr, right - mid);
}

int main() {
	unsigned const int size = 50;
	unsigned int arr[size];
	int* arrMerge = new int[size];
	unsigned long count = 0;

	// Заполнение массива рандомными числами
	for (int i = 0; i < size; ++i) {
		unsigned int number = getRandomNumber(1, 100);
		arr[i] = number;
	}

	std::cout << "Array before sorting: " << std::endl;
	printArr(arr, size);

	recursiveMergeSort(&arrMerge, 0, size - 1);
	std::cout << "Permutations: " << count << std::endl;
	std::cout << "Execution time: " << clock() / 1000.0 << std::endl;

	std::cout << "Array after sorting: " << std::endl;
	printArr(arr, size);

	return 0;
}