#include <stdio.h>
#include <iostream>
#include "utf8cpp/utf8.h"
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

char GetValidCharacter(int c) {
  if (c >= 0x41 && c <= 0x5A) { // A-Z to a-z.
    return c + 0x20;
  } else if (c >= 0x61 && c <= 0x7A) { // a-z remains a-z.
    return c;
  } else if (c >= 0xC0 && c <= 0xFF) { // Accented characters to unaccented.
    static const char*
    //   "ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
    tr = "aaaaaaeceeeeiiiidnoooooxouuuuypsaaaaaaeceeeeiiiionooooooouuuuypy";
    return tr[c - 0xC0];
  } else { // Non alphanumeric characters to null.
    return '\0';
  }
}

std::vector<std::string> ExtractLexemes(std::string text) {
  vector<std::string> result;
  
  std::string lexeme;
  std::string::iterator current_it = text.begin();
  
  int utf8char;
  while (current_it != text.end()) {
    utf8char = utf8::next(current_it, text.end());
    char c = GetValidCharacter(utf8char);
    if (c != '\0') {
      lexeme += c;
    } else if (lexeme.length() > 0 && lexeme.length() < 256) {
      result.push_back(lexeme);
      lexeme.clear();
    } else {
      lexeme.clear();
    }
  }
  
  if (lexeme.length() > 0 && lexeme.length() < 256)
    result.push_back(lexeme);
  return result;
}

int main (int argc, char* argv[]) {
  std::string line;
  std::ifstream f(argv[1]);
  if (!f.is_open()) {
    std::cout << "Could not open file" << std::endl;
    return 1;
  }

  while (std::getline(f, line)) {
    std::vector<std::string> tokens = ExtractLexemes(line);
    for (auto token : tokens)
      std::cout << token << ' ';
  }
  std::cout << std::endl;
  f.close();
  return 0;
}
