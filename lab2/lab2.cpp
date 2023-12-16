#include <iostream>
#include <vector>

// Định nghĩa các lớp tài xế và hành khách
// Lớp tài xế
class Driver {
public:
    virtual bool IsReady(bool status) = 0;
    virtual void Drive() = 0;
};

// Lớp tài xế cho xe buýt
class BusDriver : public Driver {
public:
    bool IsReady(bool status) override {
        return status;
    }
    void Drive() override {
        std::cout << "Автобус выехал!\n";
    }
};

// Lớp tài xế cho taxi
class TaxiDriver : public Driver {
public:
    bool IsReady(bool status) override {
        return status;
    }
    void Drive() override {
        std::cout << "Такси выехало!\n";
    }
};

// Lớp hành khách
class Passenger {
public:
    virtual bool IsReady(bool status) = 0;
    virtual void Board() = 0;
};

// Lớp hành khách cho xe buýt
class BusPassenger : public Passenger {
public:
    bool IsReady(bool status) override {
        return status;
    }
    void Board() override {
        std::cout << "Пассажиры сели в автобус!\n";
    }
};

// Lớp hành khách cho taxi
class TaxiPassenger : public Passenger {
public:
    bool IsReady(bool status) override {
        return status;
    }
    void Board() override {
        std::cout << "Пассажиры сели в такси!\n";
    }
    void AddChildSeat() {
        std::cout << "В такси добавлены детские кресла!\n";
    }
};

// Factory để tạo ra các loại xe

// Factory trừu tượng
class TransportFactory {
public:
    virtual Driver* CreateDriver() = 0;
    virtual Passenger* CreatePassenger() = 0;
    virtual bool CheckAvailability(int passengersCount) = 0;
};

// Factory cho xe buýt
class BusFactory : public TransportFactory {
public:
    Driver* CreateDriver() override {
        return new BusDriver();
    }

    Passenger* CreatePassenger() override {
        return new BusPassenger();
    }

    bool CheckAvailability(int passengersCount) override {
        return passengersCount <= 30;
    }
};

// Factory cho taxi
class TaxiFactory : public TransportFactory {
public:
    Driver* CreateDriver() override {
        return new TaxiDriver();
    }

    Passenger* CreatePassenger() override {
        return new TaxiPassenger();
    }

    bool CheckAvailability(int passengersCount) override {
        return passengersCount <= 4;
    }
};

int main() {
    // Sử dụng Abstract Factory
    TransportFactory* busFactory = new BusFactory();
    TransportFactory* taxiFactory = new TaxiFactory();

    // Kiểm tra số lượng hành khách
    int busPassengerCount = 20;
    int taxiPassengerCount = 3;
    
    // Kiểm tra trạng thái của tài xế và hành khách
    bool busPassengerStatus = true;
    bool taxiPassengerStatus = true;
    bool busDriverStatus = true;
    bool taxiDriverStatus = true;
    bool taxiChildSeat = true;

    if (busFactory->CheckAvailability(busPassengerCount)) {
        std::cout << "Автобус готов к отправлению!\n";
        Driver* busDriver = busFactory->CreateDriver();
        Passenger* busPassenger = busFactory->CreatePassenger();

        if (busDriver->IsReady(busDriverStatus) && busPassenger->IsReady(busPassengerStatus)) {
            busPassenger->Board();
            busDriver->Drive();
        } else {
            std::cout << "Не имеет права вылетать!\n";
        }
    } else {
        std::cout << "Автобус не может отправиться из-за превышения допустимого количества пассажиров!\n";
    }

    if (taxiFactory->CheckAvailability(taxiPassengerCount)) {
        std::cout << "Такси готово к отправлению!\n";
        Driver* taxiDriver = taxiFactory->CreateDriver();
        Passenger* taxiPassenger = taxiFactory->CreatePassenger();

        //dynamic_cast được sử dụng để kiểm tra xem con trỏ taxiPassenger có thể chuyển đổi sang TaxiPassenger không.
         if (taxiDriver->IsReady(taxiDriverStatus) && taxiPassenger->IsReady(taxiPassengerStatus)) {
            TaxiPassenger* specificTaxiPassenger = dynamic_cast<TaxiPassenger*>(taxiPassenger);         
            if (specificTaxiPassenger) {
                if (taxiChildSeat) {
                    specificTaxiPassenger->AddChildSeat();
                    }
                }
            taxiPassenger->Board();
            taxiDriver->Drive();
            } else {
            std::cout << "Не имеет права вылетать!\n";
        }

    } else {
        std::cout << "Такси не может отправиться из-за превышения допустимого количества пассажиров!\n";
    }

    return 0;
}