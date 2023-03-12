// dictionary.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::string translations_string;
  std::cout << "Unknown word. Please enter translations (comma-separated):"
            << std::endl;

  if (!std::getline(std::cin, translations_string)) {
    // Пользователь ввёл Ctrl+Z
    return 0;
  }

  // Поток, который содержит содержимое строки и из которого можно считывать
  // данные точно так же как и из cin
  // https://en.cppreference.com/w/cpp/io/basic_istringstream
  std::istringstream translation_stream{translations_string};
  std::cout << "Words:" << std::endl;
  std::string word;  // слово или словосочетание
  while (std::getline(translation_stream, word, ',')) {
    std::cout << word << std::endl;
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