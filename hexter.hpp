#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class HexTer {

  std::string hex_to_ansi_rgb(const std::string&, int&, int&, int&);
  std::string ansi_color(int, int, int, bool);
  std::string bg_color(int, int, int);
  std::string repeat(const std::string&, size_t);
  std::string strip_ansi(const std::string&);
  void print_table(const std::string&, int, int, int);

  public:
    HexTer();
    void run(int, char**);
};
