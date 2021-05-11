// may be inspired by numscale example
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

struct base_clonable {
  virtual ~base_clonable() {}
  virtual std::unique_ptr<base_clonable> clone() const = 0;
};

struct factory {
  using result_type = std::unique_ptr<base_clonable>;

  template <typename Registration> factory(Registration const &reg) {
    register_type<typename Registration::type>(reg.key);
  }

  template <typename Registration, typename... Registrations>
  factory(Registration const &r0, Registrations const &...regs) : factory(regs...) {
    register_type<typename Registration::type>(r0.key);
  }

  template <typename ConcreteType> void register_type(std::string const &key) {
    dict[key] =
        result_type(new ConcreteType); // no move: warning: moving a temporary object
                                       // prevents copy elision [-Wpessimizing-move]
  }

  result_type make(std::string const &key) {
    auto search = dict.find(key);
    if (search != dict.cend()) {
      return search->second->clone();
    }

    return result_type(nullptr);
  }

private:
  std::unordered_map<std::string, result_type> dict;
};

template <typename CurrentInterface, typename AbstractType>
CurrentInterface *as(std::unique_ptr<AbstractType> &that) {
  return dynamic_cast<CurrentInterface *>(that.get());
}

template <typename CurrentInterface, typename AbstractType>
CurrentInterface *as(std::unique_ptr<AbstractType> const &that) {
  return dynamic_cast<CurrentInterface const *>(that.get());
}

struct my_interface1 {
  virtual double foo(int) const = 0;
};

struct my_interface2 {
  virtual double bar(int) const = 0;
};

template <typename... Interface> struct clonable : base_clonable, Interface... {};

struct A : clonable<my_interface1, my_interface2> {
  virtual double foo(int i) const override { return i / 2.; }

  virtual double bar(int i) const override { return 0.3333333 * i; }

  virtual std::unique_ptr<base_clonable> clone() const override {
    return std::unique_ptr<base_clonable>(new A);
  }
};

struct B : clonable<my_interface1, my_interface2> {
  virtual double foo(int i) const override { return i * 10.; }

  virtual double bar(int i) const override { return 0.3333333 / i; }

  virtual std::unique_ptr<base_clonable> clone() const override {
    return std::unique_ptr<base_clonable>(new B);
  }
};

template <typename T> struct type_ {
  using type = T;
  const char *key;
};

struct abx_factory : factory {
  abx_factory() : factory{type_<A>{"A"}, type_<B>{"B"}, type_<B>{"X"}} {}
};

int main() {
  abx_factory f;

  {
    auto m = f.make("A");
    auto a = as<A>(m);

    std::cout << a->bar(5) << "\n";
    std::cout << a->foo(5) << "\n";
  }

  {
    auto m = f.make("B");
    auto b = as<B>(m);

    std::cout << b->bar(5) << "\n";
    std::cout << b->foo(5) << "\n";
  }
  {
    auto m = f.make("X");
    auto b = as<B>(m);

    std::cout << b->bar(5) << "\n";
    std::cout << b->foo(5) << "\n";
  }
}