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
 * ���������� ����������� ������� �������. ���� ������� ����, ���������� 0.0
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

double FindMaxElement(const std::vector<double>& numbers) {
  if (numbers.empty()) {
    return 0.0;
  }
  double max_element = numbers.front();
  for (double number : numbers) {
    if (max_element < number) {
      max_element = number;
    }
  }
  return max_element;
}

void MultiplyEachItemByNumberOtriz(std::vector<double>& numbers, double scale) {
  for (double& number : numbers) {
    if (if number < 0) {
      number += scale;
    }
  }
}

double FindMinElementsSum(const std::vector<double>& numbers, min_sum) {
  if (numbers.empty()) {
    return 0.0;
  }
  double min_sum = 0;
  double min_element = numbers.front();
  for (double number : numbers) {
    if (number = min_element) {
        //*magic with iterators*
      //erase(iterator)^
    }
      if (number < min_element) {
      number = min_element;
      min_sum += min_element;
    }
  }
  return min_sum;
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
    // *min_it ���������� ������ �� �������, �� ������� ��������� ��������
    // min_it
    MultiplyEachItemByNumber(numbers, *min_it);
  }
#endif
}

void ProcessNumbers3(std::vector<double>& numbers) {
  double min_element = FindMinElement(numbers, min_element);
  double max_element = FindMaxElement(numbers, max_element);
  double a = min_element * max_element;
  MultiplyEachItemByNumberOtriz(numbers, a);
}

void ProcessNumbers4(std::vector<double>& numbers) {
  double min_sum = FindMinElementsSum(numbers, min_sum);
  AddNumberToEachItem(numbers, min_sum);
}

int main() {
  std::vector<double> numbers = ReadNumbers();
  ProcessNumbers---(numbers);
  PrintVector(numbers);
}

/*
������������ � ������������� ������ vector ���������� STL, � ����� � ���������
����������� STL. ������������ ���������, ����������� ���������� ������� ����� �
��������� �������, ����������� ���������, �� ������������ ������ ����� � vector,
�������������� ��� �������� ������� ������ �������� � ��������� � �����������
����� ���������� ������ (����������� ���������). � ��������� ������ ����
�������� �������, ����������� ���������� �������, ��� ���������  � �����
����������.

1. ��������� � ������� �������� ������� ������� �������������� ��� �������������
���������. ���� ������ ������, �� �� �������������� ������.

2. ������ ������� ������� ������ ���� ������� �� ����������� ������� ���������
�������. ���� ������ ������, �������� ��� ��� ���������.

3. �������� ������ ������������� ������� ������� �� ������������ ������������� �
������������ ��������� ��������� �������. ���� ������ ����, �������� ��� ���
���������.

4. ��������� � ������� �������� ������� ����� ���� ����������� ���������
�������. ���� � ������� ������ ��� ���������, �� ��������� ����� ����������
���������. ���� ������ ������, �� �������� ��� ��� ���������

std::partial_sort - https://en.cppreference.com/w/cpp/algorithm/partial_sort
std::partial_sort_copy -
https://en.cppreference.com/w/cpp/algorithm/partial_sort_copy
*/
