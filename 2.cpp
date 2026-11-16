#include <iostream>
#include <string>
#include <set>
#include <codecvt>
#include <locale>

using namespace std;

int main() {
    string text;
    getline(cin, text);

    wstring_convert<codecvt_utf8<char32_t>, char32_t> cv;
    u32string input = cv.from_bytes(text);
    u32string word;
    set<u32string> words;

    auto addWord = [&]() {
        if (!word.empty()) {
            words.insert(word);
            word.clear();
        }
    };

    for (char32_t c : input) {
        bool latin = (c >= U'A' && c <= U'Z') ||
                     (c >= U'a' && c <= U'z');

        bool russian = (c >= U'А' && c <= U'я') ||
                       c == U'Ё' || c == U'ё';

        if (latin || russian) {
            if (c >= U'A' && c <= U'Z')
                c += 32;
            else if (c >= U'А' && c <= U'Я')
                c += 32;
            else if (c == U'Ё')
                c = U'ё';

            word += c;
        } else {
            addWord();
        }
    }

    addWord();

    cout << "Уникальные слова:\n";

    for (const auto& w : words)
        cout << cv.to_bytes(w) << endl;

    cout << "Всего: " << words.size() << endl;

    return 0;
}