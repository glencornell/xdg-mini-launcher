#include "../src/process.hpp"
#include <gtest/gtest.h>

namespace {

  // The fixture for testing class Foo.
  class test_process : public ::testing::Test {
  protected:
    test_process() {
      // set-up work for each test:
    }

    virtual ~test_process() {
      // clean-up work that doesn't throw exceptions:
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
      // Code here will be called immediately after the constructor (right
      // before each test).
    }

    virtual void TearDown() {
      // Code here will be called immediately after each test (right
      // before the destructor).
    }
  };

  // Tests that the process class creates a child process:
  TEST_F(test_process, start_starts_a_child_process) {
    process p;
    std::vector<std::string> args;
    p.exec("/usr/bin/xclock", args);
    EXPECT_GT(p.pid(), 0);
  }

  // Tests that Foo does Xyz.
  TEST_F(test_process, DoesXyz) {
    // Exercises the Xyz feature of Foo.
  }

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
