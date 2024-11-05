#include <iostream>

bool searchAttempt() {
    // Simulate search operation - in reality, replace this with actual search code
    static int attempt = 0;
    ++attempt;
    return attempt >= 5; // Simulate success on the 5th attempt
}

void searchWithExponentialBackoff(int maxRetries) {
    int attempt = 0;
    int baseDelay = 1; // initial delay

    while (attempt < maxRetries) {
        if (searchAttempt()) {
            std::cout << "Search successful on attempt " << attempt + 1 << std::endl;
            return;
        }

        int delay = baseDelay * (1 << attempt); // Exponential backoff using bitwise shift
        std::cout << "Attempt " << attempt + 1 << " failed. Retrying in " << delay << " units of time...\n";
        
        // Simulating delay with a loop instead of thread sleep
        for (int i = 0; i < delay * 1000000; ++i); // Adjust the multiplier to control delay duration

        ++attempt;
    }
    std::cout << "Search failed after " << maxRetries << " attempts.\n";
}

int main() {
    int maxRetries = 10;
    searchWithExponentialBackoff(maxRetries);
    return 0;
}

