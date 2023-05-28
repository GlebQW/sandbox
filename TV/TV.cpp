// TV.cpp : This file contains the 'main' function. Program execution begins and
// ends there.
//

#include <iostream>

class TV {
 public:
  void TurnOn() { is_turned_on_ = true; }

  void TurnOff() { is_turned_on_ = false; }

  bool IsTurnedOn() const { return is_turned_on_; }

  int GetChannel() const {
    if (is_turned_on_ == true) {
      return channel_;
    }
    return 0;
  }

  void SelectChannel(int channel) {
    if (is_turned_on_ == false) throw std::logic_error("TV must be turned on");
    if (channel < 1 || channel > 99)
      throw std::out_of_range("Channel is out of range");
    channel_ = channel;
  }

 private:
  bool is_turned_on_ = false;
  int channel_ = 1;
};

std::ostream& operator<<(std::ostream& out, TV tv) {
  if (tv.IsTurnedOn()) {
    out << "TV is on and shows channel #" << tv.GetChannel();
  } else {
    out << "TV is off";
  }
  return out;
}
/*
TV is off
TV is on and shows channel #N
*/

int main() {
  TV tv;
  std::cout << tv << std::endl;
  tv.TurnOn();
  tv.SelectChannel(30);
  std::cout << tv << std::endl;
}
