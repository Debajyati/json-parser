#ifndef PRETTY_PRINTER_HPP
#define PRETTY_PRINTER_HPP

#include "jsonnode.hpp"
#include <iostream>

namespace MyJSON {

class PrettyPrinter {
public:
    static void print(const std::shared_ptr<JSONNode>& node, std::ostream& os = std::cout, int indent = 0);

private:
    static void printIndent(std::ostream& os, int indent);
};

} // namespace MyJSON

#endif // PRETTY_PRINTER_HPP
