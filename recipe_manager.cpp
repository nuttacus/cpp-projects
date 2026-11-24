#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>

class Recipe
{
    std::string recipename;
    std::vector<std::string> ingredients;
    std::string instructions;

public:
    Recipe() {}
    Recipe(std::string name, const std::vector<std::string> &ingredients, std::string instructions)
        : recipename(name), ingredients(ingredients), instructions(instructions) {}

    std::string getName() const
    {
        return recipename;
    }

    void inputRecipe()
    {
        ingredients.clear();
        std::cout << "Enter recipe name: ";
        std::getline(std::cin >> std::ws, recipename);

        std::cout << "Enter ingredients (separated by commas): ";
        std::string ingredientLine;
        std::getline(std::cin, ingredientLine);
        const auto trim = [](const std::string &ingredient)
        {
            const size_t first = ingredient.find_first_not_of(" \t\n\r\f\v");
            if (first == std::string::npos)
            {
                return std::string();
            }
            const size_t last = ingredient.find_last_not_of(" \t\n\r\f\v");
            return ingredient.substr(first, last - first + 1);
        };
        size_t pos = 0;
        while ((pos = ingredientLine.find(',')) != std::string::npos)
        {
            ingredients.push_back(trim(ingredientLine.substr(0, pos)));
            ingredientLine.erase(0, pos + 1);
        }
        if (!ingredientLine.empty())
        {
            ingredients.push_back(trim(ingredientLine));
        }

        std::cout << "Enter instructions: ";
        std::getline(std::cin, instructions);
    }

    void displayRecipe() const
    {
        std::cout << "Recipe Name: " << recipename << std::endl;
        std::cout << "Ingredients: ";
        for (size_t i = 0; i < ingredients.size(); ++i)
        {
            std::cout << ingredients[i];
            if (i != ingredients.size() - 1)
                std::cout << ", ";
        }
        std::cout << "\nInstructions: " << instructions << std::endl;
    }
};

namespace RecipeUtils
{
    void convertToUpper(std::string &str)
    {
        for (char &c : str)
        {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
    }
}

// Exception-based search function
const Recipe &searchRecipeByName(const std::vector<Recipe> &recipes, const std::string &name)
{
    for (const auto &recipe : recipes)
    {
        if (recipe.getName() == name)
        {
            return recipe;
        }
    }
    throw std::runtime_error("Recipe not found.");
}

int main()
{
    std::cout << "Welcome to our recipe management system!" << std::endl;
    std::vector<Recipe> recipes;

    // Input details for 3 recipes
    for (int i = 0; i < 3; ++i)
    {
        Recipe r;
        std::cout << "\nEntering details for recipe " << (i + 1) << ":\n";
        r.inputRecipe();
        recipes.push_back(r);
    }

    int choice = 0;
    do
    {
        std::cout << "\n-- Recipe Management Menu --" << std::endl;
        std::cout << "1. Display all recipes" << std::endl;
        std::cout << "2. Search for a recipe by name" << std::endl;
        std::cout << "3. Preview uppercase name" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice))
        {
            if (std::cin.eof())
            {
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (choice == 1)
        {
            for (const auto &recipe : recipes)
            {
                recipe.displayRecipe();
            }
        }
        else if (choice == 2)
        {
            std::string searchName;
            std::cout << "Enter the name of the recipe to search: ";
            std::getline(std::cin, searchName);
            try
            {
                const Recipe &found = searchRecipeByName(recipes, searchName);
                found.displayRecipe();
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        else if (choice == 3)
        {
            std::string nameToConvert;
            std::cout << "Enter the name of the recipe to preview in uppercase: ";
            std::getline(std::cin, nameToConvert);
            bool foundRecipe = false;
            for (const auto &recipe : recipes)
            {
                if (recipe.getName() == nameToConvert)
                {
                    std::string upperName = recipe.getName();
                    RecipeUtils::convertToUpper(upperName);
                    std::cout << "Uppercase name preview: " << upperName << std::endl;
                    foundRecipe = true;
                    break;
                }
            }
            if (!foundRecipe)
            {
                std::cout << "Recipe not found." << std::endl;
            }
        }
        else if (choice == 4)
        {
            std::cout << "Exiting the program." << std::endl;
        }
        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
