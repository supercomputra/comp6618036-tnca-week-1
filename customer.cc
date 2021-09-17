#include <string>

#include "bill.cc"

struct Customer {
  uint64_t id;
  std::string name;
  std::string address;
  Bill bill;

  std::string description() {
    return std::to_string(id);
  }
};