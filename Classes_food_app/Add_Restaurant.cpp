#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

class FoodItem
{
public:
    string name;
    float price;
    float quantity;
    FoodItem(string n, float q, float p) : name(n), quantity(q), price(p) {}
};

class Restaurant
{
public:
    int id;
    int x1, y1, z1;
    float rating;
    float discount;
    vector<FoodItem> menu;
    Restaurant(int x, int y, int z, int p, float r, float d, vector<FoodItem> m)
        : x1(x), y1(y), z1(z), id(p), rating(r), discount(d), menu(m) {}
};

class ShoppingCart
{
public:
    vector<pair<int, FoodItem>> items;

    void addItem(int restaurantId, const FoodItem &item)
    {
        items.push_back(make_pair(restaurantId, item));
    }

    void printCart()
    {
        cout << "Shopping Cart:" << endl;
        for (const auto &item : items)
        {
            cout << "Restaurant ID: " << item.first << ", ";
            cout << "Item: " << item.second.name << ", ";
            cout << "Quantity: " << item.second.quantity << ", ";
            cout << "Price: " << item.second.price << endl;
        }
    }
};

FoodItem createFoodItem(const string &name, float quantity, float price)
{
    return FoodItem(name, quantity, price);
}

void addRestaurant(vector<Restaurant> &restaurants)
{
    int p;
    int x2, y2, z2;
    float rating, discount;

    cout << "Enter restaurant ID: ";
    cin >> p;
    cout << "Enter restaurant Address: ";
    cin >> x2 >> y2 >> z2;
    cout << "Enter restaurant rating: ";
    cin >> rating;
    cout << "Enter restaurant discount: ";
    cin >> discount;

    int n;
    cout << "How many food items does this restaurant have in its menu? ";
    cin >> n;
    vector<FoodItem> initialMenu;
    for (int i = 0; i < n; i++)
    {
        string foodName;
        float foodQuantity, foodPrice;
        cout << "Enter food item #" << (i + 1) << ": Name, Quantity Available, and Price: ";
        cin >> foodName >> foodQuantity >> foodPrice;
        initialMenu.push_back(createFoodItem(foodName, foodQuantity, foodPrice));
    }

    Restaurant newRestaurant(x2, y2, z2, p, rating, discount, initialMenu);
    restaurants.push_back(newRestaurant);
}

pair<int, float> getNearestRestaurant(vector<Restaurant> &restaurants, string name, int qua, int x2, int y2, int z2)
{
    int nearestRestaurantIndex = -1;
    int minDistance = INT_MAX;

    for (int i = 0; i < restaurants.size(); i++)
    {
        Restaurant &restaurant = restaurants[i];
        int distance = abs(x2 - restaurant.x1) + abs(y2 - restaurant.y1) + abs(z2 - restaurant.z1);

        if (distance < minDistance)
        {
            minDistance = distance;
            nearestRestaurantIndex = i;
        }
    }

    if (nearestRestaurantIndex != -1)
    {
        Restaurant &nearestRestaurant = restaurants[nearestRestaurantIndex];

        bool itemFound = false;
        for (int i = 0; i < nearestRestaurant.menu.size(); i++)
        {
            FoodItem &foodItem = nearestRestaurant.menu[i];

            if (foodItem.name == name)
            {
                if (foodItem.quantity >= qua)
                {
                    foodItem.quantity -= qua;
                    int dis=nearestRestaurant.discount;
                    int pri=dis*0.01*foodItem.price;
                    cout << "Item has been successfully added!" << endl;
                    return make_pair(nearestRestaurant.id, pri);
                    itemFound = true;
                }
                else
                {
                    cout << "Not enough quantity available." << endl;
                    itemFound = false;
                }
            }
        }
        if (itemFound == false)
        {
            return make_pair(0, 0);
        }
    }
    cout << "No restaurants found nearby." << endl;
    return make_pair(0, 0);
}

void addToCart(int restaurantId, float foodItemPrice, const string &itemName, int quantity, int x, int y, int z, ShoppingCart &cart, vector<Restaurant> &restaurants)
{
    if (restaurantId != 0)
    {
        for (auto &restaurant : restaurants)
        {
            if (restaurant.id == restaurantId)
            {
                for (auto &item : restaurant.menu)
                {
                    if (item.name == itemName)
                    {
                        if (item.quantity >= quantity)
                        {
                            item.quantity -= quantity; // Subtract quantity from the menu
                            FoodItem newItem(itemName, quantity, foodItemPrice);
                            cart.addItem(restaurantId, newItem);
                            cout << "Item has been successfully added!" << endl;
                        }
                        else
                        {
                            cout << "Not enough quantity available." << endl;
                        }
                        return; // No need to continue searching
                    }
                }
                cout << "Item not found in the menu." << endl;
                return;
            }
        }
        cout << "Restaurant not found." << endl;
    }
}


int main()
{
    bool exit = false;
    vector<Restaurant> restaurants;
    ShoppingCart cart;

    while (!exit)
    {
        int choice;
        cout << "1. Add a new restaurant" << endl;
        cout << "2. View available restaurants" << endl;
        cout << "3. Enter your order" << endl;
        cout << "4. View shopping cart" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addRestaurant(restaurants);
            break;
        case 2:
            if (restaurants.empty())
            {
                cout << "No restaurants added yet." << endl;
            }
            else
            {
                cout << "Available Restaurants:" << endl;
                for (auto &restaurant : restaurants)
                {
                    cout << "ID: " << restaurant.id << ", ";
                    cout << "Address: " << restaurant.x1 << ", " << restaurant.y1 << ", " << restaurant.z1 << ", ";
                    cout << "Rating: " << restaurant.rating << ", ";
                    cout << "Discount: " << restaurant.discount << endl;
                    for (auto &item : restaurant.menu)
                    {
                        cout << "  " << item.name << ": " << item.quantity <<" "<< item.price << endl;
                    }
                    cout << endl;
                }
            }
            break;
        case 3: {
                string name;
                int qty, x1, y1, z1;
                cout << "Enter the item Name: ";
                cin >> name;
                cout << "Enter your address: ";
                cin >> x1 >> y1 >> z1;
                cout << "Enter the quantity: ";
                cin >> qty;
                auto result = getNearestRestaurant(restaurants, name, qty, x1, y1, z1);
                int restaurantId = result.first;
                float foodItemPrice = result.second;
                if (restaurantId != 0) {
                    addToCart(restaurantId, foodItemPrice, name, qty, x1, y1, z1, cart, restaurants);
                }
                break;
            }
            case 4:
                cart.printCart();
                break;
            case 5:
                exit = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;

        }
    }
    return 0;
}
