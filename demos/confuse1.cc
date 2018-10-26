#include <iostream>
//using namespace std;

struct User {
  virtual void print(int i) {
	  std::cout << "I'm user " << i << "\n";
  }
};

// attacker-created structure in memory
struct Evil {
  virtual void executeMaliciousCode(double i) {
	  std::cout << "Malicious code executed " << "\n";
  }
};

int main(int argc, const char *argv[]) {
  Evil *evil = new Evil();
  User *user = new User();
  // type confusion vulnerability
  user = reinterpret_cast<User*>(evil);
  user->print(2);
  return 0;
}

