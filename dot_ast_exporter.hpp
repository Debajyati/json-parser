#ifndef DOT_AST_EXPORTER_HPP
#define DOT_AST_EXPORTER_HPP

#include "jsonnode.hpp"
#include <string>

namespace MyJSON {

class DOTASTExporter {
public:
    static std::string parentLabel;
    static long long currentArrayIndex;
    static void exportToDOT(const std::shared_ptr<JSONNode>& root, const std::string& filename);

private:
    static void exportNode(const std::shared_ptr<JSONNode>& node, std::ostream& os, int& idCounter, int parentID = -1);
    static std::string escapeLabel(const std::string& label);
    static std::string getShape(JSONNode::Type type);
    static std::string getColor(JSONNode::Type type);
};

} // namespace MyJSON

#endif // DOT_AST_EXPORTER_HPP
