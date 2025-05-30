#include "./parser.hpp"
#include <regex>
#include <stdexcept>

MyJSON::Parser::Parser(std::string filename) : tokenizer(filename) {}

std::shared_ptr<MyJSON::JSONNode> MyJSON::Parser::parse() {
  return parseValue();
}

std::shared_ptr<MyJSON::JSONNode> MyJSON::Parser::parseValue() {
  using namespace MyTokenizer;

  if (!tokenizer.hasMoreTokens()) throw std::logic_error("Unexpected end");

  Token token = tokenizer.getToken();

  switch (token.type) {
    case TOKEN::CURLY_OPEN: return parseObject();
    case TOKEN::ARRAY_OPEN: return parseArray();
    case TOKEN::STRING:
    case TOKEN::NUMBER:
    case TOKEN::BOOLEAN:
    case TOKEN::JAVASCRIPT_NULL:
      return parsePrimitive(token);
    default:
      throw std::logic_error("Unexpected token in value: " + token.value);
  }
}

std::shared_ptr<MyJSON::JSONNode>
MyJSON::Parser::parsePrimitive(MyTokenizer::Token token) {
  using namespace MyJSON;

  switch (token.type) {
  case MyTokenizer::TOKEN::STRING:
    return std::make_shared<JSONNode>(token.value);

  case MyTokenizer::TOKEN::NUMBER: {
    static std::regex int_regex(R"(^[+-]?\d+$)");
    static std::regex float_regex(R"(^[+-]?(\d+\.\d*|\.\d+)([eE][+-]?\d+)?$)");

    if (std::regex_match(token.value, int_regex)) {
      return std::make_shared<JSONNode>(std::stoll(token.value));
    } else if (std::regex_match(token.value, float_regex)) {
      return std::make_shared<JSONNode>(std::stod(token.value));
    } else {
      throw std::logic_error("Invalid number format: " + token.value);
    }
  }

  case MyTokenizer::TOKEN::BOOLEAN:
    return std::make_shared<JSONNode>(token.value == "true");

  case MyTokenizer::TOKEN::JAVASCRIPT_NULL:
    return std::make_shared<JSONNode>(nullptr);

  default:
    throw std::logic_error("Invalid primitive");
  }
}

std::shared_ptr<MyJSON::JSONNode> MyJSON::Parser::parseArray() {
  using namespace MyTokenizer;
  using namespace MyJSON;

  MyJSON::JSONNode::JSONArray array;

  if (!tokenizer.hasMoreTokens())
    throw std::logic_error("Unexpected EOF in array");

  Token token = tokenizer.getToken();
  if (token.type == TOKEN::ARRAY_CLOSE) {
    return std::make_shared<JSONNode>(array);
  } else {
    tokenizer.rollBackToken();
  }

  while (true) {
    array.push_back(parseValue());

    if (!tokenizer.hasMoreTokens())
      throw std::logic_error("Unexpected EOF in array");

    token = tokenizer.getToken();
    if (token.type == TOKEN::ARRAY_CLOSE) {
      break;
    } else if (token.type != TOKEN::COMMA) {
      throw std::logic_error("Expected comma in array");
    }
  }

  return std::make_shared<JSONNode>(array);
}

std::shared_ptr<MyJSON::JSONNode> MyJSON::Parser::parseObject() {
  using namespace MyTokenizer;
  using namespace MyJSON;

  MyJSON::JSONNode::JSONObject obj;

  // empty object?
  Token next = tokenizer.peekToken();
  if (next.type == TOKEN::CURLY_CLOSE) {
    tokenizer.getToken();         // consume the '}'
    return std::make_shared<JSONNode>(obj);
  }

  while (true) {
    Token keyTok = tokenizer.getToken();
    if (keyTok.type != TOKEN::STRING) {
      throw std::logic_error(
        "Expected STRING key in object, but got '" + keyTok.value + "'"
      );
    }
    std::string key = keyTok.value;

    Token colon = tokenizer.getToken();
    if (colon.type != TOKEN::COLON) {
      throw std::logic_error(
        "Expected ':' after key \"" + key + "\", but got '" + colon.value + "'"
      );
    }

    auto val = parseValue();
    obj[key] = val;

    Token delim = tokenizer.getToken();
    if (delim.type == TOKEN::CURLY_CLOSE) {
      break;
    } else if (delim.type != TOKEN::COMMA) {
      throw std::logic_error(
        "Expected ',' or '}', but got '" + delim.value + "'"
      );
    }
  }

  return std::make_shared<JSONNode>(obj);
}

