#include<bits/stdc++.h>

using namespace std;

typedef long long int lli;

string phrase, reverse_phrase, aux;
vector< vector < lli > > matrix;
vector< vector < char > > matrix_aux;
vector< char > palindrome;
vector< lli > spaces;

vector <char> insert_space(vector<char> palindrome, int a) {
    vector<char>::iterator it;
    it = palindrome.begin(); // Start the iterator at the beginning of the vector
    advance(it, a); // Move iterator to palindrome position a
    palindrome.insert(it, ' '); // Insert "letter" before position a
    return palindrome;
}

vector<char> insert_letter(int a, char letter) {
    vector<char>::iterator it;
    it = palindrome.begin(); // Start the iterator at the beginning of the vector
    advance(it, a); // Move iterator to palindrome position a
    palindrome.insert(it, letter); // Insert "letter" before position a
    for(int i = 0; i < spaces.size(); i++) {
        if(spaces[i] >= a) {
            spaces[i] += 1;
        }
    }
    return palindrome;
}

vector<char> build_palindrome() {
    bool flag = false;
    int i, j;
    i = 0;
    j = aux.size() - 1;
    
    for (int k = 0; k < aux.size(); k++) {
        palindrome.push_back(aux[k]);
    }
    while (i < j) {
        flag = false;
        if (palindrome[i] != palindrome[j]) {
            for (int k = 1; i != (j - k); k++) { // It traverses the vector until it verifies the positions i + 1 and j - 1
                if (palindrome[i + k] == palindrome[j]) {  // Insert Right
                    palindrome = insert_letter(j + 1, palindrome[i]);
                    i += 1;
                    flag = true;
                    break;
                } else if (palindrome[j - k] == palindrome[i]) {  // Insert Left
                    palindrome = insert_letter(i, palindrome[j]);
                    i += 1;
                    flag = true;
                    break;
                }
            }
            if (flag == false) {
                if(i == j - 1) { // Insert Right
                    palindrome = insert_letter(j + 1, palindrome[i]);
                    i += 1;
                } else { 
                    //Insert Right
                    palindrome = insert_letter(j + 1, palindrome[i]);
                    // Insert Left
                    palindrome = insert_letter(i + 1, palindrome[j]);
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
    } else if (phrase[i] == reverse_phrase[j]) {
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
    string phrase_aux;
    getline(cin, phrase_aux);
    for(int i = 0; i < phrase_aux.size(); i++) {
        if(phrase_aux[i] != ' ') {
            phrase.push_back(phrase_aux[i]);
        } else {
            spaces.push_back(i);
        }
    }
    aux = phrase;
    size = phrase.size();
    reverse_phrase = phrase;
    reverse(reverse_phrase.begin(), reverse_phrase.end());
    phrase = "#" + phrase;
    reverse_phrase = "#" + reverse_phrase;
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
    for(int i = 0; i < spaces.size(); i++) {
        palindrome = insert_space(palindrome, spaces[i]);
    }
    cout << "Minimum number of characters to be inserted: " << minimum << endl;

    cout << "Palindrome: ";
    for (int k = 0; k < palindrome.size(); k++) {
        cout << palindrome[k];
    }
    cout << endl;
    return 0;
}
