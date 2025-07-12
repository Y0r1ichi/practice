#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool isPossible(const vector<int>& lengths, int Width, int X) {
    int lines = 1; 
    int currentWidth = lengths[0];  
    
    for (size_t i = 1; i < lengths.size(); ++i) {
        if (currentWidth + 1 + lengths[i] <= Width) {
            currentWidth += 1 + lengths[i];  
        } else {
            lines++;
            currentWidth = lengths[i];
            if (lines > X) {
                return false;
            }
        }
    }
    return true;
}

int findMinWidth(const vector<int>& lengths, int X) {
    int left = *max_element(lengths.begin(), lengths.end());
    
    int right = accumulate(lengths.begin(), lengths.end(), 0) + lengths.size() - 1;
    
    int result = right;  
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (isPossible(lengths, mid, X)) {
            result = mid;
            right = mid - 1; 
        } else {
            left = mid + 1;  
        }
    }
    return result;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    
    int N, X;
    input >> N >> X;
    
    vector<int> lengths(N);
    for (int i = 0; i < N; ++i) {
        input >> lengths[i];
    }
    
    int minWidth = findMinWidth(lengths, X);
    output << minWidth;
    
    return 0;
}