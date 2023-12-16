#include <iostream>
#include <vector>

class Observer;

// Giao diện Subject
class Subject {
public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

// Giao diện Observer
class Observer {
public:
    virtual void update(bool reportSubmitted) = 0;
};

// Chủ thể cụ thể
class TeacherProgress : public Subject {
private:
    bool reportSubmitted = false;
    std::vector<Observer*> observers;

public:
    void registerObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        // Xóa observer từ danh sách
        // Thực hiện logic này dựa trên yêu cầu của bạn
    }

    void notifyObservers() override {
        for (Observer* observer : observers) {
            observer->update(reportSubmitted);
        }
    }

    void setReportSubmitted(bool submitted) {
        reportSubmitted = submitted;
        notifyObservers();
    }

    bool isReportSubmitted() {
        return reportSubmitted;
    }
};

// Observer cụ thể
class DepartmentOffice : public Observer {
public:
    void update(bool reportSubmitted) override {
        if (!reportSubmitted) {
            std::cout << "Văn phòng khoa: Báo cáo tiến độ của giáo viên chưa được nộp đúng hạn!" << std::endl;
            // Thực hiện hành động để thông báo đến khoa
        } else {
            std::cout << "Văn phòng khoa: Báo cáo tiến độ của giáo viên đã được nộp đúng hạn." << std::endl;
        }
    }
};

int main() {
    TeacherProgress teacherProgress;

    // Tạo observers (trong trường hợp này, là văn phòng khoa)
    DepartmentOffice departmentOffice;

    // Đăng ký văn phòng khoa làm observer
    teacherProgress.registerObserver(&departmentOffice);

    // Mô phỏng giáo viên gửi báo cáo (bạn có thể thay đổi để mô phỏng việc nộp muộn)
    teacherProgress.setReportSubmitted(true); // Đổi giá trị này thành false để mô phỏng việc nộp muộn

    return 0;
}
