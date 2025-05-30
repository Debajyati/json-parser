#include "jsonnode.hpp"
#include <iostream>
#include <memory>

namespace MyJSON {

class ASTPrinter {
public:
  static void print(const std::shared_ptr<JSONNode> &node, int indent = 0);

private:
  static inline void printIndent(int level) {
    for (int i = 0; i < level; ++i)
      std::cout << "  ";
  }
  static void printObject(const JSONNode::JSONObject &obj, int indent);
  static void printArray(const JSONNode::JSONArray &arr, int indent);
};

} // namespace MyJSON
