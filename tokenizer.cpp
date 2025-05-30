#include "./tokenizer.hpp"
#include <cctype>
#include <sstream>
#include <stdexcept>

MyTokenizer::Tokenizer::Tokenizer(std::string fileName) : prevPos(0) {
  file.open(fileName, std::ios::in);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file." + fileName);
  }
  prevPos = file.tellg();
}

bool MyTokenizer::Tokenizer::hasMoreTokens() { return file && !file.eof() && file.peek() != EOF; }

std::string MyTokenizer::Token::toString() {
  static const char* tokenTypeNames[] = {
    "CURLY_OPEN", "CURLY_CLOSE", "ARRAY_OPEN", "ARRAY_CLOSE",
    "COLON", "COMMA", "NUMBER", "STRING", "BOOLEAN", "JAVASCRIPT_NULL"
  };

  return "Token(" + std::string(tokenTypeNames[static_cast<int>(type)]) + ", \"" + value + "\")";
}

auto MyTokenizer::Tokenizer::getWithoutWhiteSpace() {
  char c = ' ';
  while ((c == ' ' || c == '\n')) {
    file.get(c);

    if ((c == ' ' || c == '\n') && !file.good()) {
      throw std::logic_error("Ran out of tokens");
    } else if (!file.good()) {
      return c;
    }
  }

  return c;
}

void MyTokenizer::Tokenizer::rollBackToken() {
  if (file.eof()) {
    file.clear();
  }
  file.seekg(prevPos);
}

MyTokenizer::Token MyTokenizer::Tokenizer::peekToken() {
  auto savePos = file.tellg();
  Token tok = getToken();
  file.clear();                  // in case eof-bit was set
  file.seekg(savePos);
  prevPos = savePos;
  return tok;
}

MyTokenizer::Token MyTokenizer::Tokenizer::getToken() {
  prevPos = file.tellg();
  char c = getWithoutWhiteSpace();

  if (file.eof())
    throw std::logic_error("No more tokens");

  switch (c) {
  case '{':
    return {"{", TOKEN::CURLY_OPEN};
  case '}':
    return {"}", TOKEN::CURLY_CLOSE};
  case '[':
    return {"[", TOKEN::ARRAY_OPEN};
  case ']':
    return {"]", TOKEN::ARRAY_CLOSE};
  case ':':
    return {":", TOKEN::COLON};
  case ',':
    return {",", TOKEN::COMMA};
  case '"': {
    std::ostringstream ss;
    while (file.get(c) && c != '"') {
      if (c == '\\') {
        char next;
        if (file.get(next))
          ss << '\\' << next;
        else
          throw std::logic_error("Invalid escape");
      } else {
        ss << c;
      }
    }
    return {ss.str(), TOKEN::STRING};
  }
  default:
    if (std::isdigit(c) || c == '-' || c == '+') {
      std::ostringstream ss;
      ss << c;
      while (file.peek() != EOF &&
             (std::isdigit(file.peek()) || file.peek() == '.' ||
              file.peek() == 'e' || file.peek() == 'E' || file.peek() == '+' ||
              file.peek() == '-')) {
        char next = file.get();
        ss << next;
      }
      return {ss.str(), TOKEN::NUMBER};
    } else {
      std::ostringstream ss;
      ss << c;
      while (file.peek() != EOF && std::isalpha(file.peek())) {
        ss << (char)file.get();
      }
      std::string word = ss.str();
      if (word == "true" || word == "false") {
        return {word, TOKEN::BOOLEAN};
      } else if (word == "null") {
        return {word, TOKEN::JAVASCRIPT_NULL};
      } else {
        throw std::logic_error("Unknown token: " + word);
      }
    }
  }
}
