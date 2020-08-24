//#region [Declaration]

//#endregion

class Point3D {
public:
  // class type member
  using Value = double;

private:
  // object data
  Value _x, _y, _z;

  //#region [ctor & dtor]
public:
  // Constructeur par défaut (pas d'argument)
  Point3D() : Point3D{0} {}
  // Constructeur par copie (argument du type de la classe courante)
  Point3D(const Point3D &p);
  // Autres constructeurs
  Point3D(const Value &v) { initialize(v); }
  // Destructeur [par défaut]
  ~Point3D() = default;
  //#endregion

  //#region [other methods]
public:
  // Declaration + definition & direct access to data
  void initialize(const Value &v) { _x = _y = _y = v; }

  void initialize() = delete;

  // Declaration with later definition
  // Could be 'inline' if defined in same file/multiple times
  /* inline */ void add(const Point3D &p);

  //#endregion
};

//#region [ctor definition]
Point3D::Point3D(const Point3D &p)
  : _x{p._x}, _y{p._y}, _z{p._z} {}
//#endregion

//#region [other methods]
// Separate definition
// Recall prototype
void Point3D::add(const Point3D &p) {
  // Indirect access to object member using this->
  // Direct access to other objet data using .
  this->_x += p._x;
  this->_y += p._y;
  this->_z += p._z;
}
//#endregion

int main() {
  // Access to class type member
  Point3D::Value zero = 0.0;
  Point3D::Value one = 1.0;

  // Two new Point3D [INITIALIZED ??]
  Point3D a, b;

  // method call
  a.initialize(zero);
  b.initialize(one);
  // a.initialize(); // does not exist [deleted]

  Point3D *pa = &a;
  pa->add(b);
}