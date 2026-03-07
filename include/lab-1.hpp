#include<iostream>


using std::cout;
using std::cin;
using std::endl;

// int

// 2.1
void bin_float(float *n) {
    int *i = (int*) n;
    cout << "float: ";
    for(int j = 31; j >= 0; --j){
        cout << ((*i >> j) & 1);
        if (j == 31 || j == 23)
            cout << " ";
    }

    cout << endl << endl;
}
// value = (-1)^S × (1 + Mantissa) × 2^(Exp - 127)

// 2.2
void dva_chisla() {
    cout << "Числа, между которыми фатальная ошибка составляет 1.0: " << endl
    << "(1 + 0)*2^23 = " << (2<<23) << " и (1 + 2^-23)*2^23) = "<< ((2<<23)+1) << endl << endl;

    float x = 1.0f;
    while (x != (x+1.0f))
        x++;
    cout << "x0: A x > x0 -> x == x+1: " << static_cast<int>(x) << endl;
}

//ROW
//если бы ряд расходился, цикл был бы бесконечным
void row() {
    cout << endl << "Исследуем ряд:" << endl << endl;
    float sum = 0.0f;
    int n = 1;

    do{
        sum += 1.0f/n;
        ++n;
    } while(sum + (1.0f / n) != sum);
    cout << "Сумма ряда: " << sum << endl;
    cout << "Искомое число (задание - ряд):  " << 1.0f/n << ", c порядковым номером: " << n <<  endl << endl;

    sum = 0.0f;
    for (int i = 1; i <= n + 100; ++i) {
        sum += 1.0f / i;
    }
    cout << "Новая сумма (к+100): " << sum << endl;

    sum = 0.0f;
    for (int i = n + 100; i >= 1; --i) {
        sum += 1.0f / i;
    }
    cout << "Обратная сумма: " << sum << endl;
}


// float

//1.1
void bin_signed(int *n){
    int size = 32;
    cout << "Signed bin: " << endl;
    for(int i = size-1; i >= 0; --i)
        cout << ((*n >> i) & 1);
    cout << endl << endl;
};
// двоичное представление знакового 32-битного целого числа
// Выводит число int со старшего бита до младшего

//1.2
void bin_unsigned(unsigned *n){
    int size = 32;
    cout << "Unsigned bin: " << endl;
    for(int i = size-1; i >= 0; --i)
        cout << ((*n >> i) & 1);
    cout << endl << endl;
};

//1.3
void opaopa(){
    int x = __INT_MAX__;
    cout << "__INT_MAX__ + 1" << endl;
    cout << __INT_MAX__ + 1 << endl;

    int size = 32;
    cout << "Выводим __INT_MAX__ побитово:" << endl;
    for(int i = size-1; i >= 0; --i)
        cout << ((x >> i) & 1);
    cout << endl << "Так как первый бит в int отвечает за знак, при попытке прибавить к числу единицу, мы получаем число 10000...0" << endl
    << "И это число соответствует наименьшему числу из представимых int-" << endl << endl;



    cout << "Проведем похожий тест, но с unsigned int" << endl << endl;
    unsigned x1 = __UINT32_MAX__;
    unsigned zero = 0;
    cout << "Выведем 0-1:" << endl;
    cout << zero - 1 << endl;
    cout << "Теперь __UINT32_MAX__+1" << endl;
    cout << __UINT32_MAX__+1 << endl;
    cout << "__UINT32_MAX__ побитово:" << endl;
    for(int i = size-1; i >= 0; --i)
        cout << ((x1 >> i) & 1);
    cout << endl << "Здесь все просто: __UINT32_MAX__ представляет собой 111...1 => если прибавить к нему еще единицу, число станет равным 1000...0" << endl
    << "А так как эта единица не уместится в памяти, число обнулится" << endl;
};


struct subforwardlist {
    int data;
    subforwardlist* next;

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




