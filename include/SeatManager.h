#ifndef SEATMANAGER_H
#define SEATMANAGER_H

#include <stdexcept>
#include <vector>
#include <string>

class InvalidSeatLabelException : public std::runtime_error {
public:
    InvalidSeatLabelException(const std::string& label)
        : std::runtime_error("Invalid seat label: " + label) {}
};

class SeatAlreadyReservedException : public std::runtime_error {
public:
    SeatAlreadyReservedException(const std::string& label)
        : std::runtime_error("Seat " + label + " is already reserved.") {}
};

class SeatManager {
public:
    SeatManager();
    // void displaySeats(const std::vector<std::vector<bool>>& seats) const;
    void displaySeats() const;
    bool bookSeats(const std::vector<std::string>& labels);
    bool cancelReservation(const std::string& label);
    void recommendSeats() const;
    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);

private:
    std::vector<std::vector<bool>> seats;
    bool bookSeat(const std::string& label); // Now throws exceptions if needed
    bool convertSeatLabel(const std::string& label, int& row, int& col) const;
};

#endif 