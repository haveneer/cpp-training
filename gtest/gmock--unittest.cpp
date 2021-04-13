#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

class DBAuthenticator {
public:
  virtual bool login(std::string username, std::string password) {
    std::cout << "DBAuthenticator::login call\n";
    return true;
  }
  virtual bool logout(std::string username) {
    std::cout << "DBAuthenticator::logout call\n";
    return true;
  }
};

template <typename DBAuthT> class Database {
public:
  explicit Database(DBAuthT &db_auth) : m_db_auth(db_auth) {}
  int init(std::string username, std::string password) {
    if (m_db_auth.login(username, password) != true) {
      std::cerr << "DB init failed" << std::endl;
      return -1;
    } else {
      std::cout << "DB init succeeded" << std::endl;
      m_username = username;
      return 0;
    }
  }
  virtual ~Database() { m_db_auth.logout(m_username); }

private:
  DBAuthT &m_db_auth;
  std::string m_username;
};

// Direct test without mock
TEST(Database, WithoutMock) {
  DBAuthenticator auth;
  Database<DBAuthenticator> db(auth);

  std::string username = "Goldorak";
  std::string password = "cornofulgure";

  ASSERT_EQ(db.init(username, password), 0);
}

// Test with deriving mock of DBAuth
class MockDerivingDBAuth : public DBAuthenticator {
public:
  // Before 1.10.0 use MOCK_METHOD1
  MOCK_METHOD(bool, login, (std::string username, std::string password), (override));
  MOCK_METHOD(bool, logout, (std::string username), (override));
};

TEST(Database, WithDerivingMock) {
  using ::testing::_; // _ is the joker argument for expected calls
  using ::testing::InSequence;
  using ::testing::Invoke;
  using ::testing::Return;

  MockDerivingDBAuth mock_auth;
  Database<DBAuthenticator> db(mock_auth);
  DBAuthenticator true_auth;

  std::string username = "Goldorak";
  std::string password = "cornofulgure";

  InSequence s; // will force expected ordered calls

  EXPECT_CALL(mock_auth, login(username, password)).Times(1).WillOnce(Return(true));

  EXPECT_CALL(mock_auth, logout(username)) // caught from Database destructor
      .Times(1)
      .WillOnce(Invoke(
          &true_auth,
          &DBAuthenticator::logout)); // redirect call to another object/method

  ASSERT_EQ(db.init(username, password), 0);
}

// Test with not deriving mock of DBAuth
class MockNotDerivingDBAuth /* : public DBAuthenticator */ {
public:
  // Before 1.10.0 use MOCK_METHOD1
  MOCK_METHOD(bool, login, (std::string username, std::string password));
  MOCK_METHOD(bool, logout, (std::string username));
};

TEST(Database, WithNotDerivingMock) {
  using ::testing::_; // _ is the joker argument for expected calls
  using ::testing::DoDefault;
  using ::testing::InSequence;
  using ::testing::Return;

  MockNotDerivingDBAuth mock_auth;
  Database<MockNotDerivingDBAuth> db(mock_auth);

  std::string username = "Goldorak";
  std::string password = "cornofulgure";

  InSequence s; // will force expected ordered calls

  ON_CALL(mock_auth, login(_, _)).WillByDefault(Return(true));

  EXPECT_CALL(mock_auth, login(username, password)).Times(1).WillOnce(DoDefault());
  EXPECT_CALL(mock_auth, logout(username))
      .Times(1)
      .WillOnce(Return(true)); // caught from Database destructor
  ASSERT_EQ(db.init(username, password), 0);
}

// This is the default main.
// If not defined gtest_main will do it for you.
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
