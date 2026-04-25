#include "Crafting.h"

UCraftingSystem::UCraftingSystem()
{
}

bool UCraftingSystem::CanCraft(FName RecipeID, const TMap<FName, int32>& Inventory)
{
    return false;
}

TMap<FName, int32> UCraftingSystem::Craft(FName RecipeID, const TMap<FName, int32>& Inventory)
{
    return TMap<FName, int32>();
}

TArray<FCraftingRecipe> UCraftingSystem::GetRecipesByStation(ECraftingStation Station)
{
    return TArray<FCraftingRecipe>();
}

TArray<FCraftingRecipe> UCraftingSystem::GetRecipesByCategory(ECraftingCategory Category)
{
    return TArray<FCraftingRecipe>();
}

TArray<FCraftingRecipe> UCraftingSystem::GetAllRecipes()
{
    return TArray<FCraftingRecipe>();
}

FCraftingRecipe UCraftingSystem::GetRecipe(FName RecipeID)
{
    return FCraftingRecipe();
}

int32 UCraftingSystem::GetCraftingTime(FName RecipeID)
{
    return 1;
}

bool UCraftingSystem::HasRequiredProfession(FName RecipeID, const TArray<FName>& Professions)
{
    return false;
}