#include "transpositionCipher.h"
#include <vector>
#include <cwctype>

using namespace std;

TranspositionCipher::TranspositionCipher(int key) {
    if (key <= 0) {
        throw cipher_error("Key must be positive");
    }
    if (key == 1) {
        throw cipher_error("Trivial transposition");
    }
    if (key > 10000) {
        throw cipher_error("Key is too large");
    }
    cols = key;
}

inline wstring TranspositionCipher::getValidText(const wstring& text) {
    if (text.empty()) {
        throw cipher_error("Empty text");
    }
    wstring tmp;
    for (auto c : text) {
        if (!iswprint(c)) {
            throw cipher_error("Non-printable character in text");
        }
        tmp.push_back(c);
    }
    if (tmp.empty()) {
        throw cipher_error("Empty text");
    }
    return tmp;
}

wstring TranspositionCipher::encrypt(const wstring& text) {
    wstring validText = getValidText(text);
    int s = validText.size();
    if (s == 0) return L"";
    
    if (s <= cols) {
        throw cipher_error("Useless transposition");
    }

    int rows = (s + cols - 1) / cols;
    vector<vector<wchar_t>> table(rows, vector<wchar_t>(cols, L' '));

    for (int i = 0; i < s; i++) {
        table[i / cols][i % cols] = validText[i];
    }

    wstring result;
    for (int j = cols - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (i * cols + j < s) {
                result += table[i][j];
            }
        }
    }
    return result;
}

wstring TranspositionCipher::decrypt(const wstring& text) {
    wstring validText = getValidText(text);
    int s = validText.size();
    if (s == 0) return L"";
    
    if (s <= cols) {
        throw cipher_error("Useless transposition");
    }

    int rows = (s + cols - 1) / cols;
    int full_rows = s / cols;
    int rem = s % cols;

    vector<vector<wchar_t>> table(rows, vector<wchar_t>(cols, L' '));
    vector<int> height(cols);
    
    for (int j = 0; j < cols; j++) {
        height[j] = full_rows + (j < rem ? 1 : 0);
    }

    int idx = 0;
    for (int j = cols - 1; j >= 0; j--) {
        for (int i = 0; i < height[j]; i++) {
            table[i][j] = validText[idx++];
        }
    }

    wstring result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i * cols + j < s) {
                result += table[i][j];
            }
        }
    }
    return result;
}

