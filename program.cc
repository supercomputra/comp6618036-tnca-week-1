#include <chrono>
#include <string>
#include <unordered_map>
#include <vector>

#include "customer.cc"

// Avoid using namespace
// This to prevent unexpected collision

class Program {
 private:
  // map customer id to customer value
  std::unordered_map<uint64_t, Customer> customers_map;

  // map customer id to customer existance
  std::unordered_map<uint64_t, bool> customers_existance_map;

  void save_customer(Customer customer) {
    this->customers_map[customer.id] = customer;
    this->customers_existance_map[customer.id] = true;
  }

 public:
  // Create customer value
  // The bill will be generated random
  Customer create_customer() {
    std::string customer_name = string_input("Please input your name");
    std::string customer_address = string_input("Please input your address");
    Bill customer_bill = Bill::create_random_bill();
    Customer customer = {
        .id = current_timestamp(),
        .name = customer_name,
        .address = customer_address,
        .bill = customer_bill};
    this->save_customer(customer);
    return customer;
  }

  // Getting the customer with given identifier
  // The function will throw if not found
  // This method throw an exception if customer with given id not found
  Customer get_customer(uint64_t customer_id) {
    if (this->customers_existance_map[customer_id] == false) {
      throw "Not Found";
    }

    Customer customer = this->customers_map[customer_id];
    return customer;
  }
};