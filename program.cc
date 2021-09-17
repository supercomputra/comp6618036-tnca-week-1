#include <chrono>
#include <string>
#include <unordered_map>
#include <vector>

#include "helpers.cc"

// Avoid using namespace
// This to prevent unexpected collision
using std::int64_t;
using std::string;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::chrono::time_point;

struct Bill {
  double past_due_amount;  // In US Dollar
  int current_usage;       // In meter cubic
};

struct Customer {
  string identifier;
  string name;
  string address;
  Bill bill;
};

class Program {
 private:
  // All customers
  // Map with id aas the key and customer as the value
  std::unordered_map<string, Customer> customers_map;

  // Get current timestamp
  // The timestamp return as milliseconds since epoch
  int64_t current_timestamp() {
    time_point<system_clock> current = system_clock::now();
    milliseconds milliseconds_since_epoch = duration_cast<milliseconds>(current.time_since_epoch());
    return milliseconds_since_epoch.count();
  }

  // returns random double with given min and max bound
  // Only use to generate double value for bill's past due amount
  double random_double(double min, double max) {
    double f = rand() / (RAND_MAX + 1.0);
    return min + f * (max - min);
  }

 public:
  // Create customer value
  // The bill will be generated random
  Customer create_customer() {
    string customer_name = string_input("Please input your name");
    string customer_address = string_input("Please input your address");
    string customer_id = std::to_string(current_timestamp());
    Bill customer_bill = create_random_bill();
    Customer customer = {
        .identifier = customer_id,
        .name = customer_name,
        .address = customer_address,
        .bill = customer_bill};
    this->customers_map[customer_id] = customer;
    return customer;
  }

  // Create random bill value
  // The bill usage and past due amount will be random in each creation
  Bill create_random_bill() {
    int bill_usage = rand() % 30 + 90;                      // random from 30 to 120
    double bill_past_due_amount = random_double(100, 240);  // random double from 100.0 to 240.0
    Bill bill = {
        .past_due_amount = bill_past_due_amount,
        .current_usage = bill_usage};
    return bill;
  }

  // I know we are iterating customers one by one
  // But C++ doesn't come with hash map for free
  // To keep the codebase not simple let's keep this O(n) solution
  Customer customer(string id) {
    if (this->customers_map.find(id) == this->customers_map.end()) {
      throw "Not Found";
    }

    Customer customer = customers_map[id];
    return customer;
  }

  // Get usage amount
  // The value returned is calculated from the usage
  double usage_amount(Bill bill) {
    if (bill.current_usage <= 60) {
      return 2.0 * bill.current_usage;
    } else {
      int over_limit = bill.current_usage - 60;
      return (60 * 2.0) + (over_limit * 1.75);
    }
  }
};