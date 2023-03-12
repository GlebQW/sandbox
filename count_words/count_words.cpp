/// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь
/// начинается и заканчивается выполнение программы.
//

// count_words.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

/*
Программа должна подсчитать количество вхождений каждого слова в текст, вводимый
из std::cin.
Ввод продолжается, пока не будет встречен символ конца файла.
После этого программа должна вывести частоту введённых слов по одному в строке в
алфавитном порядке Например, был введён текст "to be or not to be".
Программа должна вывести:
be: 2
not: 1
or: 1
to: 2
*/
void Print(const std::map<std::string, int>& map) {
  for (auto& [key, value] : map) {
    std::cout << key << ": " << value << "\n";
  }
}

// Атрибут [[nodiscard]] (требует C++ 17) говорит, что возвращаемое значение
// функции должно быть использовано (сохранено или передано дальше). Компилятор
// выдаст предупреждение, если оно использовано не будет
[[nodiscard]] std::string StrToLower(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return s;
}

int main() {
  // 1. Считывать слова и подсчитывать их количество
  // 2. Вывести частоту встречаемости слов
  // int n = 1;
  std::map<std::string, int> count_words;

  std::string word;

  std::cout << "Write any words and press Ctrl+Z to finish:" << std::endl;
  while (std::cin >> word) {
#if 0
    StrToLower(word); // Выдаст предупреждение
#endif
    count_words[StrToLower(word)]++;
  }
  Print(count_words);
}
