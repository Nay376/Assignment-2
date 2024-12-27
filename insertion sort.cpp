#include <iostream>
#include <vector>
using namespace std;

// Function to perform insertion sort
void insertionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key,
        // one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Function to display the array
void displayArray(const vector<int> &arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Main function
int main() {
    vector<int> arr = {12, 11, 13, 5, 6};

    cout << "Before Sorting: ";
    displayArray(arr);

    insertionSort(arr);

    cout << "After Sorting: ";
    displayArray(arr);

    return 0;
}
