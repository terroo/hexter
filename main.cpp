#include "hexter.hpp"

int main(int argc, char** argv){
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
  HexTer hexter;
  hexter.run(argc, argv);
}

