#pragma once
#include <string>
#include <stdexcept>

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};

class TranspositionCipher {
private:
    int cols;
    std::wstring getValidText(const std::wstring& text);

public:
    TranspositionCipher() = delete;
    TranspositionCipher(int key);
    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& text);
};
