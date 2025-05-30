#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <fstream>
#include <string>

namespace MyTokenizer {

enum class TOKEN {
  CURLY_OPEN,
  CURLY_CLOSE,
  ARRAY_OPEN,
  ARRAY_CLOSE,
  COLON,
  COMMA,
  NUMBER,
  STRING,
  BOOLEAN,
  JAVASCRIPT_NULL
};

struct Token {
  std::string value;
  TOKEN type;
  std::string toString();
};

class Tokenizer {
  std::fstream file;
  size_t prevPos;

public:
  Tokenizer(std::string fileName);
  Token peekToken();
  auto getWithoutWhiteSpace();
  Token getToken();
  bool hasMoreTokens();
  void rollBackToken();
};

} // namespace MyTokenizer

#endif // TOKENIZER_HPP
