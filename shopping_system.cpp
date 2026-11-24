#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

// Enum for item categories
enum class Category
{
    ELECTRONICS,
    GROCERY,
    CLOTHING
};

// Converts Category enum to a readable string
std::string categoryToString(Category cat)
{
    switch (cat)
    {
    case Category::ELECTRONICS:
        return "ELECTRONICS";
    case Category::GROCERY:
        return "GROCERY";
    case Category::CLOTHING:
        return "CLOTHING";
    default:
        return "UNKNOWN";
    }
}

// Class representing an item in the order
class Item
{
private:
    std::string name;
    Category category;
    float price;
    int quantity;

public:
    // Constructor with validation
    Item(std::string n, Category c, float p, int q) : name(n), category(c), price(p), quantity(q)
    {
        if (price <= 0)
        {
            throw std::invalid_argument("Invalid price: must be greater than 0.");
        }
        if (quantity < 1)
        {
            throw std::invalid_argument("Invalid quantity: must be at least 1.");
        }
    }

    // Calculates total price for the item
    float totalPrice() const
    {
        return price * quantity;
    }

    // Overload << to print item details
    friend std::ostream &operator<<(std::ostream &os, const Item &item)
    {
        os << "Name: " << item.name
           << ", Category: " << categoryToString(item.category)
           << ", Price: " << item.price
           << ", Quantity: " << item.quantity
           << ", Total Price: " << item.totalPrice();
        return os;
    }
};

void discardInputLine()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to add an item to the order with input validation
bool addItem(std::vector<Item> &order)
{
    std::string name;
    int categoryChoice;
    float price;
    int quantity;

    std::cout << "Enter item name: ";
    if (!std::getline(std::cin >> std::ws, name))
    {
        std::cerr << "Error adding item: failed to read item name." << std::endl;
        return false;
    }

    std::cout << "Select category (0: ELECTRONICS, 1: GROCERY, 2: CLOTHING): ";
    if (!(std::cin >> categoryChoice))
    {
        std::cerr << "Error adding item: invalid category input." << std::endl;
        if (!std::cin.eof())
            discardInputLine();
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (categoryChoice < 0 || categoryChoice > 2)
    {
        std::cerr << "Error adding item: category must be between 0 and 2." << std::endl;
        return false;
    }
    Category category = static_cast<Category>(categoryChoice);

    std::cout << "Enter price: ";
    if (!(std::cin >> price))
    {
        std::cerr << "Error adding item: invalid price input." << std::endl;
        if (!std::cin.eof())
            discardInputLine();
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter quantity: ";
    if (!(std::cin >> quantity))
    {
        std::cerr << "Error adding item: invalid quantity input." << std::endl;
        if (!std::cin.eof())
            discardInputLine();
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Try to create a valid item, handle invalid input
    try
    {
        Item newItem(name, category, price, quantity);
        order.push_back(newItem);
        return true;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error adding item: " << e.what() << std::endl;
        return false;
    }
}

int main()
{
    std::cout << "Welcome to the Online Shopping System!" << std::endl;
    std::vector<Item> order;
    int choice = 0;

    // Main menu loop
    do
    {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Item to Order\n";
        std::cout << "2. Display All Items in Order\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice))
        {
            if (std::cin.eof())
                break;
            discardInputLine();
            std::cout << "Invalid choice. Please try again." << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            // Add a new item to the order
            if (addItem(order))
                std::cout << "Item added to order." << std::endl;
            break;
        }
        case 2:
        {
            // Display all items in the order
            std::cout << "\nItems in Order:\n";
            float orderTotal = 0.0f;
            for (const auto &item : order)
            {
                std::cout << item << std::endl;
                orderTotal += item.totalPrice();
            }
            std::cout << "Order Total: " << orderTotal << std::endl;
            break;
        }
        case 3:
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 3);

    return 0;
}
