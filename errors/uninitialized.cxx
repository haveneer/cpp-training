//#region [Collapse all]
class A {
public:
  A() {} // does not init 'm_i'
  int getI() const { return m_i; }

private:
  int m_i;
};

int main() {
  int i = A().getI(); // 'm_i' (and subsequently i) has an indeterminate value
  int j;              // j has an indeterminate value
  return i + j;
}
//#endregion