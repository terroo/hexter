#include "hexter.hpp"

HexTer::HexTer(){}

std::string HexTer::hex_to_ansi_rgb(const std::string& hex_color, int& r, int& g, int& b){
  if(hex_color.size() != 7 || hex_color[0] != '#') return "";
  std::istringstream(hex_color.substr(1, 2)) >> std::hex >> r;
  std::istringstream(hex_color.substr(3, 2)) >> std::hex >> g;
  std::istringstream(hex_color.substr(5, 2)) >> std::hex >> b;
  std::ostringstream ansi;
  ansi << "\033[1;38;2;" << r << ";" << g << ";" << b << "m";
  return ansi.str();
}

std::string HexTer::ansi_color(int r, int g, int b, bool bold){
  std::ostringstream ss;
  ss << "\033[" << (bold ? "1" : "0") << ";38;2;" << r << ";" << g << ";" << b << "m";
  return ss.str();
}

std::string HexTer::bg_color(int r, int g, int b){
  std::ostringstream ss;
  ss << "\033[48;2;" << r << ";" << g << ";" << b << "m";
  return ss.str();
}

std::string HexTer::repeat(const std::string& s, size_t count){
  std::ostringstream out;
  for (size_t i = 0; i < count; ++i) out << s;
  return out.str();
}

std::string HexTer::strip_ansi(const std::string& s){
  std::string result;
  size_t i = 0;
  while (i < s.size()){
    if(s[i] == '\033' && (i + 1 < s.size()) && s[i + 1] == '['){
      i += 2;
      while (i < s.size() && !(s[i] >= '@' && s[i] <= '~')) ++i;
      if(i < s.size()) ++i;
    } else {
      result += s[i++];
    }
  }
  return result;
}

void HexTer::print_table(const std::string& hex, int r, int g, int b){
  const std::string reset = "\033[m";
  const std::string bg = bg_color(r, g, b);

  std::ostringstream rgbStr;
  rgbStr << "(" << r << "," << g << "," << b << ")";

  std::ostringstream ansi1, ansi2;
  ansi1 << "\\033[1;38;2;" << r << ";" << g << ";" << b << "m";
  ansi2 << "\\033[2;38;2;" << r << ";" << g << ";" << b << "m";

  std::vector<std::pair<std::string, std::string>> labels = {
    {"HEX:", hex},
    {"ANSI:", ansi1.str()},
    {"RGB:", rgbStr.str()},
    {"BOLD:", ansi2.str()}
  };

  std::vector<std::string> rendered = {
    ansi_color(r, g, b, false) + hex + reset,
    ansi_color(r, g, b, false) + ansi1.str() + reset,
    ansi_color(r, g, b, false) + rgbStr.str() + reset,
    ansi_color(r, g, b, true) + ansi2.str() + reset
  };

  const size_t left_width = 16;
  size_t label_width = 0, value_width = 0;

  for (size_t i = 0; i < labels.size(); ++i){
    label_width = std::max(label_width, labels[i].first.size());
    value_width = std::max(value_width, strip_ansi(rendered[i]).size());
  }

  label_width += 2; value_width += 2;

  std::string h = "─", v = "│";
  std::string tl = "╭", tr = "╮", bl = "╰", br = "╯";
  std::string tm1 = "┬", tm2 = "┬", bm1 = "┴", bm2 = "┴";
  std::string ml = "├", mm1 = "┼", mm2 = "┼", mr = "┤";

  std::cout << tl << repeat(h, left_width)
    << tm1 << repeat(h, label_width)
    << tm2 << repeat(h, value_width)
    << tr << "\n";

  for (size_t i = 0; i < labels.size(); ++i){
    std::string val = rendered[i];
    size_t valLen = strip_ansi(val).size();
    size_t pad = value_width - 2 - valLen;

    std::cout << v << bg << repeat(" ", left_width) << reset
      << v << " " << std::setw(static_cast<int>(label_width) - 2) << std::left << labels[i].first << " "
      << v << " " << val << repeat(" ", pad) << " " << v << "\n";

    if(i != labels.size() - 1){
      std::cout << v << bg << repeat(" ", left_width) << reset
        << ml << repeat(h, label_width)
        << mm1 << repeat(h, value_width)
        << mr << "\n";
    }
  }

  std::cout << bl << repeat(h, left_width)
    << bm1 << repeat(h, label_width)
    << bm2 << repeat(h, value_width)
    << br << "\n";
}

void HexTer::run(int argc, char** argv){
  if(argc <= 1){
    std::cerr << "Enter the color, e.g.: " << argv[0] << " '#a6e22e'\n";
    std::exit(1);
  }

  std::string hex = argv[1];
  if(hex[0] != '#') hex = "#" + hex;

  int r, g, b;
  hex_to_ansi_rgb(hex, r, g, b);
  print_table(hex, r, g, b);
}
