#include <iostream>
#include <vector>
#include <limits>

// Lớp gốc đối tượng Hành khách
class Passenger {
public:
    virtual int getLuggageWeight() = 0;
};

// Lớp gốc đối tượng Phi hành đoàn
class Crew : public Passenger {
public:
    int getLuggageWeight() override { return 0; }
};

// Lớp Phi công
class Pilot : public Crew {};
// Lớp Tiếp viên hàng không
class FlightAttendant : public Crew {};

// Lớp Hành khách thông thường
class RegularPassenger : public Passenger {
protected:
    int luggageWeight;

public:
    RegularPassenger(int weight) : luggageWeight(weight) {}

    int getLuggageWeight() override { return luggageWeight; }
};

// Lớp Hành khách Hạng nhất
class FirstClass : public RegularPassenger {
public:
    FirstClass(int weight) : RegularPassenger(weight) {}
};

// Lớp Hành khách Hạng thương gia
class BusinessClass : public RegularPassenger {
public:
    BusinessClass(int weight) : RegularPassenger(weight) {}
};

// Lớp Hành khách Hạng phổ thông
class EconomyClass : public RegularPassenger {
public:
    EconomyClass(int weight) : RegularPassenger(weight) {}
};

// Lớp cơ bản Đối tượng Máy bay
class AircraftClass {
public:
    virtual int getMaximumLuggageWeight() = 0;
    virtual void addPassenger(Passenger* passenger) = 0;
};

// Lớp Phân khúc Hạng nhất
class FirstClassSection : public AircraftClass {
private:
    std::vector<Passenger*> passengers;

public:
    int getMaximumLuggageWeight() override { return std::numeric_limits<int>::max(); }

    void addPassenger(Passenger* passenger) override {
        passengers.push_back(passenger);
    }

    std::vector<Passenger*>& getPassengers() { return passengers; }
};

// Lớp Phân khúc Hạng thương gia
class BusinessClassSection : public AircraftClass {
private:
    std::vector<Passenger*> passengers;

public:
    int getMaximumLuggageWeight() override { return 35; }

    void addPassenger(Passenger* passenger) override {
        passengers.push_back(passenger);
    }

    std::vector<Passenger*>& getPassengers() { return passengers; }
};

// Lớp Phân khúc Hạng phổ thông
class EconomyClassSection : public AircraftClass {
private:
    std::vector<Passenger*> passengers;

public:
    int getMaximumLuggageWeight() override { return 20; }

    void addPassenger(Passenger* passenger) override {
        passengers.push_back(passenger);
    }

    std::vector<Passenger*>& getPassengers() { return passengers; }
};

int main() {
    FirstClassSection firstSection;
    firstSection.addPassenger(new FirstClass(45));

    BusinessClassSection businessSection;
    businessSection.addPassenger(new BusinessClass(130));

    // Thêm các phân khúc khác nếu cần

    // Xử lý hành lý cho từng phân khúc
    int totalLuggageWeight = 0;
    AircraftClass* classes[] = { &firstSection, &businessSection }; // Thêm các phân khúc khác nếu cần
    for (auto aircraftClass : classes) {
        auto& classPassengers = static_cast<FirstClassSection*>(aircraftClass)->getPassengers();
        for (auto passenger : classPassengers) {
            totalLuggageWeight += passenger->getLuggageWeight();
        }
        if (totalLuggageWeight > aircraftClass->getMaximumLuggageWeight()) {
            std::cout << "Багаж превышает максимальный весa.\n";
            // Xử lý việc hành lý bị loại khỏi chuyến bay...
        }
        else {
            std::cout << "Общий вес багажа: " << totalLuggageWeight << "kg\n";
        }
        totalLuggageWeight = 0; // Reset trọng lượng tổng cho lớp tiếp theo
    }


    return 0;
}
