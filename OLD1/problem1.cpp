#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;

    string temp;
    cin >> temp; // reads the word "shuffled"
    cin.ignore(); // skip newline

    vector<string> shuffled(N);
    for (int i = 0; i < N; i++) {
        getline(cin, shuffled[i]);
    }

    cin >> temp; // reads the word "original"
    cin.ignore();

    vector<string> original(N);
    for (int i = 0; i < N; i++) {
        getline(cin, original[i]);
    }

    // map each instruction in original to its index
    unordered_map<string, int> position;
    for (int i = 0; i < N; i++) {
        position[original[i]] = i;
    }

    // convert shuffled list into their original indices
    vector<int> indices(N);
    for (int i = 0; i < N; i++) {
        indices[i] = position[shuffled[i]];
    }

    // find longest contiguous increasing subsequence
    int maxLen = 1, curLen = 1;
    for (int i = 1; i < N; i++) {
        if (indices[i] > indices[i - 1])
            curLen++;
        else
            curLen = 1;
        maxLen = max(maxLen, curLen);
    }

    // Minimum operations = N - longest increasing contiguous subsequence length
    cout << (N - maxLen) << endl;

    return 0;
}
