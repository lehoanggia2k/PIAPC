#include <iostream>
#include <string>
#include <regex>

class Context {
private:
    std::string text;

public:
    void setText(const std::string& t) {
        text = t;
    }

    std::string getText() const {
        return text;
    }

    void interpret() {
        // Sửa lỗi dấu gạch nối thành dấu gạch ngang
        std::regex regexReplaceUnderscore("-");
        text = std::regex_replace(text, regexReplaceUnderscore, "_");

        // Sửa lỗi khoảng trắng dư thừa
        std::regex regexReplaceMultipleSpaces("\\s+");
        text = std::regex_replace(text, regexReplaceMultipleSpaces, " ");

        // Thêm các quy tắc khác ở đây nếu cần
        std::regex regexMultipleNewlines("\n{2,}");
        text = std::regex_replace(text, regexMultipleNewlines, "\n");
    }
};

int main() {
    Context context;
    context.setText("Ví dụ về sửa lỗi - dấu gạch nối và  \n \n     \n    \n \n  khoảng trắng dư thừa.");

    std::cout << "Văn bản gốc: " << context.getText() << std::endl;

    // Thực hiện sửa lỗi cấu trúc trong văn bản
    context.interpret();

    std::cout << "Văn bản đã sửa lỗi: " << context.getText() << std::endl;

    return 0;
}
