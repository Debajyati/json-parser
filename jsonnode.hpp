#ifndef JSONNODE_HPP
#define JSONNODE_HPP

#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace MyJSON {

class JSONNode {
public:
  using JSONObject = std::map<std::string, std::shared_ptr<JSONNode>>;
  using JSONArray = std::vector<std::shared_ptr<JSONNode>>;
  using NUMBER = std::variant<long long int, double>;
  using STRING = std::string;
  using JAVASCRIPT_NULL = std::nullptr_t;

  enum class Type {
    JAVASCRIPT_NULL, BOOLEAN, NUMBER, STRING, ARRAY, OBJECT
  };
  Type type;

  /* Constructors for each type */
  JSONNode()                         : value(nullptr),type(Type::JAVASCRIPT_NULL) {}
  JSONNode(std::nullptr_t)           : value(nullptr),type(Type::JAVASCRIPT_NULL) {}
  JSONNode(bool b)                   : value(b),type(Type::BOOLEAN) {}
  JSONNode(double num)               : value(num), type(Type::NUMBER) {}
  JSONNode(long num)                 : value(num), type(Type::NUMBER) {}
  JSONNode(long long num)            : value(num), type(Type::NUMBER) {}
  JSONNode(const std::string& str)   : value(str), type(Type::STRING) {}
  JSONNode(std::string&& str)        : value(std::move(str)), type(Type::STRING) {}
  JSONNode(const char* cstr)         : value(std::string(cstr)), type(Type::STRING) {}
  JSONNode(const JSONArray& arr)     : value(arr), type(Type::ARRAY) {}
  JSONNode(JSONArray&& arr)          : value(std::move(arr)), type(Type::ARRAY) {}
  JSONNode(const JSONObject& obj)    : value(obj), type(Type::OBJECT) {}
  JSONNode(JSONObject&& obj)         : value(std::move(obj)), type(Type::OBJECT) {}

  /* Type-check helpers */
  bool is_null();
  bool is_bool();
  bool is_number();
  bool is_string();
  bool is_array();
  bool is_object();

  /* getters */
  JSONObject getObject();
  NUMBER getNumber();
  bool getBool();
  STRING getString();
  JAVASCRIPT_NULL getNull();
  JSONArray getArray();

  /* setters */
  void setObject(JSONObject object);
  void setArray(JSONArray array);
  void setNumber(NUMBER number);
  void setString(STRING str);
  void setBool(bool boolean);
  void setNull(JAVASCRIPT_NULL null);

private:
  std::variant<STRING, NUMBER, bool, JSONArray, JSONObject, JAVASCRIPT_NULL>
      value;
};

} // namespace MyJSON

#endif // JSONNODE_HPP
