#include <sstream>

namespace CHALK {
inline std::string cgreen(const std::string& input) {
  std::ostringstream out;
  out << "\033[92m" << input << "\033[0m";
  return out.str();
}

inline std::string cred(const std::string& input) {
  std::ostringstream out;
  out << "\033[91m" << input << "\033[0m";
  return out.str();
}

inline std::string ccyan(const std::string& input) {
  std::ostringstream out;
  out << "\033[96m" << input << "\033[0m";
  return out.str();
}

inline std::string cyellow(const std::string& input) {
  std::ostringstream out;
  out << "\033[93m" << input << "\033[0m";
  return out.str();
}

}
