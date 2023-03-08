// animals.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>
#include <map>
#include <string>

/*
 * ��������� �� ����������� ������, ����� �� ���������� ������ ���������.
 */
void Print(const std::map<std::string, int>& map) {
#if 0
  for (const std::pair<std::string, int>& key_and_value : map) {
    std::cout << key_and_value.first << ": " << key_and_value.second << "\n";
  }
#endif

#if 0
  for (auto& key_and_value : map) {
    std::cout << key_and_value.first << ": " << key_and_value.second << "\n";
  }
#endif

  /*
  ������ ����� ����� ���������� � ����� �� ����� key, � � �������� - �� �����
  value
  */
  for (auto& [key, value] : map) {
    std::cout << key << ": " << value << "\n";
  }
}

int main() {
  // animal_legs - �������, ��� ������ (��������� ��������)
  // ������������� �������� (���������� ���)
  // ���������� �������� ��������� �� ���������� ���
  std::map<std::string, int> animal_legs;

  // ����������� �������� 4 �������� � ������ "cow"
  animal_legs["cow"] = 4;
  animal_legs["dog"] = 4;
  animal_legs["chicken"] = 2;
  animal_legs["spider"] = 8;
  animal_legs["bee"] = 6;

#if 0
  Print(animal_legs);
#endif

  for (;;) {
    std::string name;
    std::cout << "Enter animal name or empty line to exit: ";
    std::getline(std::cin, name);
    if (name.empty()) {
      break;
    }

    // ����� find ���������� �������� �� ������� � �������� ������, ����
    // �������� ������ end, ���� ������ �������� ���
    // https://en.cppreference.com/w/cpp/container/map/find

    if (auto it = animal_legs.find(name); it != animal_legs.end()) {
      // �������� �������
      std::cout << name << " has " << it->second << " legs\n";
    } else {
      // �������� �� �������
      std::cout << "How many legs does " << name << " have?\n";
      std::string num_legs_str;
      std::getline(std::cin, num_legs_str);
      int num_legs = std::stoi(num_legs_str);
      animal_legs[name] = num_legs;
    }
  }
}
