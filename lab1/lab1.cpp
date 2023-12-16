#include <iostream>
#include <vector>

// Định nghĩa các lớp tài xế và hành khách

// Lớp tài xế
class Driver {
public:
    virtual void Drive() = 0;
};

// Lớp tài xế cho xe buýt
class BusDriver : public Driver {
public:
    void Drive() override {
        std::cout << "Автобус выехал!\n";
    }
};

// Lớp tài xế cho taxi
class TaxiDriver : public Driver {
public:
    void Drive() override {
        std::cout << "Такси выехало!\n";
    }
};

// Lớp hành khách
class Passenger {
public:
    virtual void Board() = 0;
};

// Lớp hành khách cho xe buýt
class BusPassenger : public Passenger {
public:
    void Board() override {
        std::cout << "Пассажиры сели в автобус!\n";
    }
};

// Lớp hành khách cho taxi
class TaxiPassenger : public Passenger {
public:
    void Board() override {
        std::cout << "Пассажиры сели в такси!\n";
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
    int taxiPassengerCount = 5; 

    if (busFactory->CheckAvailability(busPassengerCount)) {
        std::cout << "Автобус готов к отправлению!\n";
        Driver* busDriver = busFactory->CreateDriver();
        Passenger* busPassenger = busFactory->CreatePassenger();
        busPassenger->Board();
        busDriver->Drive();
    } else {
        std::cout << "Автобус не может отправиться из-за превышения допустимого количества пассажиров!\n";
    }

    if (taxiFactory->CheckAvailability(taxiPassengerCount)) {
        std::cout << "Такси готово к отправлению!\n";
        Driver* taxiDriver = taxiFactory->CreateDriver();
        Passenger* taxiPassenger = taxiFactory->CreatePassenger();
        taxiPassenger->Board();
        taxiDriver->Drive();
    } else {
        std::cout << "Такси не может отправиться из-за превышения допустимого количества пассажиров!\n";
    }

    return 0;
}


/*(Xe sẽ không di chuyển nếu không có tài xế): Đây được triển khai trong các phương thức Drive() của BusDriver và TaxiDriver, khi chúng thông báo rằng xe đã xuất phát.

(Hai tài xế không thể cùng đi trong một chiếc xe): Điều này được thể hiện trong việc tạo tài xế từ Factory (CreateDriver()) - chỉ một tài xế được tạo ra cho mỗi loại xe buýt hoặc taxi.

(Xe sẽ không di chuyển nếu không có hành khách): Tương tự như tài xế, khi gọi phương thức Board() từ BusPassenger hoặc TaxiPassenger, thông điệp được in ra khi hành khách lên xe.

(Có giới hạn số người có thể được chở. Đối với xe buýt là 30 người. Đối với taxi là 4 người): */