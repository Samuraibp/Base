#include <iostream>
using namespace std;

class Base {
public:
    static int peopleCount;
    static int vehiclesCount;
    static int petrolcount;
    static int goodsCount;
};

class Vehicel
{
    const int driver = 1;
    int petrol;
public:
    static int MaxPetrol;
};

class Bas : protected Vehicel
{
    int passengers;
public:
    static int MaxPassengers;
};

class Truck : protected Vehicel
{
    int goods;
public:
    static int MaxGoods;
};


int Base::peopleCount = 0;
int Base::vehiclesCount = 0;
int Base::petrolcount = 0;
int Base::goodsCount = 0;

int Vehicel::MaxPetrol = 100;
int Bas::MaxPassengers = 50;
int Truck::MaxGoods = 1000;
