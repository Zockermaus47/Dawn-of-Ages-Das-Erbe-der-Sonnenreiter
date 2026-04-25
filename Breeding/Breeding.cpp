#include "Breeding.h"

UBreedingSystem::UBreedingSystem()
{
}

FAnimalData UBreedingSystem::GetAnimalData(FName AnimalID)
{
    return FAnimalData();
}

bool UBreedingSystem::CanBreed(FAnimalInstance Animal1, FAnimalInstance Animal2)
{
    return false;
}

FAnimalInstance UBreedingSystem::Breed(FAnimalInstance Parent1, FAnimalInstance Parent2)
{
    return FAnimalInstance();
}

TMap<FName, int32> UBreedingSystem::Harvest(FAnimalInstance Animal)
{
    return TMap<FName, int32>();
}

void UBreedingSystem::Feed(FAnimalInstance& Animal, FName Food)
{
}

void UBreedingSystem::UpdateAnimal(FAnimalInstance& Animal, float DeltaTime)
{
}

float UBreedingSystem::CalculateProductivity(FAnimalInstance Animal)
{
    return 50.0f;
}

TArray<FAnimalData> UBreedingSystem::GetAllAnimals()
{
    return TArray<FAnimalData>();
}

void UBreedingSystem::FeedAnimal(FAnimalInstance& Animal, FName FoodID)
{
    Animal.Hunger = FMath::Clamp(Animal.Hunger + 30.0f, 0.0f, 100.0f);
    Animal.LastFed = 0.0f;
    Animal.HungerLevel = FMath::Max(0.0f, Animal.HungerLevel - 20.0f);
}

void UBreedingSystem::WaterAnimal(FAnimalInstance& Animal)
{
    Animal.Thirst = FMath::Clamp(Animal.Thirst + 40.0f, 0.0f, 100.0f);
    Animal.LastDrank = 0.0f;
    Animal.ThirstLevel = FMath::Max(0.0f, Animal.ThirstLevel - 20.0f);
}

void UBreedingSystem::InfectAnimal(FAnimalInstance& Animal, FName DiseaseID)
{
    if (Animal.Health > 30.0f && !Animal.bIsSick)
    {
        Animal.bIsSick = true;
        Animal.DiseaseID = DiseaseID;
        Animal.Health = FMath::Clamp(Animal.Health - 20.0f, 0.0f, 100.0f);
    }
}

void UBreedingSystem::CureAnimal(FAnimalInstance& Animal, FName CureItem)
{
    if (Animal.bIsSick)
    {
        Animal.bIsSick = false;
        Animal.DiseaseID = FName();
        Animal.Health = FMath::Clamp(Animal.Health + 30.0f, 0.0f, 100.0f);
    }
}

bool UBreedingSystem::CanReproduce(FAnimalInstance Animal)
{
    return Animal.bIsPregnant == false && 
           Animal.Age > 30 &&
           Animal.Health > 50.0f &&
           Animal.Hunger > 50.0f &&
           Animal.Thirst > 50.0f &&
           !Animal.bIsSick &&
           Animal.Mood == EAnimalMood::Estrus;
}

void UBreedingSystem::Reproduce(FAnimalInstance& Animal, float DeltaTime)
{
    if (Animal.bIsPregnant)
    {
        Animal.PregnancyProgress += DeltaTime * 5.0f;
        
        if (Animal.PregnancyProgress >= 100.0f)
        {
            Animal.bIsPregnant = false;
            Animal.PregnancyProgress = 0.0f;
        }
    }
}

void UBreedingSystem::UpdateAnimalNeeds(FAnimalInstance& Animal, float DeltaTime)
{
    Animal.LastFed += DeltaTime;
    Animal.LastDrank += DeltaTime;
    
    if (Animal.LastFed > 10.0f)
        Animal.HungerLevel += DeltaTime * 2.0f;
    
    if (Animal.LastDrank > 10.0f)
        Animal.ThirstLevel += DeltaTime * 3.0f;
    
    Animal.Hunger = FMath::Clamp(100.0f - Animal.HungerLevel, 0.0f, 100.0f);
    Animal.Thirst = FMath::Clamp(100.0f - Animal.ThirstLevel, 0.0f, 100.0f);
    
    if (Animal.bIsSick)
        Animal.Health = FMath::Clamp(Animal.Health - DeltaTime * 5.0f, 0.0f, 100.0f);
    
    if (Animal.HungerLevel >= 80.0f || Animal.ThirstLevel >= 80.0f)
        Animal.Mood = EAnimalMood::Hungry;
    else if (Animal.bIsSick)
        Animal.Mood = EAnimalMood::Sick;
    else
        Animal.Mood = EAnimalMood::Happy;
}

float UBreedingSystem::GetHunger(FAnimalInstance Animal)
{
    return Animal.Hunger;
}

float UBreedingSystem::GetThirst(FAnimalInstance Animal)
{
    return Animal.Thirst;
}

bool UBreedingSystem::IsSick(FAnimalInstance Animal)
{
    return Animal.bIsSick;
}

int32 UBreedingSystem::CollectEggs(FAnimalInstance& Animal)
{
    int32 Collected = Animal.Eggs;
    Animal.Eggs = 0;
    Animal.EggTimer = 0.0f;
    return Collected;
}

void UBreedingSystem::PetAnimal(FAnimalInstance& Animal)
{
    Animal.Affection = FMath::Clamp(Animal.Affection + 10.0f, 0.0f, 100.0f);
    Animal.CareLevel = FMath::Clamp(Animal.CareLevel + 5.0f, 0.0f, 100.0f);
    Animal.LastPet = 0.0f;
    Animal.Mood = EAnimalMood::Happy;
}

void UBreedingSystem::GroomAnimal(FAnimalInstance& Animal)
{
    Animal.CareLevel = FMath::Clamp(Animal.CareLevel + 15.0f, 0.0f, 100.0f);
    Animal.LastGroomed = 0.0f;
    
    if (Animal.bIsSick && Animal.CareLevel > 70.0f)
    {
        Animal.bIsSick = false;
        Animal.DiseaseID = FName();
    }
}

void UBreedingSystem::UpdateGrowth(FAnimalInstance& Animal, float DeltaTime)
{
    if (Animal.GrowthStage < 100.0f)
    {
        float GrowthRate = 1.0f;
        
        if (Animal.CareLevel > 80.0f)
            GrowthRate *= 1.5f;
        else if (Animal.CareLevel < 30.0f)
            GrowthRate *= 0.5f;
        
        if (Animal.Affection > 70.0f)
            GrowthRate *= 1.2f;
        
        Animal.GrowthStage += DeltaTime * GrowthRate;
        Animal.DaysOld += DeltaTime / 86400.0f;
    }
}

float UBreedingSystem::GetAffection(FAnimalInstance Animal)
{
    return Animal.Affection;
}

float UBreedingSystem::GetCareLevel(FAnimalInstance Animal)
{
    return Animal.CareLevel;
}

int32 UBreedingSystem::GetGrowthStage(FAnimalInstance Animal)
{
    if (Animal.GrowthStage < 25.0f) return 0;
    if (Animal.GrowthStage < 50.0f) return 1;
    if (Animal.GrowthStage < 75.0f) return 2;
    if (Animal.GrowthStage < 100.0f) return 3;
    return 4;
}

bool UBreedingSystem::IsFullyGrown(FAnimalInstance Animal)
{
    return Animal.GrowthStage >= 100.0f;
}

float UBreedingSystem::CalculateProductQuality(FAnimalInstance Animal)
{
    float Quality = 50.0f;
    
    Quality += (Animal.Affection - 50.0f) * 0.3f;
    Quality += (Animal.CareLevel - 50.0f) * 0.2f;
    Quality += (Animal.Health - 50.0f) * 0.2f;
    
    if (Animal.bIsSick)
        Quality *= 0.5f;
    
    return FMath::Clamp(Quality, 10.0f, 100.0f);
}

int32 UBreedingSystem::MilkCow(FAnimalInstance& Animal)
{
    if (Animal.AnimalType == EAnimalType::Cow && Animal.Health > 50.0f && !Animal.bIsSick)
    {
        float MilkAmount = 2.0f + (Animal.CareLevel * 0.05f);
        return (int32)MilkAmount;
    }
    return 0;
}

int32 UBreedingSystem::ShearSheep(FAnimalInstance& Animal)
{
    if (Animal.AnimalType == EAnimalType::Sheep && Animal.CareLevel > 30.0f)
    {
        return (int32)(1.0f + Animal.CareLevel / 30.0f);
    }
    return 0;
}

bool UBreedingSystem::MountAnimal(FAnimalInstance& Animal)
{
    return Animal.AnimalType == EAnimalType::Horse && Animal.Health > 30.0f;
}

bool UBreedingSystem::DismountAnimal(FAnimalInstance& Animal)
{
    return true;
}

bool UBreedingSystem::IsMounted(FAnimalInstance Animal)
{
    return Animal.bIsDiving;
}

bool UBreedingSystem::RideAnimal(FAnimalInstance& Animal, FVector Direction)
{
    if (MountAnimal(Animal))
    {
        return true;
    }
    return false;
}

int32 UBreedingSystem::HarvestHoney(FAnimalInstance& Animal)
{
    return 0;
}