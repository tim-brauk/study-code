#include <iostream>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main() {
    int arr[] = {64, 25, 12, 22};
    int n = 4;

    std::cout << "Start:    ";
    printArray(arr, n);

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;

        std::cout << "Schritt " << i << ": ";
        printArray(arr, n);
    }

    return 0;
}

/*
Unterschiede
*/