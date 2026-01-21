#include <iostream>
using namespace std;

class Base {
public:
    static int peopleCount;
    static int vehiclesCount;
    static int petrolcount;
    static int goodsCount;
    void PlusPetrol(int p)
    {
        petrolcount += p;
    }
};

class Vehicel
{
    int driver = 1;
    int petrol;
public:
    Vehicel(): driver(0), petrol(0) {}
    Vehicel(int p)
    {
        petrol = p;
    }
    void SetPet(int p)
    {
        petrol = p;
    }
    int GetPetr()
    {
        return petrol;
    }
    int GetDriver()
    {
        return driver;
    }
    static int MaxPetrol;
    virtual void arrive() {}
    virtual void leave() {}

};

class Bas : protected Vehicel
{
    int passengers;
public:
    static int MaxPassengers;
    void arrive () override {
        Base::vehiclesCount++;
        Base::peopleCount += passengers + GetDriver();
        Base::petrolcount += GetPetr();

        cout << "Bus arrived\n";
    }
    void leave() override {
        Base::vehiclesCount--;
        Base::peopleCount -= passengers + GetDriver();
        Base::petrolcount -= GetPetr();

        cout << "Bus left\n";
    }
};

class Truck : protected Vehicel
{
    int goods;
public:
    static int MaxGoods;
    void arrive() override {
        Base::vehiclesCount++;
        Base::peopleCount += GetDriver();
        Base::petrolcount += GetPetr();
        Base::goodsCount += goods;

        cout << "Truck arrived\n";
    }
    void leave() override {
        Base::vehiclesCount--;
        Base::peopleCount -= GetDriver();
        Base::petrolcount -= GetPetr();
        Base::goodsCount -= goods;

        cout << "Truck left\n";
    }
};


int Base::peopleCount = 0;
int Base::vehiclesCount = 0;
int Base::petrolcount = 0;
int Base::goodsCount = 0;

int Vehicel::MaxPetrol = 100;
int Bas::MaxPassengers = 50;
int Truck::MaxGoods = 100;
