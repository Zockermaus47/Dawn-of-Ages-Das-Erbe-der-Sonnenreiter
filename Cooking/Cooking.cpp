#include "Cooking.h"

UCookingBrewingSystem::UCookingBrewingSystem()
{
}

bool UCookingBrewingSystem::CanCook(FCookingRecipe Recipe, const TMap<FName, int32>& Inventory)
{
    return false;
}

TMap<FName, int32> UCookingBrewingSystem::Cook(FCookingRecipe Recipe, const TMap<FName, int32>& Inventory)
{
    return TMap<FName, int32>();
}

bool UCookingBrewingSystem::CanBrew(FBrewingRecipe Recipe, const TMap<FName, int32>& Inventory)
{
    return false;
}

TMap<FName, int32> UCookingBrewingSystem::Brew(FBrewingRecipe Recipe, const TMap<FName, int32>& Inventory)
{
    return TMap<FName, int32>();
}

TArray<FCookingRecipe> UCookingBrewingSystem::GetAllCookingRecipes()
{
    return TArray<FCookingRecipe>();
}

TArray<FBrewingRecipe> UCookingBrewingSystem::GetAllBrewingRecipes()
{
    return TArray<FBrewingRecipe>();
}