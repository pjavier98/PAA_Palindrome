#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long int lli;
string word, reverse_word;
vector <vector<lli>> matrix;
 
/*  Given two strings, we will look for the largest substring
    common among them, using an array to save calculations
    already made for greater efficiency (dynamic programming) */
 
lli LCS (int i, int j) {
    /*  We checked if any string arrived at 0, because
        if it arrived there will be nothing more in common */
    if (i == 0 or j == 0) { 
        return 0;
    } else if (word[i] == reverse_word[j]) { 
        /*  If one letter equals another, it means that it should
            be present in our greater subsequence group, as soon as
            we include this letter in the solution */

        if (matrix[i][j] != - 1) {
            // If we already have the answer in the matrix we return it 
            return matrix[i][j];
        } else {
            // If no we call the function recursively to seek the subsequence
            matrix[i][j] = 1 + LCS(i - 1, j - 1);
        }
    } else {
        /*  If one letter is different from the other, we should seek the
            common maximum between the two string decreasing the first
            string and keeping the second and decrementing the second string
            and keeping the first */
        if (matrix[i][j] != -1) {
            // If we already have the answer in the matrix we return it
            return matrix[i][j];
        } else {
            // If no we call the function recursively to seek the subsequence
            matrix[i][j] = max(LCS(i - 1, j), LCS(i, j - 1)); 
        }
    }
}
 
int main() {
    int size;
    cout << "Insert a string: ";
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
    // The result is the size of the string - size of the largest subsequence
    lli minimum = size - matrix[size][size];
    cout << "Minimum number of characters to be inserted: " << minimum << endl;
    return 0;
}
