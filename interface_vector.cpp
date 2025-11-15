#include <iostream>

class Subvector {
private:
    int* mas = nullptr;
    unsigned int top = 0;
    unsigned int capacity = 0;

public:
    // Конструктор по умолчанию
    Subvector() = default;

    // Конструктор с начальной емкостью
    explicit Subvector(unsigned int initial_capacity) {
        if (initial_capacity > 0) {
            mas = new int[initial_capacity];
            capacity = initial_capacity;
        }
    }

    // Деструктор
    ~Subvector() {
        delete[] mas;
    }

    // Конструктор копирования
    Subvector(const Subvector& other) {
        if (other.top > 0) {
            mas = new int[other.capacity];
            for (unsigned int i = 0; i < other.top; i++) {
                mas[i] = other.mas[i];
            }
            top = other.top;
            capacity = other.capacity;
        }
    }

    // Оператор присваивания копированием
    Subvector& operator=(const Subvector& other) {
        if (this != &other) {
            Subvector temp(other);
            
            swap(temp);

            int* new_mas = temp.mas;
            temp.mas = mas;
            mas = new_mas;

            int new_top = temp.top;
            temp.top = top;
            top = new_top;

            int new_capacity = temp.capacity;
            temp.capacity = capacity;
            capacity = new_capacity;
        }
        return *this;
    }

    // Конструктор перемещения
    Subvector(Subvector&& other) 
        : mas(other.mas), top(other.top), capacity(other.capacity) {
        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }

    // Оператор присваивания перемещением
    Subvector& operator=(Subvector&& other){
        if (this != &other) {
            delete[] mas;
            
            mas = other.mas;
            top = other.top;
            capacity = other.capacity;
            
            other.mas = nullptr;
            other.top = 0;
            other.capacity = 0;
        }
        return *this;
    }

    void swap(Subvector& other) {
        int* new_mas = other.mas;
        other.mas = mas;
        mas = new_mas;

        int new_top = other.top;
        other.top = top;
        top = new_top;

        int new_capacity = other.capacity;
        other.capacity = capacity;
        capacity = new_capacity;
    }

public:
    bool resize(unsigned int new_capacity) {
        if (new_capacity == 0) {
            delete[] mas;
            mas = nullptr;
            capacity = 0;
            top = 0;
            return true;
        }
        
        if (new_capacity == capacity) {
            return true;
        }
        
        int* new_mas = new int[new_capacity];
        
        unsigned int elements_to_copy = std::min(top, new_capacity);
        for (unsigned int i = 0; i < elements_to_copy; i++) {
            new_mas[i] = mas[i];
        }
        
        delete[] mas;
        mas = new_mas;
        capacity = new_capacity;
        top = elements_to_copy;
        
        return true;
    }

    bool push_back(int d) {
        if (top == capacity) {
            unsigned int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            if (!resize(new_capacity)) {
                return false;
            }
        }
        
        mas[top] = d;
        top++;
        return true;
    }

    int pop_back() {
        if (top == 0) {
            return 0;
        }
        
        top--;
        return mas[top];
    }

    void shrink_to_fit() {
        if (top == 0) {
            delete[] mas;
            mas = nullptr;
            capacity = 0;
        } else if (top < capacity) {
            int* new_mas = new int[top];
            
            for (unsigned int i = 0; i < top; i++) {
                new_mas[i] = mas[i];
            }
            
            delete[] mas;
            mas = new_mas;
            capacity = top;
        }
    }

    void clear() {
        top = 0;
    }
};