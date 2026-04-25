#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuctionHouse.generated.h"

UENUM(BlueprintType)
enum class EAuctionCategory : uint8
{
    Weapons   UMETA(DisplayName = "Weapons"),
    Armor    UMETA(DisplayName = "Armor"),
    Items    UMETA(DisplayName = "Items"),
    Materials UMETA(DisplayName = "Materials"),
    Pets     UMETA(DisplayName = "Pets"),
    Mounts   UMETA(DisplayName = "Mounts"),
    Housing  UMETA(DisplayName = "Housing")
};

USTRUCT(BlueprintType)
struct FAuctionItem
{
    GENERATED_BODY()
    FName ListingID;
    FName ItemID;
    FName SellerID;
    int32 Price = 100;
    int32 Quantity = 1;
    float Duration = 48.0f;
    bool bBuyNow = false;
    int32 BuyNowPrice = 0;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UAuctionHouseSystem : public UObject
{
    GENERATED_BODY()
public:
    static bool ListItem(FName ItemID, int32 Price, int32 Quantity);
    static bool BuyNow(FName ListingID);
    static bool CancelListing(FName ListingID);
    static TArray<FAuctionItem> GetListings(EAuctionCategory Category);
    static TArray<FAuctionItem> Search(FName SearchTerm);
    static FAuctionItem GetListing(FName ListingID);
    static bool PlaceBid(FName ListingID, int32 Amount);
    static void ExpireListings();
    static int32 GetTax(int32 Price);
    static int32 GetTotalSales();
};