//#region [Declaration]
#include <iostream>
#include <string>
// WARNING: missing virtual destructor !
//#endregion

class Employee {
public:
  std::string name() const { return _name; }

protected:
  std::string _id;

private:
  std::string _name;
};

class SalesPerson : public Employee {
public:
  std::string region() const { return _region; }
  std::string describe() const { return "SalesPerson(name:" + name() + ", id:" + _id + ", region:" + _region + ")"; }

protected:
  u_int64_t _sales_amount;

private:
  std::string _region;
};

class Engineer : public Employee {
public:
  std::string product() const { return _product; }
  std::string describe() const { return "Engineer(name:" + name() + ", id:" + _id + ", produc:" + _product + ")"; }

protected:
  std::string _fixed_bug_count;

private:
  std::string _product;
};

class TestEngineer : public Engineer {
public:
  std::string testStage() const { return _test_stage; }
  std::string describe() const { return "TestEngineer(name:" + name() + ", id:" + _id + ", testStage:" + _test_stage + ")"; }

private:
  std::string _test_stage;
};

int main() {
  TestEngineer t;
  std::cout << t.describe() << "\n";
}