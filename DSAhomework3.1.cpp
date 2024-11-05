#include <iostream>
#include <cmath>

struct Point {
    double x, y;
};

struct KDNode {
    Point point;
    KDNode *left, *right;
    KDNode(Point pt) : point(pt), left(nullptr), right(nullptr) {}
};

double distance(const Point& a, const Point& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Custom quicksort function for sorting points by specified axis (0 for x, 1 for y)
void quicksort(Point points[], int start, int end, int axis) {
    if (start >= end) return;

    int pivotIndex = start + (end - start) / 2;
    Point pivot = points[pivotIndex];
    int left = start, right = end;

    while (left <= right) {
        while ((axis == 0 ? points[left].x : points[left].y) < (axis == 0 ? pivot.x : pivot.y)) {
            left++;
        }
        while ((axis == 0 ? points[right].x : points[right].y) > (axis == 0 ? pivot.x : pivot.y)) {
            right--;
        }
        if (left <= right) {
            std::swap(points[left], points[right]);
            left++;
            right--;
        }
    }

    if (start < right) quicksort(points, start, right, axis);
    if (left < end) quicksort(points, left, end, axis);
}

KDNode* buildKDTree(Point points[], int start, int end, int depth) {
    if (start > end) return nullptr;

    int axis = depth % 2;
    int mid = (start + end) / 2;

    // Use quicksort to partition points by the current axis
    quicksort(points, start, end, axis);

    KDNode* node = new KDNode(points[mid]);
    node->left = buildKDTree(points, start, mid - 1, depth + 1);
    node->right = buildKDTree(points, mid + 1, end, depth + 1);

    return node;
}

void nearestNeighborSearch(KDNode* root, const Point& target, int depth, KDNode*& best, double& bestDist) {
    if (!root) return;

    double d = distance(root->point, target);
    if (d < bestDist) {
        bestDist = d;
        best = root;
    }

    int axis = depth % 2;
    KDNode* next = (axis == 0 && target.x < root->point.x) || (axis == 1 && target.y < root->point.y) ? root->left : root->right;
    KDNode* other = (next == root->left) ? root->right : root->left;

    nearestNeighborSearch(next, target, depth + 1, best, bestDist);

    double diff = (axis == 0) ? fabs(target.x - root->point.x) : fabs(target.y - root->point.y);
    if (diff < bestDist) {
        nearestNeighborSearch(other, target, depth + 1, best, bestDist);
    }
}

Point nearestNeighbor(KDNode* root, const Point& target) {
    KDNode* best = nullptr;
    double bestDist = 1e9;  // Set an initial high value for distance
    nearestNeighborSearch(root, target, 0, best, bestDist);
    return best->point;
}

int main() {
    Point points[] = {{2.0, 3.0}, {5.0, 4.0}, {9.0, 6.0}, {4.0, 7.0}, {8.0, 1.0}, {7.0, 2.0}};
    int n = sizeof(points) / sizeof(points[0]);

    KDNode* root = buildKDTree(points, 0, n - 1, 0);

    Point target = {6.0, 2.0};
    Point nearest = nearestNeighbor(root, target);

    std::cout << "Nearest point to target: (" << nearest.x << ", " << nearest.y << ")\n";
    return 0;
}

