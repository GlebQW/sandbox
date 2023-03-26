// dictionary.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <fstream>
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

enum class RequestTranslationResult {
  EXIT_REQUESTED,
  TRANSLATION_WAS_ADDED,
  TRANSLATION_WAS_NOT_ADDED,
};

RequestTranslationResult RequestTranslations(Dictionary& dictionary,
                                             const std::string& word) {
  std::cout << "Unknown word. Enter translations (comma-separated)"
            << "\n";
  std::string translations_string;
  if (!std::getline(std::cin, translations_string)) {
    return RequestTranslationResult::EXIT_REQUESTED;
  }

  std::istringstream translations(translations_string);
  std::string translation;
  bool translation_was_added = false;
  while (std::getline(translations, translation, ',')) {
    dictionary.emplace(word, translation);
    translation_was_added = true;
  }

  return translation_was_added
             ? RequestTranslationResult::TRANSLATION_WAS_ADDED
             : RequestTranslationResult::TRANSLATION_WAS_NOT_ADDED;
}

/*
   Переводит строки, вводимые пользователем.
   Возвращает true, если в словарь были внесены изменения и
   false, если изменения не были внесены
*/
[[nodiscard]] bool TranslateUserInput(Dictionary& dictionary) {
  bool has_changes = false;
  for (;;) {
    std::cout << "Enter word: ";
    std::string word;
    if (!std::getline(std::cin, word) || word == "...") {
      break;
    }

    // Диапазон [start, end) содержит все элементы с ключом word
    auto [start, end] = dictionary.equal_range(word);
    if (start != end) {
      PrintTranslations(start, end);
    } else {
      switch (RequestTranslations(dictionary, word)) {
        case RequestTranslationResult::EXIT_REQUESTED:
          return has_changes;
        case RequestTranslationResult::TRANSLATION_WAS_ADDED:
          has_changes = true;
          break;
        case RequestTranslationResult::TRANSLATION_WAS_NOT_ADDED:
          // Пользователь решил не вводить переводы и это нормально
          break;
      }
    }
  }
  return has_changes;
}

Dictionary ReadDictionary(const std::string& file_name) {
  Dictionary dictionary;
  //объявить ifstream, открыть файл
  //считывать построчно и из каждой строки извлечь слово и перевод
  //добавить слово и перевод в словарь
  std::ifstream dictionary_file;
  dictionary_file.open(file_name);

  for (std::string line; std::getline(dictionary_file, line);) {
    // либо std::string::npos
    // чтобы можно было писать if (<объявление переменной>; <проверка условия>)
    // для проекта нужно включить поддержку C++ 17 или выше
    if (size_t colon_pos = line.find(':');  //
        colon_pos != line.npos && colon_pos != 0 &&
        colon_pos != line.size() - 1) {
      std::string word = line.substr(0, colon_pos);
      std::string translation = line.substr(colon_pos + 1);
      dictionary.emplace(word, translation);
    }
  }

  return dictionary;
}

void SaveDictionary(const Dictionary& dictionary,
                    const std::string& file_name) {
  std::ofstream dictionary_file;
  dictionary_file.open(file_name);
  for (auto& [word, translation] : dictionary) {
    dictionary_file << word << ':' << translation << '\n';
  }
}

std::string RequestDictionaryFileName() {
  std::cout << "Enter dictionary file name: ";
  std::string file_name;
  std::getline(std::cin, file_name);
  return file_name;
}

int main() {
  /*
   * Запросить имя файла словаря
   * Если оно не пустое, то загрузить словарь из файла.
   * Если пустое, то начать с пустого словаря
   */

  Dictionary dictionary;

  std::string file_name = RequestDictionaryFileName();
  if (!file_name.empty()) {
    dictionary = ReadDictionary(file_name);
  }

  if (TranslateUserInput(dictionary)) {
    // Do you want to save your changes (y/n)?
    std::cout << " Do you want to save your changes (y/n)?";

    if (file_name.empty()) {
      file_name = RequestDictionaryFileName();
    }
    if (!file_name.empty()) {
      SaveDictionary(dictionary, file_name);
    }
  }

  /*
   * Если в словарь были внесены изменения, то
   *     Если имя файла было указано, то сохранить словарь в файл
   *     Если имя не было указано, то спросить имя и сохранить в файл
   * Если не были внесены изменения, то просто завершить работу
   */
}

/*

Дополнительные требования:

Программа при старте должна запросить имя файла словаря. Если пользователь ввёл
пустую строку в качестве имени файла, то программа должна начать с пустого
словаря. Если пользователь ввёл непустое имя, то программа должна прочитать с
диска файл с переводами. Формат файла вы выбираете сами.
Самый простой вариант - обычный текстовый файл, в котором хранятся пары
слово-перевод, разделённые двоеточием или другим удобным символом apple:яблоко
cat:кот
dog:пёс
dog:собака
the red square:красная площадь

Если пользователь вместо слова для перевода ввёл ..., то программа должна
завершить ввод слов для перевода. Перед выходом программа должна спросить, хочет
ли пользователь сохранить в файл словарь, если в процессе диалога в словарь были
добавлены новые слова.
Если пользователь согласен, то надо сохранить словарь в файл с введённым при
старте программы именем, а если при старте пользователь ввёл пустое имя файла,
то надо спросить имя файла и сохранить содержимое словаря в этот файл.

Пример диалога:
Enter dictionary file name:
<пользователь вводит пустую строку>
Enter word:
cat
Unknown word. blablabla
кот,кошка

Enter word:
cat
Translations:
кот
кошка

Enter word:
...
Do you want to save your changes (y/n)?
y
Enter dictionary file name:
dictionary.txt
<программа сохраинла и вышла>

Следующий запуск:
Enter dictionary file name:
dictionary.txt
Enter word:
cat
Translations:
кот
кошка

Enter word:
...
<программа выходит, не спрашивая про сохранение изменений, так как в словарь не
вносились новые слова>


#include <fstream> // для работы с файловыми потоками

string file_name = "dictionary.txt";
// открывает файл для чтения (ifstream - input file stream)
ifstream input_file(file_name);
можно работать с ним как с cin:
std::string word_and_translation_str;
std::getline(input_file, word_and_translation_str);
дальше из word_and_translation_str можно считать слово и перевод с помощью
istringstream


// открывает файл для записи (ofstream - output file stream)
ofstream output_file(file_name);
output_file << word << ":" << translation << "\n";
https://en.cppreference.com/w/cpp/io/basic_ifstream
https://en.cppreference.com/w/cpp/io/basic_ofstream
Примеры:
https://github.com/alexey-malov/oop/blob/master/samples/01-basics/input-output/main.cpp

*/

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