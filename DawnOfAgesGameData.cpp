#include "DawnOfAgesGameData.h"

FItemEntry UDawnOfAgesGameData::GetItem(FName ItemID) const
{
    if (AllItems.Contains(ItemID))
    {
        return AllItems[ItemID];
    }
    return FItemEntry();
}

FCraftingRecipeEntry UDawnOfAgesGameData::GetRecipe(FName RecipeID) const
{
    if (CraftingRecipes.Contains(RecipeID))
    {
        return CraftingRecipes[RecipeID];
    }
    return FCraftingRecipeEntry();
}

TArray<FName> UDawnOfAgesGameData::GetItemsByEpoch(FString Epoch) const
{
    TArray<FName> Result;
    for (const auto& Pair : AllItems)
    {
        if (Pair.Value.Epoch == Epoch)
        {
            Result.Add(Pair.Key);
        }
    }
    return Result;
}

TArray<FName> UDawnOfAgesGameData::GetRecipesByEpoch(FString Epoch) const
{
    TArray<FName> Result;
    for (const auto& Pair : CraftingRecipes)
    {
        if (Pair.Value.Epoch == Epoch)
        {
            Result.Add(Pair.Key);
        }
    }
    return Result;
}

bool UDawnOfAgesGameData::CanCraftInCurrentEpoch(FName RecipeID, FString CurrentEpoch) const
{
    if (!CraftingRecipes.Contains(RecipeID))
    {
        return false;
    }

    FCraftingRecipeEntry Recipe = CraftingRecipes[RecipeID];
    
    if (Recipe.Epoch == "Alle")
    {
        return true;
    }
    
    if (Recipe.Epoch == "Steinzeit" && CurrentEpoch == "Steinzeit")
    {
        return true;
    }
    
    if (Recipe.Epoch == "Bronzezeit" && (CurrentEpoch == "Bronzezeit" || CurrentEpoch == "Steinzeit"))
    {
        return true;
    }
    
    if (Recipe.Epoch == "Mittelalter")
    {
        return true;
    }
    
    return false;
}

void UDawnOfAgesGameData::InitializeDefaultData()
{
    StoneAgeItems.Empty();
    BronzeAgeItems.Empty();
    MedievalItems.Empty();

    StoneAgeItems.Add(FName("Club_Wood"));
    StoneAgeItems.Add(FName("Club_Stone"));
    StoneAgeItems.Add(FName("Spear_Stone"));
    StoneAgeItems.Add(FName("Knife_Stone"));
    StoneAgeItems.Add(FName("Hammer_Stone"));
    StoneAgeItems.Add(FName("Sling_Stone"));
    StoneAgeItems.Add(FName("Axe_Stone"));
    StoneAgeItems.Add(FName("Pickaxe_Stone"));
    StoneAgeItems.Add(FName("Flint"));
    StoneAgeItems.Add(FName("Stick"));
    StoneAgeItems.Add(FName("Rope_Plant"));
    StoneAgeItems.Add(FName("Cape_Fur"));
    StoneAgeItems.Add(FName("Pelt_Raw"));
    StoneAgeItems.Add(FName("Necklace_Bone"));
    StoneAgeItems.Add(FName("Skirt_Leaf"));
    StoneAgeItems.Add(FName("Meat_Raw"));
    StoneAgeItems.Add(FName("Fish_Raw"));
    StoneAgeItems.Add(FName("Egg"));
    StoneAgeItems.Add(FName("Berry_Wild"));
    StoneAgeItems.Add(FName("Mushroom_Wild"));
    StoneAgeItems.Add(FName("Honey"));
    StoneAgeItems.Add(FName("Milk"));
    StoneAgeItems.Add(FName("Water_Dirty"));
    StoneAgeItems.Add(FName("Wood_Branch"));
    StoneAgeItems.Add(FName("Wood_Log"));
    StoneAgeItems.Add(FName("Stone_Rock"));
    StoneAgeItems.Add(FName("Clay"));
    StoneAgeItems.Add(FName("Bone_Raw"));
    StoneAgeItems.Add(FName("Hide_Raw"));
    StoneAgeItems.Add(FName("Fiber_Plant"));

    BronzeAgeItems.Add(FName("Sword_Copper"));
    BronzeAgeItems.Add(FName("Spear_Copper"));
    BronzeAgeItems.Add(FName("Arrow_Copper"));
    BronzeAgeItems.Add(FName("Shield_Copper"));
    BronzeAgeItems.Add(FName("Dagger_Copper"));
    BronzeAgeItems.Add(FName("Mace_Copper"));
    BronzeAgeItems.Add(FName("Axe_Copper"));
    BronzeAgeItems.Add(FName("Pickaxe_Copper"));
    BronzeAgeItems.Add(FName("Sickle_Copper"));
    BronzeAgeItems.Add(FName("Knife_Copper"));
    BronzeAgeItems.Add(FName("Hammer_Copper"));
    BronzeAgeItems.Add(FName("Anvil_Small"));
    BronzeAgeItems.Add(FName("Helmet_Copper"));
    BronzeAgeItems.Add(FName("Armor_Leather"));
    BronzeAgeItems.Add(FName("Bracers_Copper"));
    BronzeAgeItems.Add(FName("Greaves_Copper"));
    BronzeAgeItems.Add(FName("Boots_Leather"));
    BronzeAgeItems.Add(FName("Belt_Copper"));
    BronzeAgeItems.Add(FName("Meat_Cooked"));
    BronzeAgeItems.Add(FName("Fish_Cooked"));
    BronzeAgeItems.Add(FName("Soup"));
    BronzeAgeItems.Add(FName("Bread_Simple"));
    BronzeAgeItems.Add(FName("Beer"));
    BronzeAgeItems.Add(FName("Water_Clean"));
    BronzeAgeItems.Add(FName("Herb_Healing"));
    BronzeAgeItems.Add(FName("Bandage"));
    BronzeAgeItems.Add(FName("Antidote"));
    BronzeAgeItems.Add(FName("Water_Bottle"));
    BronzeAgeItems.Add(FName("Copper_Ore"));
    BronzeAgeItems.Add(FName("Copper_Ingot"));
    BronzeAgeItems.Add(FName("Tin_Ore"));
    BronzeAgeItems.Add(FName("Tin_Ingot"));
    BronzeAgeItems.Add(FName("Coal"));
    BronzeAgeItems.Add(FName("Leather"));
    BronzeAgeItems.Add(FName("Leather_Tanned"));
    BronzeAgeItems.Add(FName("Cloth_Raw"));

    MedievalItems.Add(FName("Sword_Iron"));
    MedievalItems.Add(FName("Sword_Long"));
    MedievalItems.Add(FName("Sword_TwoHand"));
    MedievalItems.Add(FName("Spear_Iron"));
    MedievalItems.Add(FName("Pike"));
    MedievalItems.Add(FName("Bow_Long"));
    MedievalItems.Add(FName("Crossbow"));
    MedievalItems.Add(FName("Arrow_Iron"));
    MedievalItems.Add(FName("Shield_Iron"));
    MedievalItems.Add(FName("Shield_Tower"));
    MedievalItems.Add(FName("Mace_War"));
    MedievalItems.Add(FName("Dagger_Iron"));
    MedievalItems.Add(FName("Axe_Battle"));
    MedievalItems.Add(FName("Axe_Iron"));
    MedievalItems.Add(FName("Pickaxe_Iron"));
    MedievalItems.Add(FName("Sickle_Iron"));
    MedievalItems.Add(FName("Knife_Iron"));
    MedievalItems.Add(FName("Hammer_Iron"));
    MedievalItems.Add(FName("Anvil_Large"));
    MedievalItems.Add(FName("Tongs"));
    MedievalItems.Add(FName("Bellows"));
    MedievalItems.Add(FName("Helmet_Iron"));
    MedievalItems.Add(FName("Helmet_Kettle"));
    MedievalItems.Add(FName("Helmet_Great"));
    MedievalItems.Add(FName("Armor_Chain"));
    MedievalItems.Add(FName("Armor_Plate"));
    MedievalItems.Add(FName("Armor_Full"));
    MedievalItems.Add(FName("Gauntlets_Iron"));
    MedievalItems.Add(FName("Boots_Iron"));
    MedievalItems.Add(FName("Cloak_Noble"));
    MedievalItems.Add(FName("Crown"));
    MedievalItems.Add(FName("Meat_Smoked"));
    MedievalItems.Add(FName("Fish_Smoked"));
    MedievalItems.Add(FName("Stew"));
    MedievalItems.Add(FName("Bread_Fine"));
    MedievalItems.Add(FName("Cheese"));
    MedievalItems.Add(FName("Wine"));
    MedievalItems.Add(FName("Mead"));
    MedievalItems.Add(FName("Potion_Small"));
    MedievalItems.Add(FName("Potion_Medium"));
    MedievalItems.Add(FName("Potion_Large"));
    MedievalItems.Add(FName("Potion_Stamina"));
    MedievalItems.Add(FName("Elixir_Strength"));
    MedievalItems.Add(FName("Bandage_Antiseptic"));
    MedievalItems.Add(FName("Iron_Ore"));
    MedievalItems.Add(FName("Iron_Ingot"));
    MedievalItems.Add(FName("Gold_Ore"));
    MedievalItems.Add(FName("Gold_Ingot"));
    MedievalItems.Add(FName("Silver_Ore"));
    MedievalItems.Add(FName("Silver_Ingot"));
    MedievalItems.Add(FName("Wool"));
    MedievalItems.Add(FName("Fur_Premium"));
    MedievalItems.Add(FName("Linen"));
}