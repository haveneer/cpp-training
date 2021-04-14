#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

class IAuthenticator {
public:
  virtual bool login(std::string username, std::string password) = 0;
  virtual bool logout(std::string username) = 0;
  virtual void something() = 0;
  virtual ~IAuthenticator() = default;
};

class Authenticator : public IAuthenticator {
public:
  bool login(std::string username, std::string password) override {
    std::cout << "Authenticator::login call\n";
    return true;
  }
  bool logout(std::string username) override {
    std::cout << "Authenticator::logout call\n";
    return true;
  }
  void something() override { //
    std::cout << "Authenticator::something call\n";
  }
};

class Service {
public:
  explicit Service(IAuthenticator *auth) : m_auth(auth) {}
  int init(std::string username, std::string password) {
    if (m_auth->login(username, password) != true) {
      std::cerr << "Service init failed" << std::endl;
      return -1;
    } else {
      std::cout << "Service init succeeded" << std::endl;
      m_username = username;
      return 0;
    }
  }
  void something() {
    std::cout << "Service::something" << std::endl;
    m_auth->something();
  }
  virtual ~Service() {
    // TODO "forget" the logout call
    m_auth->logout(m_username);
  }

private:
  IAuthenticator *m_auth;
  std::string m_username;
};

// Direct test without mock
TEST(Service, WithoutMock) {
  std::cout << "------------------------------\n";
  Authenticator auth;
  Service service(&auth);

  std::string username = "Goldorak";
  std::string password = "cornofulgure";

  ASSERT_EQ(service.init(username, password), 0);
  service.something();
}

// Test with deriving mock of Authenticator
class MockDerivingAuth : public Authenticator {
public:
  // Before 1.10.0 use MOCK_METHOD1...
  MOCK_METHOD(bool, login, (std::string username, std::string password), (override));
  MOCK_METHOD(bool, logout, (std::string username), (override));
};

TEST(IAuthenticator, dtor_must_be_virual) {
  std::unique_ptr<IAuthenticator> p = std::make_unique<MockDerivingAuth>();
  ASSERT_TRUE(std::has_virtual_destructor_v<MockDerivingAuth>);
  // static_assert(std::has_virtual_destructor_v<MockDerivingAuth>); // or statically
  // when p is destroyed destructor is not call => no report is destroyed this way
}

TEST(Service, WithDerivingMock) {
  std::cout << "------------------------------\n";
  using ::testing::_; // _ is the joker argument for expected calls
  using ::testing::InSequence;
  using ::testing::Invoke;
  using ::testing::Return;

  Authenticator true_auth;     // This code is not very safe, since true_auth
  MockDerivingAuth mock_auth;  // and mock_auth should be alive as long as service is
  Service service(&mock_auth); // In production prefer using shared_ptr or protect
                               // using block scope
  std::string username = "Goldorak";
  std::string password = "cornofulgure";

  InSequence s; // will force expected ordered calls

  // Will only catch call after EXPECT_CALL rules
  EXPECT_CALL(mock_auth, login(username, password)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(mock_auth, logout(username)) // caught from Database destructor
      .Times(1)
      .WillOnce(
          Invoke(&true_auth,
                 &Authenticator::logout)); // redirect call to another object/method

  ASSERT_EQ(service.init(username, password), 0);
  service.something();
}

// Test with not deriving mock of Authenticator
// With template instanciation, inheritance is not required
class MockNotDerivingAuth : public IAuthenticator {
public:
  // Before 1.10.0 use MOCK_METHOD1
  MOCK_METHOD(bool, login, (std::string username, std::string password));
  MOCK_METHOD(bool, logout, (std::string username));

public: // other methods required by interface
  void something() override {}
};

TEST(Service, WithNotDerivingMock) {
  std::cout << "------------------------------\n";
  using ::testing::_; // _ is the joker argument for expected calls
  using ::testing::DoDefault;
  using ::testing::InSequence;
  using ::testing::Return;

  MockNotDerivingAuth mock_auth;
  Service service(&mock_auth);

  std::string username = "Goldorak";
  std::string password = "cornofulgure";

  InSequence s; // will force expected ordered calls

  ON_CALL(mock_auth, login(_, _)).WillByDefault(Return(true));

  EXPECT_CALL(mock_auth, login(username, password)).Times(1).WillOnce(DoDefault());
  EXPECT_CALL(mock_auth, logout(username))
      .Times(1)
      .WillOnce(Return(true)); // caught from Auth destructor
  ASSERT_EQ(service.init(username, password), 0);
  service.something();
}

// This is the default main.
// If not defined gtest_main will do it for you.
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
