//#region [Declarations]
#include <stdexcept>
#include <string>
//#endregion

/* Déclaration de la class ClassName
 * La partie public est son interface d'utilisation */
class ClassName {
public: // Public part [types]
  using String = std::string;

public: // Public part [ctor & dtor]
  // Special methods about construction & destruction
  ClassName();
  ClassName(const String &name);
  ~ClassName();

public: // An other public part [methods]
  String getName() const;
  bool setName(const String &name);

private: // Private/internal part
  // Internal data
  String _name;

private: // Private/internal part
  // Internal function
  bool validateName(const String &name) const;
}; // Don't forget this semicolon !!

//#region [Implementation]
ClassName::ClassName(const String &name) {
  if (!setName(name))
    throw std::invalid_argument("Cannot build ClassName");
}

ClassName::~ClassName() {
  // nothing to do now
}

ClassName::String ClassName::getName() const {
  return _name;
}

bool ClassName::setName(const String &name) {
  bool isValid = validateName(name);
  if (isValid) {
    _name = name;
    return true;
  } else {
    return false;
  }
}

bool ClassName::validateName(const String &name) const {
  bool is_first = true;
  for (auto c : name) {
    if (is_first && !(std::isalpha(c) || c == '_'))
      return false;
    else if (!(std::isalnum(c) || c == '_'))
      return false;
    is_first = false;
  }
  return true;
}
//#endregion

//#region [Use class]
int main() {
  ClassName s("toto");
}
//#endregion