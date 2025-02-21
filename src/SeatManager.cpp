#include "../include/SeatManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

const int ROWS = 10; // Number of rows in the airplane
const int SEATS_PER_ROW = 6; // Number of seats per row
const string SEAT_LABELS = "ABCDEF"; // Seat labels for each column

SeatManager::SeatManager() : seats(ROWS, std::vector<bool>(SEATS_PER_ROW, false)) {}

// Function to display the seating arrangement
void SeatManager::displaySeats() const {
    cout << "   A B C  D E F" << endl; // Seat labels
    for (int i = 0; i < ROWS; i++) {
        cout << setw(2) << i + 1 << " "; // Row number
        for (int j = 0; j < SEATS_PER_ROW; j++) {
            if (j == 3) cout << " "; // Gap between seats
            cout << (seats[i][j] ? 'X' : 'O') << " "; // 'X' for occupied, 'O' for available
        }
        cout << endl;
    }
}

void SeatManager::saveData(const std::string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& row : seats) {
            for (bool seat : row) {
                file << seat << " ";
            }
            file << endl;
        }
        file.close();
    } else {
        cout << "An error occured, please try again later." << endl;
    }
}

// Function to convert seat label (e.g., "1A") to row and column indices
bool SeatManager::convertSeatLabel(const std::string& label, int& row, int& col) const {
    if (label.length() < 2) return false;

    row = stoi(label.substr(0, label.length() - 1)) - 1; // Extract row number
    char seatLetter = toupper(label.back()); // Extract seat letter

    col = SEAT_LABELS.find(seatLetter); // Find column index from seat letter
    return row >= 0 && row < ROWS && col >= 0 && col < SEATS_PER_ROW;
}

// Book a single seat without saving to file
bool SeatManager::bookSeat(const std::string& label) {
    int row, col;
    if (!convertSeatLabel(label, row, col)) {
        // Throw exception for an invalid seat label.
        throw InvalidSeatLabelException(label);
    }
    if (seats[row][col]) {
        // Throw exception for already reserved seat.
        throw SeatAlreadyReservedException(label);
    }
    seats[row][col] = true;
    std::cout << "Seat " << label << " has been successfully booked.\n";
    return true;
}

bool SeatManager::bookSeats(const std::vector<std::string>& labels) {
    bool allBooked = true;
    // We'll collect messages for any failures.
    for (const auto& label : labels) {
        try {
            bookSeat(label);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            allBooked = false;
        }
    }
    return allBooked;
}


bool SeatManager::cancelReservation(const std::string& label) {
    int row, col;
    if (!convertSeatLabel(label, row, col)) {
        std::cout << "Invalid seat label: " << label << std::endl;
        return false;
    }
    if (!seats[row][col]) {
        std::cout << "Seat " << label << " is not reserved." << std::endl;
        return false;
    }
    seats[row][col] = false;
    return true;
}

void SeatManager::recommendSeats() const {
    cout << "Recommended available seats (Window: A/F, Aisle: C/D): ";
    for (int i = 0; i < ROWS; i++) {
        if (!seats[i][0]) cout << i + 1 << "A "; // Window seat A
        if (!seats[i][5]) cout << i + 1 << "F "; // Window seat F
        if (!seats[i][2]) cout << i + 1 << "C "; // Aisle seat C
        if (!seats[i][3]) cout << i + 1 << "D "; // Aisle seat D
    }
    cout << endl;
}

void SeatManager::loadData(const std::string& filename) {
    ifstream file(filename);
    int seatValue;
    if (file.is_open()) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < SEATS_PER_ROW; j++) {
                file >> seatValue;
                seats[i][j] = (seatValue != 0);
            }
        }
        file.close();
        cout << "Seat data loaded from " << filename << endl;
    } else {
        cout << "No existing seat data found. Starting with empty seats." << endl;
    }
}
