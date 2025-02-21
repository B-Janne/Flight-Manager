#include "../include/SeatManager.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

int main() {
    SeatManager manager;
    const std::string filename = "./data/seat_data.txt";
    manager.loadData(filename);

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Display seats\n";
        cout << "2. Book seats\n";
        cout << "3. Cancel reservation\n";
        cout << "4. Recommend seats\n";
        cout << "5. Save and exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        // Clear the newline character from input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                manager.displaySeats();
                break;
            case 2: {
                bool bookingSuccess = false;
                while (!bookingSuccess) {
                    cout << "\nEnter seat labels to book (e.g., 1A 2B), or type 'quit' to cancel: ";
                    string input;
                    getline(cin, input);

                    if (input == "quit") {
                        cout << "Booking cancelled.\n";
                        break;
                    }
                    if (input.empty()) {
                        cout << "No seats entered. Try again.\n";
                        continue;
                    }
                    istringstream iss(input);
                    vector<string> labels;
                    string label;
                    while (iss >> label) {
                        labels.push_back(label);
                    }
                    // Call bookSeats and check if all seats booked successfully.
                    bookingSuccess = manager.bookSeats(labels);
                }
                break;
            }
            case 3: {
                cout << "Enter seat to cancel (e.g., 1A): ";
                string label;
                cin >> label;
                if (manager.cancelReservation(label)) {
                    cout << "Reservation canceled successfully.\n";
                } else {
                    cout << "Failed to cancel reservation.\n";
                }
                break;
            }
            case 4:
                manager.recommendSeats();
                break;
            case 5:
                manager.saveData(filename);
                cout << "Exiting program. Thank you!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
