#include <iostream>
#include <random>

using namespace std;

void merge(int* array, int start, int mid, int end);
void divide(int* array, int start, int end);

int main() {
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<int> distr(1, 100);
    int size = 100;
    int* array = new int[size];
    for (int i = 0; i < size; ++i) {
        int randomNum = distr(eng);
        array[i] = randomNum;
        cout << array[i] << " ";
    }
    cout << endl;

    divide(array, 0, size-1);

    cout << "Sorted array: ";
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }

    return 0;
}

void merge(int* array, int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int* left = new int[n1];
    int* right = new int[n2];

    for (int i = 0; i < n1; i++)
        left[i] = array[start + i];
    for (int j = 0; j < n2; j++)
        right[j] = array[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = start;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        }
        else {
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = right[j];
        j++;
        k++;
    }

    delete[] left;
    delete[] right;
}

void divide(int* array, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        divide(array, start, mid);
        divide(array, mid + 1, end);
        merge(array, start, mid, end);
    }
}