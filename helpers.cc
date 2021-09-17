#include <iostream>
#include <string>
#include <vector>

// THESE ARE SOME HELPER METHODS
using std::string;

// print some string to the out stream
// add end of line at the end
void print(string s) {
  std::cout << s << std::endl;
}

// print some string to the out stream
// this will print with red foreground in the terminal
void print_error(string s) {
  printf("\033[0;31;49m%s\033[0m", s.c_str());
}

// print some string to the out stream
// this will print with red foreground in the terminal
void print_success(string s) {
  printf("\033[0;32;49m%s\033[0m", s.c_str());
}

// Get user input and print some given string
// return user input value
string string_input(string s) {
  if (s.empty() == false) {
    std::cout << s << ": ";
  };

  string value;
  getline(std::cin, value);
  return value;
}

// Get user input and print some given string
// return user input value as integer
int number_input(string s) {
  string input = string_input(s);
  try {
    int number = std::stoi(input);
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
int menu_input(string title, string question, std::vector<string> selections) {
  // Construct dialog from title and selections
  // Each selection will be printed with format <number>. <selection>\n
  string dialog = "============MENU============\n";
  dialog.append(title);
  dialog.append("\n");
  for (int i = 0; i < selections.size(); i++) {
    dialog.append(std::to_string(i + 1));
    dialog.append(". ");
    dialog.append(selections[i]);
    dialog.append("\n");
  }
  dialog.append("============================\n");
  dialog.append(question);
  int selected_number = number_input(dialog);

  // Validation
  // Self recall if invalid
  if ((selected_number <= 0) || (selected_number > selections.size())) {
    print("Invalid menu selection. Please try again!");
    return menu_input(title, question, selections);
  }

  return selected_number;
}