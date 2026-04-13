#include <iostream>
#include <deque>
#include <string>

template <typename ElementType, typename UnderlyingContainer = std::deque<ElementType>>
class StackContainer {
private:
    UnderlyingContainer storage;

public:
    void add_to_top(const ElementType& item) {
        storage.push_back(item);
    }

    void remove_from_top() {
        if (!storage.empty()) {
            storage.pop_back();
        }
    }

    ElementType& get_top() {
        return storage.back();
    }

    const ElementType& get_top() const {
        return storage.back();
    }

    std::size_t get_size() const {
        return storage.size();
    }

    bool is_empty() const {
        return storage.empty();
    }
};

template <>
class StackContainer<char, std::string> {
private:
    std::string storage;

public:
    void add_to_top(char item) {
        storage.push_back(item);
    }

    void remove_from_top() {
        if (!storage.empty()) {
            storage.pop_back();
        }
    }

    char& get_top() {
        return storage.back();
    }

    const char& get_top() const {
        return storage.back();
    }

    std::size_t get_size() const {
        return storage.size();
    }

    bool is_empty() const {
        return storage.empty();
    }
};

template <typename StackType>
void display_stack_info(StackType& target_stack, const std::string& stack_description) {
    std::cout << stack_description << " top: " << target_stack.get_top() << '\n';
    
    target_stack.remove_from_top();
    std::cout << stack_description << " size: " << target_stack.get_size() << '\n';
    std::cout << stack_description << " is empty: " << (target_stack.is_empty() ? "yes" : "no") << '\n';
}

void demonstrate_integer_stack() {
    StackContainer<int> integer_stack;
    
    integer_stack.add_to_top(10);
    integer_stack.add_to_top(20);
    integer_stack.add_to_top(30);
    
    display_stack_info(integer_stack, "integer");
}

void demonstrate_character_stack() {
    StackContainer<char, std::string> character_stack;
    
    character_stack.add_to_top('a');
    character_stack.add_to_top('b');
    character_stack.add_to_top('c');
    
    display_stack_info(character_stack, "character");
}

int main() {
    std::cout << "=== INTEGER STACK DEMONSTRATION ===\n";
    demonstrate_integer_stack();
    
    std::cout << "\n=== CHARACTER STACK DEMONSTRATION ===\n";
    demonstrate_character_stack();
    
    return 0;
}