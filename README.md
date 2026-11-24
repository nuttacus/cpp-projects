# C++ Practice Projects

Three small console programs that show core C++ object-oriented ideas.

## Build

Each file compiles on its own with g++ (C++17):

```
g++ -std=c++17 -Wall -Wextra recipe_manager.cpp -o recipe_manager
g++ -std=c++17 -Wall -Wextra shopping_system.cpp -o shopping_system
g++ -std=c++17 -Wall -Wextra vehicle_fleet.cpp -o vehicle_fleet
```

## Programs

### Recipe Manager (`recipe_manager.cpp`)
Enter three recipes (name, comma-separated ingredients, instructions), then use a menu to display all recipes, search by name, preview a recipe name in uppercase, or exit.
**Shows:** classes with a constructor, `std::vector`, a utility namespace, and exception-based search with `try` and `catch`.

### Online Shopping System (`shopping_system.cpp`)
Add items to an order with a name, category, price and quantity, then list the order with a total for each item.
**Shows:** an `enum class` for categories, validation in the constructor (price above 0, quantity at least 1), and an overloaded `<<` operator for printing.

### Vehicle Fleet (`vehicle_fleet.cpp`)
Creates a fleet of cars and trucks through an abstract `Vehicle` base class and prints the details of each.
**Shows:** inheritance, pure virtual functions, a virtual destructor, runtime polymorphism, and `dynamic_cast` to identify the real type of each object.
The virtual destructor ensures each derived vehicle is properly destroyed when owned through a `Vehicle` pointer.

## What I learned

Designing classes with clear responsibilities, why base classes need virtual destructors, and validating input so a bad entry cannot crash the program.

## Next steps

- Save recipes and orders to a file.

Built by Chloe.
