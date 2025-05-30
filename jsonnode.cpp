#include "./jsonnode.hpp"
#include <stdexcept>

void MyJSON::JSONNode::setObject(MyJSON::JSONNode::JSONObject object) {
  this->value = object;
  this->type = Type::OBJECT;
}
void MyJSON::JSONNode::setArray(MyJSON::JSONNode::JSONArray array) {
  this->value = array;
  this->type = Type::ARRAY;
}
void MyJSON::JSONNode::setNumber(MyJSON::JSONNode::NUMBER number) {
  this->value = number;
  this->type = Type::NUMBER;
}
void MyJSON::JSONNode::setString(MyJSON::JSONNode::STRING str) {
  this->value = str;
  this->type = Type::STRING;
}
void MyJSON::JSONNode::setBool(bool boolean) {
  this->value = boolean;
  this->type = Type::BOOLEAN;
}
void MyJSON::JSONNode::setNull(MyJSON::JSONNode::JAVASCRIPT_NULL null) {
  this->value = null;
  this->type = Type::JAVASCRIPT_NULL;
}

bool MyJSON::JSONNode::is_null()    { return std::holds_alternative<MyJSON::JSONNode::JAVASCRIPT_NULL>(this->value); }
bool MyJSON::JSONNode::is_bool()    { return std::holds_alternative<bool>(this->value); }
bool MyJSON::JSONNode::is_number()  { return std::holds_alternative<MyJSON::JSONNode::NUMBER>(this->value); }
bool MyJSON::JSONNode::is_string()  { return std::holds_alternative<MyJSON::JSONNode::STRING>(this->value); }
bool MyJSON::JSONNode::is_array()   { return std::holds_alternative<MyJSON::JSONNode::JSONArray>(this->value); }
bool MyJSON::JSONNode::is_object()  { return std::holds_alternative<MyJSON::JSONNode::JSONObject>(this->value); }

MyJSON::JSONNode::JSONObject MyJSON::JSONNode::getObject() {
  if (MyJSON::JSONNode::is_object())
    return std::get<MyJSON::JSONNode::JSONObject>(this->value);

  throw std::logic_error("Improper Return!");
}
MyJSON::JSONNode::NUMBER MyJSON::JSONNode::getNumber() {
  if (MyJSON::JSONNode::is_number())
    return std::get<MyJSON::JSONNode::NUMBER>(this->value);

  throw std::logic_error("Improper Return!");
}
bool MyJSON::JSONNode::getBool() {
  if (MyJSON::JSONNode::is_bool())
    return std::get<bool>(this->value);

  throw std::logic_error("Improper Return!");
}
MyJSON::JSONNode::STRING MyJSON::JSONNode::getString() {
  if (MyJSON::JSONNode::is_string())
    return std::get<MyJSON::JSONNode::STRING>(this->value);

  throw std::logic_error("Improper Return!");
}
MyJSON::JSONNode::JAVASCRIPT_NULL MyJSON::JSONNode::getNull() {
  if (MyJSON::JSONNode::is_null())
    return nullptr;

  throw std::logic_error("Improper Return!");
}
MyJSON::JSONNode::JSONArray MyJSON::JSONNode::getArray() {
  if (MyJSON::JSONNode::is_array())
    return std::get<MyJSON::JSONNode::JSONArray>(this->value);

  throw std::logic_error("Improper Return!");
}
