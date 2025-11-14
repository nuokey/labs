struct subforwardlist {
       int data;
       subforwardlist* next;
};


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