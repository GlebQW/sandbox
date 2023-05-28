// classes.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>

enum class Weekday {
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY
};

std::ostream& operator<<(std::ostream& out, Weekday weekday) {
  switch (weekday) {
    case Weekday::MONDAY:
      out << "Monday";
      break;
    case Weekday::TUESDAY:
      out << "Tuesday";
      break;
    case Weekday::WEDNESDAY:
      out << "Wednesday";
      break;
    case Weekday::THURSDAY:
      out << "Thursday";
      break;
    case Weekday::FRIDAY:
      out << "Friday";
      break;
    case Weekday::SATURDAY:
      out << "Saturday";
      break;
    case Weekday::SUNDAY:
      out << "Sunday";
      break;
  }
  return out;
}

struct Point {
  double x = 0.0;
  double y = 0.0;
};

class Date {
 public:
  int GetDay() const { return day_; }
  int GetMonth() const { return month_; }
  int GetYear() const { return year_; }

  void SetDate(int day, int month, int year) {
    if (month < 1 || month > 12) {
      throw std::out_of_range("Month must be in range [1, 12]");
    }
    day_ = day;
    month_ = month;
    year_ = year;
  }

 private:
  int day_ = 1;
  int month_ = 1;
  int year_ = 2023;
};

std::ostream& operator<<(std::ostream& out, Point point) {
  out << "{" << point.x << ", " << point.y << "}";
  return out;
}

int main() {
  Weekday weekday = Weekday::SUNDAY;
  Point p1{1.0, 2.0};
  Point p2{5.0, 3.0};
  Point p3{3.0, 6.0};

  std::cout << p1;

  Date d;

  try
  {
    d.SetDate(14, 10, 2023);
    d.SetDate(13, 13, 2013);
    d.SetDate(15, 1, 2023);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
    std::cout << d.GetDay() << "." << d.GetMonth() << "." << d.GetYear()
              << std::endl;
  }

  std::cout << d.GetDay();

  std::cout << weekday << std::endl;
}
