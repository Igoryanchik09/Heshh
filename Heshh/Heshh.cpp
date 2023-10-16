#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>

class MyBigInt {
private:
    std::bitset<64> binaryValue;

public:
    MyBigInt() {
        binaryValue = 0;
    }

    MyBigInt(const std::string& hexValue) {
        setHex(hexValue);
    }

    void setHex(const std::string& hexValue) {
        std::string binaryString = "";
        for (char c : hexValue) {
            unsigned int hexDigit;
            if (c >= '0' && c <= '9') {
                hexDigit = c - '0';
            }
            else if (c >= 'a' && c <= 'f') {
                hexDigit = c - 'a' + 10;
            }
            else if (c >= 'A' && c <= 'F') {
                hexDigit = c - 'A' + 10;
            }
            else {
                std::cerr << "Invalid hex digit: " << c << std::endl;
                return;
            }
            binaryString += std::bitset<4>(hexDigit).to_string();
        }
        binaryValue = std::bitset<64>(binaryString);
    }

    std::string getHex() const {
        std::string binaryString = binaryValue.to_string();
        std::string hexResult = "";
        for (size_t i = 0; i < binaryString.length(); i += 4) {
            std::string hexDigit = binaryString.substr(i, 4);
            int decimalValue = std::stoi(hexDigit, nullptr, 2);
            if (decimalValue < 10) {
                hexResult += static_cast<char>('0' + decimalValue);
            }
            else {
                hexResult += static_cast<char>('A' + (decimalValue - 10));
            }
        }
        return hexResult;
    }

    MyBigInt INV() const {
        MyBigInt result;
        result.binaryValue = ~binaryValue;
        return result;
    }

    MyBigInt XOR(const MyBigInt& other) const {
        MyBigInt result;
        result.binaryValue = binaryValue ^ other.binaryValue;
        return result;
    }

    MyBigInt OR(const MyBigInt& other) const {
        MyBigInt result;
        result.binaryValue = binaryValue | other.binaryValue;
        return result;
    }

    MyBigInt AND(const MyBigInt& other) const {
        MyBigInt result;
        result.binaryValue = binaryValue & other.binaryValue;
        return result;
    }

    MyBigInt shiftR(int n) const {
        MyBigInt result;
        result.binaryValue = binaryValue >> n;
        return result;
    }

    MyBigInt shiftL(int n) const {
        MyBigInt result;
        result.binaryValue = binaryValue << n;
        return result;
    }
};

int main() {
    MyBigInt numberA("51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    MyBigInt numberB("403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c");
    MyBigInt numberC = numberA.XOR(numberB);
    std::cout << "XOR result: " << numberC.getHex() << std::endl;

    MyBigInt invertedA = numberA.INV();
    std::cout << "INV result: " << invertedA.getHex() << std::endl;

    MyBigInt shiftedRightA = numberA.shiftR(10);
    std::cout << "Shift Right result: " << shiftedRightA.getHex() << std::endl;

    MyBigInt shiftedLeftA = numberA.shiftL(5);
    std::cout << "Shift Left result: " << shiftedLeftA.getHex() << std::endl;

    MyBigInt orResult = numberA.OR(numberB);
    std::cout << "OR result: " << orResult.getHex() << std::endl;

    MyBigInt andResult = numberA.AND(numberB);
    std::cout << "AND result: " << andResult.getHex() << std::endl;

    return 0;
}