#include <iostream>
#include <locale>
#include <string>
#include "modAlphaCipher.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wcout.imbue(locale("ru_RU.UTF-8"));
    wcin.imbue(locale("ru_RU.UTF-8"));

    wstring key, text;
    unsigned op;

    try {
        wcout << L"Введите ключ для шифра Гронсфельда: ";
        wcin >> key;
        
        modAlphaCipher cipher(key);
        wcout << L"Ключ успешно загружен.\n";

        do {
            wcout << L"\nВыберите операцию (0 - выход, 1 - зашифровать, 2 - расшифровать): ";
            wcin >> op;

            if (op > 2) {
                wcout << L"Недопустимая операция.\n";
                continue;
            }
            if (op == 0) break;

            wcout << L"Введите текст: ";
            wcin >> text;

            if (op == 1) {
                wcout << L"Зашифрованный текст: " << cipher.encrypt(text) << endl;
            } else {
                wcout << L"Расшифрованный текст: " << cipher.decrypt(text) << endl;
            }
        } while (op != 0);
    } 
    catch (const cipher_error& e) {
        wcerr << L"Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
