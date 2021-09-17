#include <vector>

#include "program.cc"

int create_customer();
int get_customer_bill();
Program* program = new Program();

int main() {
  std::vector<std::string> selections;
  selections.push_back("Sign Up");
  selections.push_back("Bill");
  selections.push_back("Exit");

  std::string title = "Welcome to Utility Inc.";
  std::string question = "Please input the number associated with the menu";
  int selected = menu_input(title, question, selections);

  if (selected == 1) {
    return create_customer();
  } else if (selected == 2) {
    return get_customer_bill();
  } else if (selected == 3) {
    return 0;
  } else {
    return 1;
  }
}

// Create customer flow
// This will create new customer in the program
int create_customer() {
  Customer customer = program->create_customer();
  std::string success_message = "Congratulation a new user has been created with details:\n";
  success_message.append("identifier: " + customer.description() + "\n");
  success_message.append("name: " + customer.name + "\n");
  success_message.append("address: " + customer.address + "\n");
  print_success(success_message);
  return main();
}

// This will get customer bill from using customer id given by the user
// Then the program will print all information related to the customer and the bill
// The program will be reattempt if the customer with given id not found
int get_customer_bill() {
  std::string dialog = "Please input your customer identifier";
  std::string input_id = string_input(dialog);

  // Try to get customer id
  uint64_t customer_id;
  try {
    customer_id = std::stoull(input_id);
  } catch (...) {
    print_error("The customer identifier should only have number. Please try again or ctrl+c to exit!\n");
    return get_customer_bill();
  }

  // Try to get customer
  Customer customer;
  try {
    customer = program->get_customer(customer_id);
  } catch (...) {
    std::string error_message = "Sorry, The user with customer identifier ";
    error_message.append(input_id);
    error_message.append(" not found.");
    error_message.append(" Please try again!\n");
    print_error(error_message);
    return main();
  }

  double customer_usage_amount = customer.bill.get_usage_amount();
  double customer_past_due_amount = customer.bill.past_due_amount;
  double total_amount = customer_usage_amount + customer_past_due_amount;
  print("Here are the details we found for you regarding this month bill:");
  print("\n==========CUSTOMER==========");
  printf("* Identifier: %llu\n", customer.id);
  printf("* Name: %s\n", customer.name.c_str());
  printf("* Address: %s\n", customer.address.c_str());
  print("============BILL============");
  printf("* Current Usage: %d m cubic\n", customer.bill.current_usage);
  printf("* Current Amount: $%.2f\n", customer_usage_amount);
  printf("* Past Due Amount: $%.2f\n", customer_past_due_amount);

  printf("* Total amount: $%.2f\n", total_amount);
  print("============================\n");
  return main();
}