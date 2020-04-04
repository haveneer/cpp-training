//#region [Declaration]
#include <iostream>
#include <string>
// WARNING: missing virtual destructor !
//#endregion

class Employee {
public:
  std::string name() const { return m_name; }

protected:
  std::string m_id;

private:
  std::string m_name;
};

class SalesPerson : public Employee {
public:
  std::string region() const { return m_region; }
  std::string describe() const { return "SalesPerson(name:" + name() + ", id:" + m_id + ", region:" + m_region + ")"; }

protected:
  uint64_t m_sales_amount;

private:
  std::string m_region;
};

class Engineer : public Employee {
public:
  std::string product() const { return m_product; }
  std::string describe() const { return "Engineer(name:" + name() + ", id:" + m_id + ", produc:" + m_product + ")"; }

protected:
  std::string m_fixed_bug_count;

private:
  std::string m_product;
};

class TestEngineer : public Engineer {
public:
  std::string testStage() const { return m_test_stage; }
  std::string describe() const { return "TestEngineer(name:" + name() + ", id:" + m_id + ", testStage:" + m_test_stage + ")"; }

private:
  std::string m_test_stage;
};

int main() {
  TestEngineer t;
  std::cout << t.describe() << "\n";
}