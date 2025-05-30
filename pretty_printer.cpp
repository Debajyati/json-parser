#include "pretty_printer.hpp"
#include "chalk.hpp"
#include <string>

const std::string curly_open = CHALK::cred("{\n");
const std::string curly_close = CHALK::cred("}");
const std::string array_open = CHALK::cred("[\n");
const std::string array_close = CHALK::cred("]");
const std::string call_open = CHALK::cred("(");
const std::string call_close = CHALK::cred(")\n");
const std::string comma = CHALK::cred(",");
const std::string quote = CHALK::cyellow("\"");
const std::string key_quote = CHALK::ccyan("\"");

namespace MyJSON {

void PrettyPrinter::printIndent(std::ostream& os, int indent) {
  os << std::string(indent * 2, ' ');
}

void PrettyPrinter::print(const std::shared_ptr<JSONNode>& node, std::ostream& os, int indent) {
  switch (node->type) {
  case JSONNode::Type::OBJECT: {
    os << curly_open;
    const auto &obj = node->getObject();
    size_t count = 0;
    for (const auto &[key, value] : obj) {
      printIndent(os, indent + 1);
      os << key_quote << CHALK::ccyan(key) << key_quote << CHALK::cred(": ");
      print(value, os, indent + 1);
      if (++count != obj.size())
        os << comma;
      os << "\n";
    }
    printIndent(os, indent);
    os << curly_close;
    break;
  }

  case JSONNode::Type::ARRAY: {
    os << array_open;
    const auto &arr = node->getArray();
    for (size_t i = 0; i < arr.size(); ++i) {
      printIndent(os, indent + 1);
      print(arr[i], os, indent + 1);
      if (i != arr.size() - 1)
        os << comma;
      os << "\n";
    }
    printIndent(os, indent);
    os << array_close;
    break;
  }

  case JSONNode::Type::STRING:
    os << quote << CHALK::cyellow(node->getString()) << quote;
    break;

  case JSONNode::Type::NUMBER: {
    const auto &num = node->getNumber();
    std::visit([&](auto &&val) { os << CHALK::cyellow(std::to_string(val)); }, num);
    break;
  }

  case JSONNode::Type::BOOLEAN:
    os << (node->getBool() ? CHALK::cyellow("true") : CHALK::cyellow("false"));
    break;

  case JSONNode::Type::JAVASCRIPT_NULL:
    os << CHALK::cyellow("null");
    break;
  }
}

} // namespace MyJSON
