// dictionary.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include <map>
#include <sstream>
#include <string>

// Пример использования istringstream
// https://wandbox.org/permlink/p3N29JOqLCfeaM5N

using Dictionary = std::multimap<std::string, std::string>;

void PrintTranslations(Dictionary::const_iterator start,
                       Dictionary::const_iterator end) {
  std::cout << "Translations:\n";
  // i - итератор, указывающий на пару ключ-значение внутри [start, end)
  for (auto i = start; i != end; ++i) {
    // Привязываем к именам _ и translation элементы first и second пары, на
    // которые указывал итератор i
    auto& [_, translation] = *i;  // Либо так: auto& translation = i->second;
    std::cout << translation << "\n";
  }
  std::cout << "\n";
}

bool RequestTranslations(Dictionary& dictionary, const std::string& word) {
  std::cout << "Unknown word. Enter translations (comma-separated)"
            << "\n";
  std::string translations_string;
  if (!std::getline(std::cin, translations_string)) {
    return false;
  }
  std::istringstream translations(translations_string);
  std::string translation;
  while (std::getline(translations, translation, ',')) {
    dictionary.emplace(word, translation);
  }
  return true;
}

int main() {
  Dictionary dictionary;
  for (;;) {
    std::cout << "Enter word: ";
    std::string word;
    if (!std::getline(std::cin, word)) {
      break;
    }

    // [start, end) содержит все элементы с ключом word
    auto [start, end] = dictionary.equal_range(word);
    if (start != end) {
      PrintTranslations(start, end);
    } else if (!RequestTranslations(dictionary, word)) {
      // if (!RequestTranslations(dictionary, word) == false)
      break;
    }
  }
}

/*

Напишите программу "Самообучающийся словарь".
Пользователь вводит слово или словосочетание, а программа выводит переводы этого
слова (или словосочетания).
Если программа не знает такого слова или словосочетания, то просит пользователя
ввести переводы через запятую и запоминает их все.
Программа завершает диалог с пользователем и выходит после ввода символа конца
файла (Ctrl+Z).

Посмотрите диалог в программе animals (количество ног)
Можно использовать std::multimap<std::string, std::string>
Для поиска всех переводов используйте equal_range
https://en.cppreference.com/w/cpp/container/multimap/equal_range
В случае, если элементов нет, то equal_range возвращает пару итераторов,
указывающих на один и тот же элемент


Пример интерфейса:
Enter text:
cat
Translations:
кот
кошка

Enter text:
dog
Unknown word. Please enter translations (comma-separated):
собака,пёс

Enter text:
dog
Translations:
собака
пёс

Enter text:
lady bug
Unknown word. Please enter translations (comma-separated):
божья коровка,кокцинеллида

*/