#include <stdio.h>

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

// Avoid using namespace
// This to prevent unexpected collision
using std::int64_t;
using std::string;
using std::to_string;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::chrono::time_point;

// Helpers prototype
void print(string s);
string input(string s);
int number_input(string s);
int menu_input(string title, std::vector<string> selections);

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
    std::vector<Customer> customers;

    // Get current timestamp in milliseconds
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
        string customer_name = input("Please input your name:");
        string customer_address = input("Please input your address:");
        string customer_id = to_string(current_timestamp());
        Bill customer_bill = create_random_bill();
        Customer customer{customer_id, customer_name, customer_address, customer_bill};
        customers.push_back(customer);
        return customer;
    }

    // Create random bill value
    // The bill usage and past due amount will be random in each creation
    Bill create_random_bill() {
        int bill_usage = rand() % 30 + 90;                      // random from 30 to 120
        double bill_past_due_amount = random_double(100, 240);  // random double from 100.0 to 240.0
        Bill bill{bill_past_due_amount, bill_usage};
        return bill;
    }

    // I know we are iterating customers one by one
    // But C++ doesn't come with hash map for free
    // To keep the codebase not simple let's keep this O(n) solution
    Customer customer(string id) {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].identifier == id) {
                return customers[i];
            }
        }
        throw "User with given id not found";
    }

    double usage_amount(Bill bill) {
        if (bill.current_usage <= 60) {
            return 2.0 * bill.current_usage;
        } else {
            int over_limit = bill.current_usage - 60;
            return (60 * 2.0) + (over_limit * 1.75);
        }
    }
};

int main() {
    Program program;
    // Build selections from 3 different selections
    std::vector<string> selections;
    selections.push_back("Sign Up");
    selections.push_back("Bill");
    selections.push_back("Exit");

    int user_selection_number = menu_input("Please input the number associated with the menu:", selections);

    // Sign Up
    if (user_selection_number == 1) {
        Customer customer = program.create_customer();
        printf("Congratulation a user with identifier %s and name %s has successfully created!\n", customer.identifier.c_str(), customer.name.c_str());
        main();
    }

    // Bill
    else if (user_selection_number == 2) {
        string id_input_dialog = "Please input your customer identifier:";
        string customer_id = input(id_input_dialog);
        try {
            Customer current = program.customer(customer_id);
            double current_usage_amount = program.usage_amount(current.bill);
            double current_past_due_amount = current.bill.past_due_amount;
            print("\nHere are the details we found for you regarding this month bill:");
            print("\n=====CUSTOMER=====");
            printf("Identifier: %s\n", current.identifier.c_str());
            printf("Name: %s\n", current.name.c_str());
            printf("Address: %s\n", current.address.c_str());
            print("\n=======BILL=======");
            printf("Past Due Amount: %.2f\n", current_past_due_amount);
            printf("Current Amount: %.2f\n", current_usage_amount);
            printf("Total amount: %.2f\n", current_usage_amount + current_past_due_amount);
            main();
        } catch (...) {
            print("Sorry, The user with given customer identifier not found. Please sign up or try again!\n");
            main();
        }
    }

    // Exit
    else {
        return 1;  // Unexpected error
    }

    return 0;
}

// THESE ARE SOME HELPER METHODS

// print some string to the out stream
// add end of line at the end
void print(string s) {
    std::cout << s << std::endl;
}

// Get user input and print some given string
// return user input value
string input(string s) {
    if (s.empty() == false) {
        print(s);
    };

    string value;
    std::cin >> value;
    return value;
}

// Get user input and print some given string
// return user input value as integer
int number_input(string s) {
    string string_input = input(s);
    try {
        int number = std::stoi(string_input);
        return number;
    } catch (std::invalid_argument& e) {
        print("Invelid number");
        return number_input(s);
    } catch (std::out_of_range& e) {
        print("The number you input is out of range.");
        return number_input(s);
    } catch (...) {
        print("Something went wrong");
        return number_input(s);
    }
}

// Get user input as menu selection
// This method will call it self when receiviing unexpected input
int menu_input(string title, std::vector<string> selections) {
    // Construct dialog from title and selections
    string dialog = title;
    dialog.append("\n");
    for (int i = 0; i < selections.size(); i++) {
        dialog.append(to_string(i + 1));
        dialog.append(". ");
        dialog.append(selections[i]);
        dialog.append("\n");
    }
    int selected_number = number_input(dialog);

    // Validation
    // Self recall if invalid
    if ((selected_number <= 0) || (selected_number > selections.size())) {
        print("Invalid menu selection. Please try again!");
        return menu_input(title, selections);
    }
    return selected_number;
}