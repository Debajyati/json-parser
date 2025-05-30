#include "dot_ast_exporter.hpp"
#include <fstream>
#include <sstream>
#include <string>

namespace MyJSON {

std::string DOTASTExporter::parentLabel = "Object";
long long DOTASTExporter::currentArrayIndex = -1;

void DOTASTExporter::exportToDOT(const std::shared_ptr<JSONNode> &root,
                                 const std::string &filename) {
    std::ofstream ofs(filename);
    ofs << "digraph JSON_AST {\n";
    ofs << "  ranksep=0.75;\n";
    ofs << "  nodesep=0.3;\n";
    ofs << "  node [fontname=\"Helvetica\"];\n";
    ofs << "  edge [fontname=\"Palatino-Roman\"];\n";
    int idCounter = 0;
    exportNode(root, ofs, idCounter);
    ofs << "}\n";
}

void DOTASTExporter::exportNode(const std::shared_ptr<JSONNode> &node,
                                std::ostream &os, int &idCounter,
                                int parentID) {
    int currentID = idCounter++;
    std::ostringstream label;
    std::string edgeLabel;
    if (parentLabel == "Array") {
        currentArrayIndex++;
        edgeLabel = "index[" + std::to_string(currentArrayIndex) + "]";
    } else {
        edgeLabel = "value";
    }

    switch (node->type) {
        case JSONNode::Type::OBJECT:
            label << "Object";
            break;
        case JSONNode::Type::ARRAY:
            label << "Array";
            break;
        case JSONNode::Type::STRING:
            label << "\"" << escapeLabel(node->getString()) << "\"";
            break;
        case JSONNode::Type::NUMBER: {
            JSONNode::NUMBER num = node->getNumber();
            if (std::holds_alternative<double>(num))
                label << std::get<double>(num);
            else
                label << std::get<long long>(num);
            break;
        }
        case JSONNode::Type::BOOLEAN:
            label << (node->getBool() ? "true" : "false");
            break;
        case JSONNode::Type::JAVASCRIPT_NULL:
            label << "null";
            break;
    }

    os << "  node" << currentID << " [label=\"" << escapeLabel(label.str()) << "\", shape=" << getShape(node->type) << ", style=filled, fillcolor=\"" << getColor(node->type) << "\"];\n";

    if (parentID >= 0) {
        os << "  node" << parentID << " -> node" << currentID << " [label=\"" << edgeLabel << "\", style=" << (edgeLabel == "value" ? "dashed" : "solid") << "];\n";
    }

    if (node->type == JSONNode::Type::OBJECT) {
        for (const auto &[k, v] : node->getObject()) {
            int keyID = idCounter++;
            os << "  node" << keyID << " [label=\"" << escapeLabel(k) << "\"];\n";
            os << "  node" << currentID << " -> node" << keyID << " [label=\"" << "key" << "\", style=" << "solid" << "];\n";
            parentLabel = "Object";
            exportNode(v, os, idCounter, keyID);
        }
    } else if (node->type == JSONNode::Type::ARRAY) {
        parentLabel = "Array";
        currentArrayIndex = -1;
        for (const auto &elem : node->getArray()) {
            exportNode(elem, os, idCounter, currentID);
        }
    }
}

std::string DOTASTExporter::escapeLabel(const std::string &label) {
    std::string escaped;
    for (char c : label) {
        switch (c) {
            case '"': escaped += "\\\""; break;
            case '\n': escaped += "\\n"; break;
            case '\\': escaped += "\\\\"; break;
            default: escaped += c;
        }
    }
    return escaped;
}

std::string DOTASTExporter::getShape(JSONNode::Type type) {
    switch (type) {
        case JSONNode::Type::OBJECT: return "box";
        case JSONNode::Type::ARRAY: return "ellipse";
        default: return "note"; // for values
    }
}

std::string DOTASTExporter::getColor(JSONNode::Type type) {
    switch (type) {
        case JSONNode::Type::OBJECT: return "lightblue";
        case JSONNode::Type::ARRAY: return "khaki";
        case JSONNode::Type::STRING: return "lightgreen";
        case JSONNode::Type::NUMBER: return "orange";
        case JSONNode::Type::BOOLEAN: return "gold";
        case JSONNode::Type::JAVASCRIPT_NULL: return "gray";
        default: return "white";
    }
}

} // namespace MyJSON
