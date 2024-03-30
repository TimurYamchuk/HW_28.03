#include <iostream>
#include <vector>

using namespace std;

class Herbivore {
protected:
    int weight;
public:
    Herbivore(int w) : weight(w) {}

    void Eat() {
        cout << "Eating..." << endl;
        weight += 10;
        cout << "Weight: " << weight << endl;
    }

    int GetWeight() const {
        return weight;
    }

    virtual ~Herbivore() {}
};

class Carnivore {
protected:
    int power;
public:
    Carnivore(int p) : power(p) {}

    virtual void Eat(Herbivore* herbivore) = 0;

    int GetPower() const {
        return power;
    }

    virtual ~Carnivore() {}
};

class Wildebeest : public Herbivore {
public:
    Wildebeest(int w) : Herbivore(w) {}

    void Eat() {
        Herbivore::Eat();
        cout << "Wildebeest is eating grass." << endl;
    }
};

class Bison : public Herbivore {
public:
    Bison(int w) : Herbivore(w) {}

    void Eat() {
        Herbivore::Eat();
        cout << "Bison is eating grass." << endl;
    }
};

class Elk : public Herbivore {
public:
    Elk(int w) : Herbivore(w) {}

    void Eat() {
        Herbivore::Eat();
        cout << "Elk is eating grass." << endl;
    }
};

class Lion : public Carnivore {
public:
    Lion(int p) : Carnivore(p) {}

    void Eat(Herbivore* herbivore) override {
        if (herbivore->GetWeight() < power) {
            power -= 10;
            cout << "Lion won:" << endl;
        }
        else {
            power += 10;
            delete herbivore;
            cout << "Lion lost:" << endl;
        }
        cout << "Lion power:" << power << endl;
    }
};

class Wolf : public Carnivore {
public:
    Wolf(int p) : Carnivore(p) {}

    void Eat(Herbivore* herbivore) override {
        if (herbivore->GetWeight() < power) {
            power -= 10;
            cout << "Wolf won:" << endl;
        }
        else {
            power += 10;
            delete herbivore;
            cout << "Wolf lost:" << endl;
        }
        cout << "Wolf power:" << power << endl;
    }
};

class Tiger : public Carnivore {
public:
    Tiger(int p) : Carnivore(p) {}

    void Eat(Herbivore* herbivore) override {
        if (herbivore->GetWeight() < power) {
            power -= 10;
            cout << "Tiger won:" << endl;
        }
        else {
            power += 10;
            delete herbivore;
            cout << "Tiger lost:" << endl;

        }
        cout << "Tiger power:" << power << endl;
    }
};

class Continent {
public:
    virtual Herbivore* CreateHerbivore() = 0;
    virtual Carnivore* CreateCarnivore() = 0;
    virtual ~Continent() {}
};

class Africa : public Continent {
public:
    Herbivore* CreateHerbivore() override {
        return new Wildebeest(10);
    }

    Carnivore* CreateCarnivore() override {
        return new Lion(40);
    }
};

class NorthAmerica : public Continent {
public:
    Herbivore* CreateHerbivore() override {
        return new Bison(20);
    }

    Carnivore* CreateCarnivore() override {
        return new Wolf(90);
    }
};

class Eurasia : public Continent {
public:
    Herbivore* CreateHerbivore() override {
        return new Elk(150);
    }

    Carnivore* CreateCarnivore() override {
        return new Tiger(40);
    }
};

class AnimalWorld {
private:
    vector<Herbivore*> herbivores;
    vector<Carnivore*> carnivores;

public:
    void AddHerbivore(Herbivore* herbivore) {
        herbivores.push_back(herbivore);
    }

    void AddCarnivore(Carnivore* carnivore) {
        carnivores.push_back(carnivore);
    }

    void MealsHerbivores() {
        cout << "\nHerbivores are eating..." << endl;
        for (Herbivore* herbivore : herbivores) {
            herbivore->Eat();
        }
    }

    void NutritionCarnivores() {
        cout << "\nCarnivores are hunting..." << endl;
        for (Carnivore* carnivore : carnivores) {
            if (!herbivores.empty()) {
                Herbivore* prey = herbivores.back();
                herbivores.pop_back();
                carnivore->Eat(prey);
            }
        }
    }

    ~AnimalWorld() {
        for (Herbivore* herbivore : herbivores) {
            delete herbivore;
        }
        for (Carnivore* carnivore : carnivores) {
            delete carnivore;
        }
    }
};

int main() {
    Continent* africa = new Africa();
    Continent* northAmerica = new NorthAmerica();
    Continent* eurasia = new Eurasia();

    AnimalWorld animalWorld;

    animalWorld.AddHerbivore(africa->CreateHerbivore());
    animalWorld.AddCarnivore(africa->CreateCarnivore());

    animalWorld.AddHerbivore(northAmerica->CreateHerbivore());
    animalWorld.AddCarnivore(northAmerica->CreateCarnivore());

    animalWorld.AddHerbivore(eurasia->CreateHerbivore());
    animalWorld.AddCarnivore(eurasia->CreateCarnivore());

    animalWorld.MealsHerbivores();
    animalWorld.NutritionCarnivores();

    delete africa;
    delete northAmerica;
    delete eurasia;

    return 0;
}
