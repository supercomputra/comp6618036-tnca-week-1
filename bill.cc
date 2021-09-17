#include "helpers.cc"

struct Bill {
  double past_due_amount;  // In US Dollar
  int current_usage;       // In meter cubic

  // Create random bill value
  // The bill usage and past due amount will be random in each creation
  // Bill usage will be generated random in range from 30 to 120
  // Past due amount will be generated in range from 100.0 to 240.0
  static Bill create_random_bill() {
    int bill_usage = rand() % 30 + 90;
    double bill_past_due_amount = random_double(100, 240);
    Bill bill = {
        .past_due_amount = bill_past_due_amount,
        .current_usage = bill_usage};
    return bill;
  }

  // Get usage amount
  // The value returned is calculated from the usage
  double get_usage_amount() {
    if (current_usage <= 60) {
      return 2.0 * current_usage;
    } else {
      int over_limit = current_usage - 60;
      return (60 * 2.0) + (over_limit * 1.75);
    }
  }
};