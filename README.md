# ![json-parser-logo](https://github.com/Debajyati/json-parser/blob/main/JSON%20Parser%20Logo.png)

It is a JSON Parser in C++. 

You can compile the main file by running the script - 
```bash
./compile
```
But make sure you have GNU C++ compiler (g++) installed.

Then run the program using - `./json_parser <input-filepath> <options>`.
For example you can get the helptexts by running `./json_parser -h` which will show - 
```markdown

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

```

From here you will get the idea how to use the compiled binary.

Also, you can use some of the header and source files as third party modules by downloading the files in your projects. And the tweaking them as per your requirements. 

The documentation for the Parser API (content of the header files) is not available yet. Coming soon.
