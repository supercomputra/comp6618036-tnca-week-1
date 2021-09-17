// #include <format>
#include <iostream>
#include <string>
#include <vector>

#include "program.cc"

int create_customer();
int customer_bill();
Program* program = new Program();

int main() {
  // Build selections from 3 different selections
  std::vector<string> selections;
  selections.push_back("Sign Up");
  selections.push_back("Bill");
  selections.push_back("Exit");

  int selected = menu_input("Welcome to Utility Inc.", "Please input the number associated with the menu", selections);
  if (selected == 1) {
    return create_customer();
  } else if (selected == 2) {
    return customer_bill();
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
  string success_message = "Congratulation a new user has been created with details: ";
  success_message.append("\nidentifier: ");
  success_message.append(customer.identifier);
  success_message.append("\nname: ");
  success_message.append(customer.name);
  success_message.append("\naddress: ");
  success_message.append(customer.address);
  success_message.append("\n");
  print_success(success_message);

  return main();
}

// Get the customer bill
int customer_bill() {
  string id_input_dialog = "Please input your customer identifier";
  string customer_id = string_input(id_input_dialog);
  try {
    Customer current = program->customer(customer_id);
    double current_usage_amount = program->usage_amount(current.bill);
    double current_past_due_amount = current.bill.past_due_amount;
    print("Here are the details we found for you regarding this month bill:");
    print("\n==========CUSTOMER==========");
    printf("* Identifier: %s\n", current.identifier.c_str());
    printf("* Name: %s\n", current.name.c_str());
    printf("* Address: %s\n", current.address.c_str());
    print("============BILL============");
    printf("* Past Due Amount: $%.2f\n", current_past_due_amount);
    printf("* Current Amount: $%.2f\n", current_usage_amount);
    printf("* Total amount: $%.2f\n", current_usage_amount + current_past_due_amount);
    print("============================\n");
    return main();
  } catch (...) {
    string error_message = "Sorry, The user with customer identifier ";
    error_message.append(customer_id);
    error_message.append(" not found.");
    error_message.append(" Please try again!\n");
    print_error(error_message);
    return main();
  }
}