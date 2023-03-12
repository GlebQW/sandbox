// multimap.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include <map>

enum class AnimalType {
  MAMMAL,  // 0
  BIRD,    // 1
  FISH,    // 2
  INSECT,  // 3
  SPIDER,  // 4
};

void PlayWithMap() {
  std::map<std::string, AnimalType> animal_types;
  animal_types["cat"] = AnimalType::MAMMAL;
  // Вставляет пару "dog"/AnimalType::MAMMAL
  animal_types.insert({"dog", AnimalType::MAMMAL});
  // Создаёт элемент из ключа и значения
  animal_types.emplace("eagle", AnimalType::BIRD);

  // insert возвращает пару: итератор на элемент с этим ключом и bool (была ли
  // вставка)
  auto insertion_result = animal_types.insert({"eagle", AnimalType::FISH});
  std::cout << "Eagle has been inserted: " << std::boolalpha
            << insertion_result.second << std::endl;
  std::cout << insertion_result.first->first << ": "
            << static_cast<int>(insertion_result.first->second) << std::endl;

  auto [iter, inserted] = animal_types.emplace("spider", AnimalType::SPIDER);
  std::cout << "Spider has been inserted: " << inserted << std::endl;
  // *iter возвращает ссылку на объект, на который ссылаетя итератор iter
  // в нашем случае - на элемент map, то есть на пару ключ-значение
  // С помощью structured binding
  // (https://en.cppreference.com/w/cpp/language/structured_binding) привязываем
  // элементы этой пары к именам name и type
  auto& [name, type] = *iter;
  std::cout << name << ": " << static_cast<int>(type) << std::endl;
}

void PrintMultimap(const std::multimap<std::string, int>& multimap) {
  for (auto& [key, value] : multimap) {
    std::cout << key << ":" << value << " birth year"
              << "\n";
  }
}

// https://en.cppreference.com/w/cpp/container/multimap
void PlayWithMultimap() {
  std::multimap<std::string, int> student_birth_year;

  student_birth_year.emplace("Kuvshinov", 2004);
  student_birth_year.emplace("Malov", 1981);
  student_birth_year.emplace("Kuvshinov", 2023);
  PrintMultimap(student_birth_year);

  auto [start, end] = student_birth_year.equal_range("Kuvshinov");
  for (auto i = start; i != end; ++i) {
    auto& [name, birth_year] = *i;
    std::cout << name << ": " << birth_year << '\n';
  }
}

int main() { PlayWithMultimap(); }
