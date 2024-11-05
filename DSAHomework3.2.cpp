#include <iostream>
#include <cmath>
#include <climits>

struct Point {
    int x, y;
};

// Function to calculate Euclidean distance
double dist(const Point &p1, const Point &p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute-force method for finding the closest pair in a small region
double bruteForce(Point points[], int left, int right) {
    double minDist = INT_MAX;
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j < right; ++j) {
            double distance = dist(points[i], points[j]);
            if (distance < minDist) {
                minDist = distance;
            }
        }
    }
    return minDist;
}

// Sort points by their y-coordinates in the strip region
void sortByY(Point strip[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strip[i].y > strip[j].y) {
                Point temp = strip[i];
                strip[i] = strip[j];
                strip[j] = temp;
            }
        }
    }
}

// Function to find the closest points in the strip
double stripClosest(Point strip[], int size, double d) {
    double minDist = d;
    sortByY(strip, size);
    
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; ++j) {
            double distance = dist(strip[i], strip[j]);
            if (distance < minDist) {
                minDist = distance;
            }
        }
    }
    return minDist;
}

// Main recursive function to find closest pair
double closestUtil(Point points[], int left, int right) {
    if (right - left <= 3) {
        return bruteForce(points, left, right);
    }

    int mid = left + (right - left) / 2;
    double dLeft = closestUtil(points, left, mid);
    double dRight = closestUtil(points, mid, right);
    double d = (dLeft < dRight) ? dLeft : dRight;

    // Build the strip array
    Point strip[1000]; // Arbitrary large size; replace with dynamic allocation for real use
    int stripSize = 0;
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - points[mid].x) < d) {
            strip[stripSize] = points[i];
            stripSize++;
        }
    }

    return (d < stripClosest(strip, stripSize, d)) ? d : stripClosest(strip, stripSize, d);
}

double closestPair(Point points[], int n) {
    // Sorting points by x-coordinates using simple bubble sort for demonstration
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (points[i].x > points[j].x) {
                Point temp = points[i];
                points[i] = points[j];
                points[j] = temp;
            }
        }
    }
    return closestUtil(points, 0, n);
}

int main() {
    Point points[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(points) / sizeof(points[0]);
    std::cout << "The smallest distance is " << closestPair(points, n) << std::endl;
    return 0;
}

