#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class ArrayBase {
public:
    virtual ~ArrayBase() = default;

    virtual void printArray() const = 0;
    virtual int productEvenElements() const = 0;
    virtual int sumBetweenZeros() const = 0;
    virtual void reorderArray() = 0;
};

class Array : public ArrayBase {
private:
    std::vector<int> array;

public:
    Array(int size) {
        array.resize(size);
        for (int& el : array) {
            el = rand() % 21 - 10;
        }
    }

    void printArray() const override {
        for (const int& el : array) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }

    int productEvenElements() const override {
        int product = 1;
        for (size_t i = 0; i < array.size(); i += 2) {
            product *= array[i];
        }
        return product;
    }

    int sumBetweenZeros() const override {
        int firstZeroIndex = -1;
        int lastZeroIndex = -1;
        for (size_t i = 0; i < array.size(); ++i) {
            if (array[i] == 0) {
                if (firstZeroIndex == -1) {
                    firstZeroIndex = i;
                }
                lastZeroIndex = i;
            }
        }

        if (firstZeroIndex == -1 || lastZeroIndex == -1 || firstZeroIndex == lastZeroIndex) {
            return 0; 
        }

        int sum = 0;
        for (size_t i = firstZeroIndex + 1; i < lastZeroIndex; ++i) {
            sum += array[i];
        }
        return sum;
    }

    void reorderArray() override {
        std::partition(array.begin(), array.end(), [](int x) { return x >= 0; });
    }
};

int main() {
    srand(time(0)); 
    int size;
    std::cout << "Enter size array: ";
    std::cin >> size;

    ArrayBase* container = new Array(size);

    std::cout << "Initial array: ";
    container->printArray();

    int product = container->productEvenElements();
    std::cout << "Product of array elements with even numbers: " << product << std::endl;

    int sum = container->sumBetweenZeros();
    std::cout << "Sum of elements between the first and last zeros: " << sum << std::endl;

    container->reorderArray();
    std::cout << "Organized array: ";
    container->printArray();

    delete container; 

    return 0;
}
