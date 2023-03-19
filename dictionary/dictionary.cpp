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

    // Диапазон [start, end) содержит все элементы с ключом word
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

Дополнительные требоваиня:

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