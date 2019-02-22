#include<bits/stdc++.h>

using namespace std;

typedef long long int lli;
string word, reverse_word;
vector <vector<lli>> matrix;

lli LCS (int i, int j) {
    if (i == 0 or j == 0) {
        matrix[i][j] = 0;
        return 0;
    } else if (word[i] == reverse_word[j]) {
        if (matrix[i][j] != - 1) {
            return matrix[i][j];
        } else {
            matrix[i][j] = 1 + LCS(i - 1, j - 1);
        }
    } else {
        if (matrix[i][j] != -1) {
            return matrix[i][j];
        } else {
            matrix[i][j] = max(LCS(i - 1, j), LCS(i, j - 1));
        }
    }
}

int main() {
    cout << "Insert a string: ";
    int size;
    cin >> word;
    size = word.size();
    reverse_word = word;
    reverse(reverse_word.begin(), reverse_word.end());
    word = "#" + word;
    reverse_word = "#" + reverse_word;
    matrix.resize(size + 1);
    for (int i = 0; i < size + 1; i++) {
        matrix[i].resize(size + 1, -1);
    }
    
    LCS(size, size);
    // for(int i = 0; i < matrix.size(); i++) {
    //     for(int j = 0; j < matrix[i].size(); j++) {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    lli minimum = size - matrix[size][size];
    // o resultado é o tamanho da string - tamanho da maior sub-string
    cout << "Minimum number of characters to be inserted: " << minimum << endl;
    return 0;
}