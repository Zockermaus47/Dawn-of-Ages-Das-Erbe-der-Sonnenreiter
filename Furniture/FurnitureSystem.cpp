#include "FurnitureSystem.h"

FName UFurnitureSystem::HomeBuilding;
TMap<FText, FVector> UFurnitureSystem::Waypoints;

FFurnitureItem UFurnitureSystem::GetFurniture(FName ItemID)
{
    FFurnitureItem Item;
    Item.ItemID = ItemID;
    
    if (ItemID == "Bed_Simple")
    {
        Item.DisplayName = FText::FromString("Einfaches Bett");
        Item.Category = EFurnitureCategory::Bed;
        Item.Comfort = 10.0f;
        Item.GridSizeX = 2;
        Item.GridSizeY = 3;
    }
    else if (ItemID == "Bed_Luxury")
    {
        Item.DisplayName = FText::FromString("Luxus Bett");
        Item.Category = EFurnitureCategory::Bed;
        Item.Comfort = 30.0f;
        Item.GridSizeX = 2;
        Item.GridSizeY = 3;
    }
    else if (ItemID == "Chair_Wood")
    {
        Item.DisplayName = FText::FromString("Holz Stuhl");
        Item.Category = EFurnitureCategory::Chair;
        Item.Comfort = 5.0f;
        Item.GridSizeX = 1;
        Item.GridSizeY = 1;
    }
    else if (ItemID == "Table_Dinner")
    {
        Item.DisplayName = FText::FromString("Esstisch");
        Item.Category = EFurnitureCategory::Table;
        Item.Comfort = 0.0f;
        Item.GridSizeX = 3;
        Item.GridSizeY = 2;
    }
    else if (ItemID == "Shelf_Book")
    {
        Item.DisplayName = FText::FromString("Bucherregal");
        Item.Category = EFurnitureCategory::Shelf;
        Item.Comfort = 0.0f;
        Item.StorageSlots = 20.0f;
        Item.GridSizeX = 2;
        Item.GridSizeY = 1;
    }
    else if (ItemID == "Rug_Wool")
    {
        Item.DisplayName = FText::FromString("Wolle Teppich");
        Item.Category = EFurnitureCategory::Rug;
        Item.Comfort = 15.0f;
        Item.GridSizeX = 3;
        Item.GridSizeY = 2;
    }
    else if (ItemID == "Curtain")
    {
        Item.DisplayName = FText::FromString("Vorhang");
        Item.Category = EFurnitureCategory::Curtain;
        Item.Comfort = 0.0f;
        Item.GridSizeX = 1;
        Item.GridSizeY = 2;
    }
    else if (ItemID == "Lamp_Oil")
    {
        Item.DisplayName = FText::FromString("OlLampe");
        Item.Category = EFurnitureCategory::Lamp;
        Item.LightOutput = 100.0f;
    }
    else if (ItemID == "Plant_Potted")
    {
        Item.DisplayName = FText::FromString("Topfpflanze");
        Item.Category = EFurnitureCategory::Plant;
        Item.Comfort = 5.0f;
    }
    
    return Item;
}

FPlacedFurniture UFurnitureSystem::PlaceFurniture(FFurnitureItem Item, FVector Location)
{
    FPlacedFurniture Placed;
    Placed.InstanceID = FName(*FString::Printf(TEXT("Furniture_%d"), 0));
    Placed.Item = Item;
    Placed.Location = Location;
    Placed.bIsActive = true;
    return Placed;
}

bool UFurnitureSystem::RemoveFurniture(FName InstanceID)
{
    return true;
}

void UFurnitureSystem::RotateFurniture(FName InstanceID)
{
}

TArray<FPlacedFurniture> UFurnitureSystem::GetFurnitureInRoom(FName RoomID)
{
    return TArray<FPlacedFurniture>();
}

float UFurnitureSystem::GetRoomComfort(FName RoomID)
{
    return 0.0f;
}

int32 UFurnitureSystem::GetStorageSlots(FName RoomID)
{
    return 0;
}

void UFurnitureSystem::SetHome(FName BuildingID)
{
    HomeBuilding = BuildingID;
}

FName UFurnitureSystem::GetHome()
{
    return HomeBuilding;
}

bool UFurnitureSystem::TeleportToHome()
{
    return HomeBuilding != FName();
}

bool UFurnitureSystem::SetWaypoint(FVector Location, FText Name)
{
    Waypoints.Add(Name, Location);
    return true;
}

bool UFurnitureSystem::TeleportToWaypoint(FText Name)
{
    return Waypoints.Contains(Name);
}

TArray<FName> UFurnitureSystem::GetWaypoints()
{
    return TArray<FName>();
}