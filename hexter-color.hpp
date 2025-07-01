#pragma once

#include <string>
#include <sstream>

namespace hexter {
  const std::string off = "\033[m";
  inline std::string color(const std::string& hex_color, bool bold = true) {
    if (hex_color.size() != 7 || hex_color[0] != '#') return "";

    int r, g, b;
    std::istringstream(hex_color.substr(1, 2)) >> std::hex >> r;
    std::istringstream(hex_color.substr(3, 2)) >> std::hex >> g;
    std::istringstream(hex_color.substr(5, 2)) >> std::hex >> b;

    std::ostringstream ansi;
    ansi << "\033[" << (bold ? "1;" : "") << "38;2;" << r << ";" << g << ";" << b << "m";
    return ansi.str();
  }
}
