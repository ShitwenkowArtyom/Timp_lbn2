#include <iostream>
#include <locale>
#include <string>
#include <limits>
#include "modAlphaCipher.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wcout.imbue(locale("ru_RU.UTF-8"));
    wcin.imbue(locale("ru_RU.UTF-8"));

    wstring key, text;
    unsigned op;
    modAlphaCipher* cipher = nullptr;

    while (cipher == nullptr) {
        wcout << L"Введите ключ для шифра Гронсфельда (или нажмите Enter для пустого): ";
        getline(wcin, key);
        try {
            cipher = new modAlphaCipher(key);
            wcout << L"Ключ успешно загружен.\n";
        } catch (const cipher_error& e) {
            wcerr << L"Ошибка: " << e.what() << L". Попробуйте снова.\n";
        }
    }

    do {
        wcout << L"\nВыберите операцию (0 - выход, 1 - зашифровать, 2 - расшифровать): ";
        wcin >> op;

        if (wcin.fail()) {
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
            wcout << L"Ошибка: введено не число.\n";
            continue;
        }

        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

        if (op > 2) {
            wcout << L"Недопустимая операция.\n";
            continue;
        }
        if (op == 0) break;

        wcout << L"Введите текст: ";
        getline(wcin, text);

        try {
            if (op == 1) {
                wcout << L"Зашифрованный текст: " << cipher->encrypt(text) << endl;
            } else {
                wcout << L"Расшифрованный текст: " << cipher->decrypt(text) << endl;
            }
        } catch (const cipher_error& e) {
            wcerr << L"Ошибка при обработке текста: " << e.what() << endl;
        }
    } while (op != 0);

    delete cipher;
    return 0;
}

