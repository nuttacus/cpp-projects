#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Abstract base class for all vehicles
class Vehicle
{
protected:
    int vehicleID;
    std::string brand;

public:
    Vehicle(int id, const std::string &b) : vehicleID(id), brand(b) {}
    virtual void displayDetails() const = 0; // Pure virtual function for displaying details
    virtual ~Vehicle() {}                    // Virtual destructor for proper cleanup
};

// Derived class representing a Car
class Car : public Vehicle
{
private:
    int numSeats;

public:
    Car(int id, const std::string &b, int seats) : Vehicle(id, b), numSeats(seats) {}

    void displayDetails() const override
    {
        std::cout << "Car ID: " << vehicleID << ", Brand: " << brand
                  << ", Seats: " << numSeats << std::endl;
    }
};

// Derived class representing a Truck
class Truck : public Vehicle
{
private:
    double maxLoad;

public:
    Truck(int id, const std::string &b, double load) : Vehicle(id, b), maxLoad(load) {}
    void displayDetails() const override
    {
        std::cout << "Truck ID: " << vehicleID << ", Brand: " << brand
                  << ", Max Load: " << maxLoad << " tons" << std::endl;
    }
};

int main()
{
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Car>(1, "Toyota", 5));
    fleet.push_back(std::make_unique<Truck>(2, "Volvo", 10.5));
    fleet.push_back(std::make_unique<Car>(3, "Honda", 4));

    // Display details of each vehicle and identify their type
    for (const auto &v : fleet)
    {
        v->displayDetails();

        // Use dynamic_cast to identify the actual derived type
        if (dynamic_cast<Car *>(v.get()))
        {
            std::cout << "Identified as Car." << std::endl;
        }
        else if (dynamic_cast<Truck *>(v.get()))
        {
            std::cout << "Identified as Truck." << std::endl;
        }
    }

    return 0;
}