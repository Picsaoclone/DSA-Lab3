//22520468
//Nguyen Huy Hoang
//Session 03 
#include <iostream>
#include <string>
#include <cmath>

// Function prototypes for each exercise
int binarySearchFirst(int arr[], int size, int target);
int binarySearchLast(int arr[], int size, int target);
int countOccurrences(int arr[], int size, int target);

int jumpSearch(int arr[], int size, int target);

int interpolationSearch(std::string arr[], int size, const std::string& target);

int findMissingNumber(int arr[], int size);

int bidirectionalBinarySearch(int arr[], int size, int target);

void swap(int &a, int &b);
int partition(int arr[], int low, int high);
int quickSelect(int arr[], int low, int high, int k);
int kthSmallest(int arr[], int size, int k);

void linearSearch(int arr[], int size, int target, int &comparisons);
void binarySearch(int arr[], int size, int target, int &comparisons);

int main() {
    int choice;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Count Occurrences Using Binary Search\n";
        std::cout << "2. Dynamic Step Size Jump Search\n";
        std::cout << "3. Interpolation Search for Strings\n";
        std::cout << "4. Find Missing Number Using Binary Search\n";
        std::cout << "5. Multi-Search System (Linear and Binary)\n";
        std::cout << "6. Bidirectional Binary Search\n";
        std::cout << "7. Kth Smallest Element Using Binary Search\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int size, target;
                std::cout << "Enter the size of the array: ";
                std::cin >> size;
                int arr[size];
                std::cout << "Enter " << size << " sorted elements: ";
                for (int i = 0; i < size; i++) std::cin >> arr[i];
                std::cout << "Enter target to count occurrences: ";
                std::cin >> target;
                int count = countOccurrences(arr, size, target);
                std::cout << "Count of " << target << " is: " << count << "\n";
                break;
            }
            case 2: {
                int size, target;
                std::cout << "Enter the size of the array: ";
                std::cin >> size;
                int arr[size];
                std::cout << "Enter " << size << " sorted elements: ";
                for (int i = 0; i < size; i++) std::cin >> arr[i];
                std::cout << "Enter target to find using Jump Search: ";
                std::cin >> target;
                int index = jumpSearch(arr, size, target);
                if (index != -1)
                    std::cout << "Found at index: " << index << "\n";
                else
                    std::cout << "Not found\n";
                break;
            }
            case 3: {
                int size;
                std::cout << "Enter the number of strings: ";
                std::cin >> size;
                std::string arr[size];
                std::cout << "Enter " << size << " lexicographically sorted strings: ";
                for (int i = 0; i < size; i++) std::cin >> arr[i];
                std::string target;
                std::cout << "Enter target string to search: ";
                std::cin >> target;
                int index = interpolationSearch(arr, size, target);
                if (index != -1)
                    std::cout << "Found at index: " << index << "\n";
                else
                    std::cout << "Not found\n";
                break;
            }
            case 4: {
                int size;
                std::cout << "Enter the size of the array (excluding missing number): ";
                std::cin >> size;
                int arr[size];
                std::cout << "Enter " << size << " sorted elements with one missing (0 to n): ";
                for (int i = 0; i < size; i++) std::cin >> arr[i];
                int missing = findMissingNumber(arr, size);
                std::cout << "Missing number is: " << missing << "\n";
                break;
            }
            case 5: {
                int size, target;
                std::cout << "Enter the size of the array: ";
                std::cin >> size;
                int arr[size];
                std::cout << "Enter " << size << " sorted elements: ";
                for (int i = 0; i < size; i++) std::cin >> arr[i];
                std::cout << "Enter target to search: ";
                std::cin >> target;

                // Simulate "multi-threading" by running both searches sequentially and counting comparisons
                int linearComparisons = 0, binaryComparisons = 0;
                linearSearch(arr, size, target, linearComparisons);
                binarySearch(arr, size, target, binaryComparisons);

                std::cout << "Linear Search Comparisons: " << linearComparisons << "\n";
                std::cout << "Binary Search Comparisons: " << binaryComparisons << "\n";
                break;
            }
            case 6: {
                int size, target;
                std::cout << "Enter the size of the array: ";
                std::cin >> size;
                int arr[size];
                std::cout << "Enter " << size << " sorted elements: ";
                for (int i = 0; i < size; i++) std::cin >> arr[i];
                std::cout << "Enter target to find using Bidirectional Binary Search: ";
                std::cin >> target;
                int index = bidirectionalBinarySearch(arr, size, target);
                if (index != -1)
                    std::cout << "Found at index: " << index << "\n";
                else
                    std::cout << "Not found\n";
                break;
            }
            case 7: {
                int size, k;
                std::cout << "Enter the size of the array: ";
                std::cin >> size;
                int arr[size];
                std::cout << "Enter " << size << " unsorted elements: ";
                for (int i = 0; i < size; i++) std::cin >> arr[i];
                std::cout << "Enter k to find kth smallest element: ";
                std::cin >> k;
                if (k > 0 && k <= size) {
                    int result = kthSmallest(arr, size, k);
                    std::cout << "The " << k << "th smallest element is: " << result << "\n";
                } else {
                    std::cout << "Invalid k\n";
                }
                break;
            }
            case 8:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}

// Linear Search with comparison count
void linearSearch(int arr[], int size, int target, int &comparisons) {
    for (int i = 0; i < size; i++) {
        comparisons++;
        if (arr[i] == target) {
            std::cout << "Linear Search: Found at index " << i << "\n";
            return;
        }
    }
    std::cout << "Linear Search: Not found\n";
}

// Binary Search with comparison count
void binarySearch(int arr[], int size, int target, int &comparisons) {
    int low = 0, high = size - 1;
    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            std::cout << "Binary Search: Found at index " << mid << "\n";
            return;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    std::cout << "Binary Search: Not found\n";
}

// Implement other functions here (e.g., countOccurrences, jumpSearch, etc.)


int binarySearchFirst(int arr[], int size, int target) {
    int low = 0, high = size - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int binarySearchLast(int arr[], int size, int target) {
    int low = 0, high = size - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            low = mid + 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int countOccurrences(int arr[], int size, int target) {
    int first = binarySearchFirst(arr, size, target);
    if (first == -1) return 0;
    int last = binarySearchLast(arr, size, target);
    return last - first + 1;
}

// Exercise 2: Jump Search
int jumpSearch(int arr[], int size, int target) {
    int step = std::sqrt(size);
    int prev = 0;
    while (arr[std::min(step, size) - 1] < target) {
        prev = step;
        step += std::sqrt(size);
        if (prev >= size) return -1;
    }
    for (int i = prev; i < std::min(step, size); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// Exercise 3: Interpolation Search for Strings
int interpolationSearch(std::string arr[], int size, const std::string& target) {
    int low = 0, high = size - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) return (arr[low] == target) ? low : -1;
        int pos = low + (target.compare(arr[low]) * (high - low)) / (arr[high].compare(arr[low]));
        if (arr[pos] == target) return pos;
        if (arr[pos] < target) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

// Exercise 4: Find Missing Number Using Binary Search
int findMissingNumber(int arr[], int size) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == mid) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

// Exercise 5: Bidirectional Binary Search
int bidirectionalBinarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        if (arr[low] == target) return low;
        if (arr[high] == target) return high;
        low++;
        high--;
    }
    return -1;
}

// Exercise 6: Kth Smallest Element Using Binary Search
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

int quickSelect(int arr[], int low, int high, int k) {
    if (low <= high) {
        int pi = partition(arr, low, high);
        if (pi == k) return arr[pi];
        else if (pi < k) return quickSelect(arr, pi + 1, high, k);
        else return quickSelect(arr, low, pi - 1, k);
    }
    return -1;
}

int kthSmallest(int arr[], int size, int k) {
    return quickSelect(arr, 0, size - 1, k - 1);
}

