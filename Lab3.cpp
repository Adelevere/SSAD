#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Animal {
    protected:
        string name;
        int age;
    public: 
        Animal(string n, int a) : name(n), age(a) {}
        virtual ~Animal() {}

        virtual void makeSound() const = 0;
};

class LandAnimal : virtual public Animal {
    public: 
        LandAnimal(string n, int a) : Animal(n, a) {}

        virtual void walk() const {
            cout << name << " is walking on land." << endl;
        }

        void makeSound() const override {
            cout << "Generic land animal sound." << endl;
        }
};

class WaterAnimal : virtual public Animal {
    public:
        WaterAnimal(string n, int a) : Animal(n, a) {}
        
        virtual void swim() const {
            cout << name << " is swimming in water." << endl;
        }

        void makeSound() const override {
            cout << "Generic water animal sound." << endl;
        }
};

class Lion : public LandAnimal {
    public:
        Lion(string n, int a) : Animal(n, a), LandAnimal(n, a) {}

        void makeSound() const override {
        cout << "Lion " << name << " says: ROAR!" << endl;
        }

        void walk() const override {
            cout << "Lion " << name << " stalks through the grass." << endl;
        }
};

class Dolphin : public WaterAnimal {
    public:
        Dolphin(string n, int a) : Animal(n, a), WaterAnimal(n, a) {}

        void makeSound() const override {
            cout << "Dolphin " << name << " says: Click-click!" << endl;
        }

        void swim() const override {
            cout << "Dolphin " << name << " leaps through the waves." << endl;
        }
};

class Frog : public LandAnimal, public WaterAnimal {
    public:
            Frog(string n, int a) : Animal(n, a), LandAnimal(n, a), WaterAnimal(n, a) {}

            void makeSound() const override {
                cout << "Frog " << name << " says: Ribbit!" << endl;
            }
};

int main() {
    vector<Animal*> zoo;

    zoo.push_back(new Lion("Leo", 5));
    zoo.push_back(new Dolphin("Flipper", 3));
    zoo.push_back(new Frog("Kermit", 2));

    for (Animal* animal : zoo) {
        animal->makeSound();

        LandAnimal* land = dynamic_cast<LandAnimal*>(animal);
        if (land) land->walk();

        WaterAnimal* water = dynamic_cast<WaterAnimal*>(animal);
        if (water) water->swim();
        
        cout << "" << endl;
    }

    for (Animal* animal : zoo) {
        delete animal;
    }
    zoo.clear();

    return 0;
}