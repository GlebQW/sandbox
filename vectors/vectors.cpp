// vectors.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <vector>

std::vector<double> ReadNumbers() {
  std::vector<double> numbers;
  double number;
  while (std::cin >> number) {
    numbers.push_back(number);
  }
  return numbers;
}

template <typename ItemType>
void PrintVector(const std::vector<ItemType>& vector) {
  // for (const ItemType& item : vector) {
  for (auto& item : vector) {
    std::cout << item << ", ";
  }
  std::cout << "\n";
}

double CalcAverageOfPositives(const std::vector<double>& numbers) {
  double sum_of_positives = 0;
  size_t count_of_positives = 0;
  for (double number : numbers) {
    if (number > 0) {
      sum_of_positives += number;
      count_of_positives += 1;
    }
  }
  double average_of_positives = sum_of_positives / count_of_positives;
  return average_of_positives;
}

void AddNumberToEachItem(std::vector<double>& numbers, double number_to_add) {
  for (double& number : numbers) {
    number += number_to_add;
  }
}

/*
 * Возвращает минимальный элемент массива. Если масссив пуст, возвращает 0.0
 */
double FindMinElement(const std::vector<double>& numbers) {
  if (numbers.empty()) {
    return 0.0;
  }
  double min_element = numbers.front();
  for (double number : numbers) {
    if (number < min_element) {
      min_element = number;
    }
  }
  return min_element;
}

void MultiplyEachItemByNumber(std::vector<double>& numbers, double scale) {
  for (double& number : numbers) {
    number *= scale;
  }
}

void ProcessNumbers1(std::vector<double>& numbers) {
  double average_of_positives = CalcAverageOfPositives(numbers);
  AddNumberToEachItem(numbers, average_of_positives);
}

void ProcessNumbers2(std::vector<double>& numbers) {
#if 0
  double min_element = FindMinElement(numbers);
  MultiplyEachItemByNumber(numbers, min_element);
#else

  if (auto min_it = std::min_element(numbers.begin(), numbers.end());
      min_it != numbers.end()) {
    // *min_it возвращает ссылку на элемент, на который указывает итератор
    // min_it
    MultiplyEachItemByNumber(numbers, *min_it);
  }
#endif
}

int main() {
  std::vector<double> numbers = ReadNumbers();
  ProcessNumbers2(numbers);
  PrintVector(numbers);
}

/*
Ознакомьтесь с возможностями класса vector библиотеки STL, а также с основными
алгоритмами STL. Разработайте программу, выполняющую считывание массива чисел с
плавающей запятой, разделяемых пробелами, из стандартного потока ввода в vector,
обрабатывающую его согласно заданию Вашего варианта и выводящую в стандартный
поток полученный массив (разделенный пробелами). В программе должны быть
выделены функции, выполняющие считывание массива, его обработку  и вывод
результата.

1. Прибавить к каждому элементу массива среднее арифметическое его положительных
элементов. Если массив пустой, то не модифицировать массив.

2. Каждый элемент массива должен быть умножен на минимальный элемент исходного
массива. Если массив пустой, оставить его без изменений.

3. Умножить каждый отрицательный элемент массива на произведение максимального и
минимального элементов исходного массива. Если массив пуст, оставить его без
изменений.

4. Прибавить к каждому элементу массива сумму трех минимальных элементов
массива. Если в массиве меньше трёх элементов, то прибавить сумму имеюющихся
элементов. Если массив пустой, то оставить его без изменений

std::partial_sort - https://en.cppreference.com/w/cpp/algorithm/partial_sort
std::partial_sort_copy - https://en.cppreference.com/w/cpp/algorithm/partial_sort_copy
*/
