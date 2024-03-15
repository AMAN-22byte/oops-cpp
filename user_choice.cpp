#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Menu {
private:
    map<string, double> foodPrices;

public:
    Menu() {}

    void addFood(const string& food, double price) {
        foodPrices[food] = price;
    }

    double getPrice(const string& food) const {
        auto it = foodPrices.find(food);
        if (it != foodPrices.end()) {
            return it->second;
        }
        return -1; // Indicates food not found
    }
};

class Restaurant {
private:
    string name;
    Menu menu;

public:
    Restaurant(const string& name) : name(name) {}

    void addFood(const string& food, double price) {
        menu.addFood(food, price);
    }

    double getPrice(const string& food) const {
        return menu.getPrice(food);
    }

    const string& getName() const {
        return name;
    }
};

int main() {
    string desiredFood;
    cout << "What do you like to have??" << endl;
    cin >> desiredFood;

    int numRestaurants;
    cout << "Enter the number of restaurants: ";
    cin >> numRestaurants;

    vector<Restaurant> restaurants;
    for (int i = 0; i < numRestaurants; i++) {
        string resName;
        cout << "Enter restaurant name: ";
        cin >> resName;

        int numFoods;
        cout << "Enter the number of foods for " << resName << ": ";
        cin >> numFoods;

        Restaurant restaurant(resName);
        for (int j = 0; j < numFoods; j++) {
            string food;
            double price;
            cout << "Enter food name and price for " << resName << " (e.g., Egg 5.99): ";
            cin >> food >> price;
            restaurant.addFood(food, price);
        }
        restaurants.push_back(restaurant);
    }

    cout << "Restaurants serving " << desiredFood << " along with their prices:" << endl;
    for (const auto& restaurant : restaurants) {
        double price = restaurant.getPrice(desiredFood);
        if (price != -1) {
            cout << restaurant.getName() << ": " << desiredFood << " - $" << price << endl;
        }
    }

    // Selecting a restaurant
    int choice;
    cout << "Enter the number corresponding to the restaurant you want to order from: ";
    cin >> choice;
    if (choice < 1 || choice > restaurants.size()) {
        cout << "Invalid choice!" << endl;
        return 1;
    }

    Restaurant selectedRestaurant = restaurants[choice - 1];

    // Increasing the quantity of the selected food item
    int quantity;
    cout << "Enter the quantity you want to order: ";
    cin >> quantity;

    // Confirming the order
    double totalPrice = selectedRestaurant.getPrice(desiredFood) * quantity;
    if (totalPrice != -1) {
        cout << "Your order details:" << endl;
        cout << "Restaurant: " << selectedRestaurant.getName() << endl;
        cout << "Food: " << desiredFood << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Total Price: $" << totalPrice << endl;
    } else {
        cout << "Invalid food selection!" << endl;
    }

    return 0;
}
