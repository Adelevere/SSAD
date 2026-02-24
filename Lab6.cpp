#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

using namespace std;

template <typename T>
class GenericStack {
protected:
    vector<T> elements;

public:
    GenericStack(size_t initialCapacity = 10) {
        elements.reserve(initialCapacity);
    }

    virtual ~GenericStack() = default;

    virtual void push(const T& element) {
        elements.push_back(element);
    }

    T pop() {
        if (elements.empty()) {
            throw out_of_range("Stack is empty");
        }
        T topElement = elements.back();
        elements.pop_back();
        return topElement;
    }

    T peek() const {
        if (elements.empty()) {
            throw out_of_range("Stack is empty");
        }
        return elements.back();
    }

    bool isEmpty() const {
        return elements.empty();
    }
};

class StringStack : public GenericStack<string> {
public:
    StringStack(size_t initialCapacity = 10) : GenericStack<string>(initialCapacity) {}

    void push(const string& element) override {
        if (element.empty()) {
            return;
        }
        GenericStack<string>::push(element);
    }

    void concatTopTwo() {
        if (elements.size() < 2) {
            throw logic_error("Not enough elements");
        }
        string s1 = pop();
        string s2 = pop();
        push(s2 + s1);
    }
};

class Box {
public:
    int value;
    Box(int v) : value(v) {
        cout << "Box " << value << " created" << endl;
    }
    ~Box() {
        cout << "Box " << value << " destroyed" << endl;
    }
};

int create_unique(int value) {
    unique_ptr<Box> box = make_unique<Box>(value);
    return box->value;
}

void test_shared_and_weak() {
    shared_ptr<Box> sptr1 = make_shared<Box>(100);
    shared_ptr<Box> sptr2 = sptr1;
    
    cout << "Ref count: " << sptr1.use_count() << endl;

    weak_ptr<Box> wptr = sptr1;
    if (auto locked = wptr.lock()) {
        cout << "Weak access value: " << locked->value << endl;
    }
}

int main() {
    try {
        StringStack ss;
        ss.push("World");
        ss.push("Hello ");
        ss.concatTopTwo();
        cout << "Stack top: " << ss.peek() << endl;

        create_unique(10);
        test_shared_and_weak();
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}