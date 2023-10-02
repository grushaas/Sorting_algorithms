#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <algorithm>

// Получение рандомных чисел
int getRandomNumber(int min, int max) {
	// srand(time(NULL));

	int num = min + rand() % (max - min + 1);

	return num;
}

// Вывод массива
void printArr(int arr[], const int size) {
	for (int i = 0; i < size; i++) {
		std::cout << i << ": " << arr[i] << std::endl;
	}
}

// Пузырьковая сортировка
void bubbleSort(int arr[], const int size, long long &count) {
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
}

void insertionSort(int arr[], const int size, long long& count) {
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
}

int partition(int a[], int start, int end, long long &count) {
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

void quickSort(int a[], int start, int end, long long &count) {
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

void merge(int array[], int const left, int const mid, int const right, long long &count) {
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0,
		indexOfSubArrayTwo = 0;

	int indexOfMergedArray = left;

	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
			++count;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
			++count;
		}
		indexOfMergedArray++;
	}

	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
		++count;
	}

	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
		++count;
	}
}

void mergeSort(int array[], int const begin, int const end, long long &count) {
	if (begin >= end)
		return;

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid, count);
	mergeSort(array, mid + 1, end, count);
	merge(array, begin, mid, end, count);
}

void sheakerSort(int* mass, int size, long long &count) {
	int left = 0, right = size - 1;
	int flag = 1;
	while ((left < right) && flag > 0) {
		flag = 0;
		for (int i = left; i < right; i++) {
			if (mass[i] > mass[i + 1]) {
				double t = mass[i];
				mass[i] = mass[i + 1];
				mass[i + 1] = t;
				flag = 1;
				++count;
			}
		}
		right--;
		for (int i = right; i > left; i--) {
			if (mass[i - 1] > mass[i]) {
				double t = mass[i];
				mass[i] = mass[i - 1];
				mass[i - 1] = t;
				flag = 1;
				++count;
			}
		}
		left++;
	}
}

void swap(int* xp, int* yp, long long &count) {
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
	++count;
}

void selectionSort(int arr[], int n, long long &count) {
	int i, j, min_idx;
	for (i = 0; i < n - 1; i++) { 
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;
		swap(&arr[min_idx], &arr[i], count);
	}
}


int main() {
	const int size = 100000;
	int arr[size];
	int* arrMerge = new int[size];
	long long count = 0;

	// Заполнение массива рандомными числами
	for (int i = 0; i < size; ++i) {
		unsigned int number = getRandomNumber(1, 100000);
		arr[i] = number;
	}

	std::cout << "Array before sorting: " << std::endl;
	printArr(arr, size);

	sheakerSort(arr, size, count);
	
	std::cout << "Array after sorting: " << std::endl;
	printArr(arr, size);

	std::cout << "Permutations: " << count << std::endl;
	std::cout << "Execution time: " << clock() / 1000.0 << std::endl;

	return 0;
}