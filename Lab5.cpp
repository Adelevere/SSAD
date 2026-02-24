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

    size_t size() const {
        return elements.size();
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
            throw logic_error("Not enough elements to concatenate");
        }
        string str1 = pop();
        string str2 = pop();
        push(str2 + str1);
    }
};

class Box {
public:
    int value;
    weak_ptr<Box> otherBox;

    Box(int v) : value(v) {
        cout << "Box " << value << " constructed" << endl;
    }

    ~Box() {
        cout << "Box " << value << " destructed" << endl;
    }
};

int create_unique(int value) {
    unique_ptr<Box> box = make_unique<Box>(value);
    return box->value;
}

void testGenericStack() {
    cout << "--- Task 1: StringStack ---" << endl;
    StringStack stack;
    
    stack.push("World");
    stack.push("Hello ");
    stack.push(""); 

    cout << "Peek top: " << stack.peek() << endl;

    stack.concatTopTwo();
    cout << "After concat: " << stack.peek() << endl;

    stack.pop(); 
    
    try {
        stack.pop(); 
    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    cout << endl;
}

void testUniquePtr() {
    cout << "--- Task 2: unique_ptr ---" << endl;
    int val = create_unique(50);
    cout << "Value returned: " << val << endl;

    unique_ptr<Box> box1 = make_unique<Box>(10);
    unique_ptr<Box> box2 = move(box1);

    if (!box1) cout << "box1 is empty" << endl;
    if (box2) cout << "box2 owns Box " << box2->value << endl;
    cout << endl;
}

void testSharedPtr() {
    cout << "--- Task 2: shared_ptr ---" << endl;
    shared_ptr<Box> ptr1 = make_shared<Box>(100);
    
    cout << "Ref count: " << ptr1.use_count() << endl;
    {
        shared_ptr<Box> ptr2 = ptr1;
        cout << "Ref count inside scope: " << ptr1.use_count() << endl;
    }
    cout << "Ref count outside scope: " << ptr1.use_count() << endl;
    cout << endl;
}

void testWeakPtr() {
    cout << "--- Task 2: weak_ptr & Circular Reference ---" << endl;
    shared_ptr<Box> boxA = make_shared<Box>(1);
    shared_ptr<Box> boxB = make_shared<Box>(2);

    boxA->otherBox = boxB;
    boxB->otherBox = boxA;

    if (auto locked = boxA->otherBox.lock()) {
        cout << "Box " << boxA->value << " is linked to Box " << locked->value << endl;
    }

    boxA.reset();
    boxB.reset();
    cout << endl;
}

int main() {
    testGenericStack();
    testUniquePtr();
    testSharedPtr();
    testWeakPtr();
    return 0;
}