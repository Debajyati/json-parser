#include "ast_printer.hpp"
#include "dot_ast_exporter.hpp"
#include "parser.hpp"
#include "pretty_printer.hpp"
#include <cstring>
#include <stdexcept>

#define PRETTY_PRINT()                                                         \
  std::cout << std::endl << "Pretty printing the json file - \n" << std::endl; \
  MyJSON::PrettyPrinter::print(root);                                          \
  std::cout << std::endl;

#define ABSTRACT_SYNTAX_TREE()                                                 \
  std::cout << "The Abstract Syntax Tree of the provided json file is - \n"    \
            << std::endl;                                                      \
  MyJSON::ASTPrinter::print(root);

#define EXPORT_DOT(directory)                                                  \
  std::string filepath = "ast.dot";                                            \
  if (directory.empty()) {                                                     \
    filepath = "ast.dot";                                                      \
  } else {                                                                     \
    filepath = directory + filepath;                                           \
  }                                                                            \
  MyJSON::DOTASTExporter::exportToDOT(root, filepath);

int main(int argc, char *argv[]) {
  try {
    if (argc < 2) {
      std::cerr << "\033[31m You forgot to provide the filepath ; (\033[0m"
                << std::endl;
      return 1;
    }
    if (argc < 3) {
      const bool cond1 = strcmp(argv[1], "--help") == 0;
      const bool cond2 = strcmp(argv[1], "-h") == 0;
      const bool cond3 = strcmp(argv[1], "help") == 0;
      if (cond3 || cond1 || cond2) {
        std::cout << R"(
json_parser - A simple command-line tool to parse and visualize JSON structures.

USAGE:
  ./json_parser <input-filepath> <command>

ARGUMENTS:
  <input-filepath>            Path to the input JSON file to be parsed.
  <command>                   The operation to perform on the parsed JSON.
    
COMMANDS:    
  --pprint                    Pretty print the JSON content with proper formatting and highlighting.
  --cast                      Display the Abstract Syntax Tree (AST) of the JSON in console.
  --export <output-directory> Export the AST to a Graphviz-compatible DOT file. 

EXAMPLES:
  ./json_parser example.json --pprint
      Prints the JSON file in a human-readable, indented format.

  ./json_parser example.json --cast
      Outputs the AST to standard output.

  ./json_parser example.json --export <output-directory>
      Writes the AST in DOT format to 'ast.dot' located at <output-directory>.
      If no directory for DOT output file provided, a DOT file named `ast.dot` will be generated in the same dirctory of the program binary.
      To visualize, run: dot -Tsvg ast.dot -o ast.svg

  ./json_parser --help
      Show this help message.

TIPS:
  • Make sure your JSON file is syntactically correct.
  • Use Graphviz (`dot`) to visualize exported ASTs.
  • For best results, keep your file under ~1MB for smooth parsing.

)" << std::endl;

        return 0;
      } else {
        std::cerr << "\033[31m Invalid command! Are you sure you know what you "
                  << "are doing? =) \033[0m" << std::endl;
        std::cout << "May be a piece of helptext can help you out! $-)\n";
        std::cout << "Try running `./json_parser --help`" << std::endl;
        return 1;
      }
    }
    MyJSON::Parser parser(argv[1]);
    auto root = parser.parse();
    if (strcmp(argv[2], "--pprint") == 0) {
      PRETTY_PRINT();
    } else if (strcmp(argv[2], "--cast") == 0) {
      ABSTRACT_SYNTAX_TREE();
    } else if (strcmp(argv[2], "--export") == 0) {
      std::string dir = "";
      if (argv[3]) {
        dir = argv[3];
        EXPORT_DOT(dir);
      } else {
        EXPORT_DOT(dir);
      }
      std::cout << '\n'
                << "A Graphviz dot language file is generated" << std::endl;
      std::cout << "If you have graphviz cli installed, run `dot -Tsvg " << dir
                << "ast.dot"
                << " -o ast.svg` to generate an SVG image for visualizing the "
                << "JSON Syntax Tree" << std::endl;
    } else {
      std::cerr << "\033[31m Invalid command! Are you sure you know what you "
                << "are doing? =) \033[0m" << std::endl;
      std::cout << "May be a piece of helptext can help you out! $-)\n";
      std::cout << "Try running `./json_parser --help`" << std::endl;
      return 1;
    }
  } catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
