#include "ast_printer.hpp"
#include "chalk.hpp"
#include <string>
#include <variant>

const std::string curly_open = CHALK::cred(" {\n");
const std::string curly_close = CHALK::cred("}\n");
const std::string array_open = CHALK::cred(" [\n");
const std::string array_close = CHALK::cred("]\n");
const std::string call_open = CHALK::cred("(");
const std::string call_close = CHALK::cred(")\n");
const std::string quote = CHALK::cyellow("\"");
const std::string val_quote = CHALK::ccyan("\"");

namespace MyJSON {

void ASTPrinter::print(const std::shared_ptr<JSONNode> &node, int indent) {
  if (!node) {
    printIndent(indent);
    std::cout << CHALK::ccyan("null\n");
    return;
  }

  switch (node->type) {
  case JSONNode::Type::JAVASCRIPT_NULL:
    printIndent(indent);
    std::cout << CHALK::cgreen("Null\n");
    break;

  case JSONNode::Type::BOOLEAN:
    printIndent(indent);
    std::cout << CHALK::cgreen("Boolean") << call_open << (node->getBool() ? CHALK::ccyan("true") : CHALK::ccyan("false")) << call_close;
    break;

  case JSONNode::Type::NUMBER: {
    printIndent(indent);
    JSONNode::NUMBER num = node->getNumber();
    if (std::holds_alternative<double>(num))
      std::cout << CHALK::cgreen("Number") << call_open << CHALK::ccyan(std::to_string(std::get<double>(num))) << call_close;
    else
      std::cout << CHALK::cgreen("Number") << call_open << CHALK::ccyan(std::to_string(std::get<long long>(num))) << call_close;
    break;
  }

  case JSONNode::Type::STRING:
    printIndent(indent);
    std::cout << CHALK::cgreen("String") << call_open << val_quote << CHALK::ccyan(node->getString()) << val_quote << call_close;
    break;

  case JSONNode::Type::ARRAY:
    printIndent(indent);
    std::cout << CHALK::cgreen("Array") << array_open;
    printArray(node->getArray(), indent + 1);
    printIndent(indent);
    std::cout << array_close;
    break;

  case JSONNode::Type::OBJECT:
    printIndent(indent);
    std::cout << CHALK::cgreen("Object") << curly_open;
    printObject(node->getObject(), indent + 1);
    printIndent(indent);
    std::cout << curly_close;
    break;
  }
}

void ASTPrinter::printArray(const JSONNode::JSONArray &arr, int indent) {
  for (const auto &item : arr) {
    print(item, indent);
  }
}

void ASTPrinter::printObject(const JSONNode::JSONObject &obj, int indent) {
  for (const auto &pair : obj) {
    printIndent(indent);
    std::cout << quote << CHALK::cyellow(pair.first) << quote << CHALK::cred(":") << "\n";
    print(pair.second, indent + 1);
  }
}

} // namespace MyJSON
