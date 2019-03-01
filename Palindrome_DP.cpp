#include<bits/stdc++.h>

using namespace std;

typedef long long int lli;

string word, reverse_word, aux;
vector <vector<lli>> matrix;
vector<vector<char>> matrix_aux;


// fazer funcao para reaproveitar codigo da build_palindrome;

vector<char> build_palindrome() {
    bool flag = false;
    int i, j;
    i = 0;
    j = aux.size() - 1;
    vector<char> palindrome;
    vector<char>::iterator it;

    for (int k = 0; k < aux.size(); k++) {
        palindrome.push_back(aux[k]);
    }
    while (i < j) {
        flag = false;
        if (palindrome[i] != palindrome[j]) {
            for (int k = 1; i != (j - k); k++) { // It traverses the vector until it verifies the positions i + 1 and j - 1
                if (palindrome[i + k] == palindrome[j]) {  // Insert Right
                    it = palindrome.begin(); // Start the iterator at the beginning of the vector
                    advance(it, j + 1); // Move iterator to palindrome position j + 1
                    palindrome.insert(it, palindrome[i]); // Insert "palindrome [i]" before position j + 1
                    i += 1;
                    flag = true;
                    break;
                } else if (palindrome[j - k] == palindrome[i]) {  // Insert Left
                    it = palindrome.begin(); // Start the iterator at the beginning of the vector
                    advance(it, i); // Move iterator to palindrome position i
                    palindrome.insert(it, palindrome[j]); // Insert "palindrome [j]" before position i
                    i += 1;
                    flag = true;
                    break;
                }
            }
            if (flag == false) {
                if(i == j - 1) { // Insert Right
                    it = palindrome.begin(); // Start the iterator at the beginning of the vector
                    advance(it, j + 1); // Move iterator to palindrome position j + 1
                    palindrome.insert(it, palindrome[i]); // Insert "palindrome [i]" before position j + 1
                    i += 1;
                } else { 
                    //Insert Right
                    it = palindrome.begin(); // Start the iterator at the beginning of the vector
                    advance(it, j + 1); // Move o it para a posição j + 1 do palindromo
                    palindrome.insert(it, palindrome[i]);// Insere "palindrome[i]" antes da posição j+1
                    // Insert Left
                    it = palindrome.begin();//Inicia o it no início do vector
                    advance(it, i + 1);// Move o it para a posição i + 1 do palindromo
                    palindrome.insert(it, palindrome[j]);// Insere "palindrome[j]" antes da posição i+1
                    i += 2;
                }
            }
        } else {
            i += 1;
            j -= 1;
        }
    }
    return palindrome;
}

/*  Given two strings, we will look for the largest substring
    common among them, using an array to save calculations
    already made for greater efficiency (dynamic programming) */

lli LCS(int i, int j) {
    /*  We checked if any string arrived at 0, because
        if it arrived there will be nothing more in common */
    if (i == 0 or j == 0) {
        return 0;
    } else if (word[i] == reverse_word[j]) {
        /*  If one letter equals another, it means that it should
            be present in our greater subsequence group, as soon as
            we include this letter in the solution */

        if (matrix[i][j] != -1) {
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
    cout << "Insert a string: ";
    int size;
    cin >> word;
    aux = word;
    size = word.size();
    reverse_word = word;
    reverse(reverse_word.begin(), reverse_word.end());
    word = "#" + word;
    reverse_word = "#" + reverse_word;
    matrix.resize(size + 1);
    matrix_aux.resize(size + 1);
    for (int i = 0; i < size + 1; i++) {
        matrix[i].resize(size + 1, -1);
        matrix_aux[i].resize(size + 1,'#');
    }
    
    LCS(size, size);
    lli minimum = size - matrix[size][size];
    // The result is the size of the string - size of the largest subsequence
    vector<char> palindrome = build_palindrome();
    cout << "Minimum number of characters to be inserted: " << minimum << endl;

    cout << "Palindrome: ";
    for (int k = 0; k < palindrome.size(); k++) {
        cout << palindrome[k];
    }
    cout << endl;
    cout << palindrome.size() << " - " << size << " = " << minimum << endl;
    return 0;
}
