#include <iostream>

class subforwardlist {
    int data;
    subforwardlist* next;

public:
    subforwardlist() : data(0), next(nullptr) {}
    
    // Конструктор копирования
    subforwardlist(const subforwardlist& other) : data(other.data), next(nullptr) {
    }
    
    // Оператор присваивания копированием
    subforwardlist& operator=(const subforwardlist& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }
    
    // Конструктор перемещения
    subforwardlist(subforwardlist&& other)
        : data(other.data), next(other.next) {
        other.next = nullptr;
        other.data = 0;
    }
    
    // Оператор присваивания перемещением
    subforwardlist& operator=(subforwardlist&& other) {
        if (this != &other) {
            data = other.data;
            next = other.next;
            
            other.next = nullptr;
            other.data = 0;
        }
        return *this;
    }
    
    // Деструктор
    ~subforwardlist() = default;

    void swap(subforwardlist& other) {
        using std::swap;
        swap(data, other.data);
        swap(next, other.next);
    }

public:
    bool init(subforwardlist** sfl) {
        *sfl = nullptr;
        return true;
    }

    bool push_back(subforwardlist** sfl, int d) {
        subforwardlist* new_node = new subforwardlist;
        new_node->data = d;
        new_node->next = nullptr;
        
        if (*sfl == nullptr) {
            *sfl = new_node;
        } else {
            subforwardlist* current = *sfl;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
        }
        return true;
    }

    int pop_back(subforwardlist** sfl) {
        if (*sfl == nullptr) {
            return 0;
        }
        
        if ((*sfl)->next == nullptr) {
            int data = (*sfl)->data;
            delete *sfl;
            *sfl = nullptr;
            return data;
        }
        
        subforwardlist* current = *sfl;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        
        int data = current->next->data;
        delete current->next;
        current->next = nullptr;
        return data;
    }

    bool push_forward(subforwardlist** sfl, int d) {
        subforwardlist* new_node = new subforwardlist;
        new_node->data = d;
        new_node->next = *sfl;
        *sfl = new_node;
        return true;
    }

    int pop_forward(subforwardlist** sfl) {
        if (*sfl == nullptr) {
            return 0;
        }
        
        subforwardlist* temp = *sfl;
        int data = temp->data;
        *sfl = (*sfl)->next;
        delete temp;
        return data;
    }

    bool push_where(subforwardlist** sfl, unsigned int where, int d) {
        if (where == 0) {
            return push_forward(sfl, d);
        }
        
        subforwardlist* current = *sfl;
        for (unsigned int i = 0; i < where - 1 && current != nullptr; i++) {
            current = current->next;
        }
        
        if (current == nullptr) {
            return false;
        }
        
        subforwardlist* new_node = new subforwardlist;
        new_node->data = d;
        new_node->next = current->next;
        current->next = new_node;
        return true;
    }

    int erase_where(subforwardlist** sfl, unsigned int where) {
        if (*sfl == nullptr) {
            return 0;
        }
        
        if (where == 0) {
            return pop_forward(sfl);
        }
        
        subforwardlist* current = *sfl;
        for (unsigned int i = 0; i < where - 1 && current != nullptr; i++) {
            current = current->next;
        }
        
        if (current == nullptr || current->next == nullptr) {
            return 0;
        }
        
        subforwardlist* temp = current->next;
        int data = temp->data;
        current->next = temp->next;
        delete temp;
        return data;
    }

    unsigned int size(subforwardlist** sfl) {
        unsigned int count = 0;
        subforwardlist* current = *sfl;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    void clear(subforwardlist** sfl) {
        while (*sfl != nullptr) {
            subforwardlist* temp = *sfl;
            *sfl = (*sfl)->next;
            delete temp;
        }
    }
};


class subvector {
private:
    int* mas = nullptr;
    unsigned int top = 0;
    unsigned int capacity = 0;

public:
    // Конструктор по умолчанию
    subvector() = default;

    // Конструктор с начальной емкостью
    subvector(unsigned int initial_capacity) {
        if (initial_capacity > 0) {
            mas = new int[initial_capacity];
            capacity = initial_capacity;
        }
    }

    // Деструктор
    ~subvector() {
        delete[] mas;
    }

    // Конструктор копирования
    subvector(const subvector& other) {
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
    subvector& operator=(const subvector& other) {
        if (this != &other) {
            subvector temp(other);
            
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
    subvector(subvector&& other) 
        : mas(other.mas), top(other.top), capacity(other.capacity) {
        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }

    // Оператор присваивания перемещением
    subvector& operator=(subvector&& other){
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

    void swap(subvector& other) {
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
