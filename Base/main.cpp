#include <iostream>
using namespace std;

class Base {
public:
    static int peopleCount;
    static int vehiclesCount;
    static double petrolCount;
    static int goodsCount;
};

class Vehicle
{
    const int driver = 1;
    double petrol;
    double TankVolume;

public:
    Vehicle(): TankVolume(0.0), petrol(0.0) {}
    Vehicle(double  t, double  p )
    {
        TankVolume = t;
        if (p <= TankVolume) petrol = p;
        else {
            petrol = TankVolume;
            cout << "Over limit of petrol\n";
        }
    }
    double GetTankVolume() const
    {
        return TankVolume;
    }
    void SetPet(double p)
    {
        petrol = (p <= TankVolume) ? p : TankVolume;
    }


    double GetPetrol() const
    {
        return petrol;
    }
    int GetDriver() const
    {
        return driver;
    }
    virtual void arrive() {}
    virtual bool leave() { return false; }
    virtual ~Vehicle() {}

};

class Bus : public Vehicle
{
    int passengers;
    int MaxPassengers;
public:
    Bus() : Vehicle(), MaxPassengers(0), passengers(0) {}
    Bus(double t, double pet, int MaxP, int pass) : Vehicle(t, pet) {
        MaxPassengers = MaxP;
        if (pass <= MaxPassengers) passengers = pass;
        else {
            passengers = MaxPassengers;
            cout << "Over limit of passengers" << endl;
        }
    }
    void SetPassengers(int p)
    {
        passengers = (p <= MaxPassengers) ? p : MaxPassengers;
    }

    int GetPassengers() const
    {
        return passengers;
    }
    int GetMaxPassengers() const { return MaxPassengers; }
    void arrive () override {
        Base::vehiclesCount++;
        Base::peopleCount += GetPassengers() + GetDriver();
        Base::petrolCount += GetPetrol();

        cout << "Bus arrived\n";
    }
    bool leave() override
    {
        int availablePeople = Base::peopleCount - GetDriver();
        if (availablePeople < 0) return false;

        int canTake = min(GetMaxPassengers(), availablePeople);

        double need = GetTankVolume() - GetPetrol();
        if (Base::petrolCount < need) return false;

        SetPassengers(canTake);
        Base::peopleCount -= GetPassengers() + GetDriver();

        Base::petrolCount -= need;
        SetPet(GetTankVolume());

        Base::vehiclesCount--;

        cout << "Bus left\n";
        return true;
    }

    ~Bus() override {}
};

class Truck : public Vehicle
{
    int goods;
    int MaxGoods;
public:
    Truck(): Vehicle(), MaxGoods(0), goods(0) {}
    Truck(double t, double pet, int MaxG, int g) : Vehicle(t, pet)
    {
        MaxGoods = MaxG;
        if (g <= MaxGoods) goods = g;
        else
        {
            goods = MaxGoods;
            cout << "Over limit of goods" << endl;
        }
    }

    int GetGoods() const
    {
        return goods;
    }
    void SetGoods(int g)
    {
        goods = (g <= MaxGoods) ? g : MaxGoods;
    }
    int GetMaxGoods() const { return MaxGoods; }
    void arrive() override {
        Base::vehiclesCount++;
        Base::peopleCount += GetDriver();
        Base::petrolCount += GetPetrol();
        Base::goodsCount += GetGoods();

        cout << "Truck arrived\n";
    }
    bool leave() override
    {
        if (Base::goodsCount <= 0) return false;

        int canTake = min(GetMaxGoods(), Base::goodsCount);

        double need = GetTankVolume() - GetPetrol();
        if (Base::petrolCount < need) return false;

        SetGoods(canTake);

        Base::petrolCount -= need;
        SetPet(GetTankVolume());

        Base::vehiclesCount--;

        Base::peopleCount -= GetDriver();
        Base::goodsCount -= GetGoods();

        cout << "Truck left\n";
        return true;
    }

    ~Truck() override {}
};


int Base::peopleCount = 0;
int Base::vehiclesCount = 0;
double Base::petrolCount = 0;
int Base::goodsCount = 0;

int main()
{
    cout << "=== Initial state ===\n";
    cout << "People: " << Base::peopleCount << endl;
    cout << "Vehicles: " << Base::vehiclesCount << endl;
    cout << "Petrol: " << Base::petrolCount << endl;
    cout << "Goods: " << Base::goodsCount << endl;

    cout << "\n=== Bus arrives ===\n";
    Bus bus(100, 30, 40, 20);   
    bus.arrive();

    cout << "People: " << Base::peopleCount << endl;
    cout << "Vehicles: " << Base::vehiclesCount << endl;
    cout << "Petrol: " << Base::petrolCount << endl;

    cout << "\n=== Truck arrives ===\n";
    Truck truck(150, 50, 200, 120); 
    truck.arrive();

    cout << "People: " << Base::peopleCount << endl;
    cout << "Vehicles: " << Base::vehiclesCount << endl;
    cout << "Petrol: " << Base::petrolCount << endl;
    cout << "Goods: " << Base::goodsCount << endl;

    cout << "\n=== Bus leaves ===\n";
    if (!bus.leave())
        cout << "Bus could not leave\n";

    cout << "People: " << Base::peopleCount << endl;
    cout << "Vehicles: " << Base::vehiclesCount << endl;
    cout << "Petrol: " << Base::petrolCount << endl;

    cout << "\n=== Truck leaves ===\n";
    if (!truck.leave())
        cout << "Truck could not leave\n";

    cout << "People: " << Base::peopleCount << endl;
    cout << "Vehicles: " << Base::vehiclesCount << endl;
    cout << "Petrol: " << Base::petrolCount << endl;
    cout << "Goods: " << Base::goodsCount << endl;

}