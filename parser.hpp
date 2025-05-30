#ifndef PARSER_HPP
#define PARSER_HPP

#include "jsonnode.hpp"
#include "tokenizer.hpp"

namespace MyJSON {

class Parser {
  MyTokenizer::Tokenizer tokenizer;

  std::shared_ptr<MyJSON::JSONNode> parseValue();
  std::shared_ptr<MyJSON::JSONNode> parseObject();
  std::shared_ptr<MyJSON::JSONNode> parseArray();
  std::shared_ptr<MyJSON::JSONNode> parsePrimitive(MyTokenizer::Token token);

public:
  Parser(std::string filename);
  std::shared_ptr<MyJSON::JSONNode> parse();
};

} // namespace MyParser

#endif // PARSER_HPP
