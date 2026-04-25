#include "Minimap.h"

FMinimapSettings UMinimapSystem::Settings;
TArray<FMapMarker> UMinimapSystem::Markers;

FVector UMinimapSystem::GetPlayerCoordinates()
{
    return FVector(0, 0, 0);
}

FText UMinimapSystem::GetCoordinatesText()
{
    FVector Coords = GetPlayerCoordinates();
    FString CoordString = FString::Printf(TEXT("X: %.0f Z: %.0f"), Coords.X, Coords.Y);
    return FText::FromString(CoordString);
}

float UMinimapSystem::GetCompassHeading()
{
    return 0.0f;
}

FText UMinimapSystem::GetCompassDirection()
{
    float Heading = GetCompassHeading();
    if (Heading >= 337.5f || Heading < 22.5f) return FText::FromString("N");
    if (Heading >= 22.5f && Heading < 67.5f) return FText::FromString("NO");
    if (Heading >= 67.5f && Heading < 112.5f) return FText::FromString("O");
    if (Heading >= 112.5f && Heading < 157.5f) return FText::FromString("SO");
    if (Heading >= 157.5f && Heading < 202.5f) return FText::FromString("S");
    if (Heading >= 202.5f && Heading < 247.5f) return FText::FromString("SW");
    if (Heading >= 247.5f && Heading < 292.5f) return FText::FromString("W");
    return FText::FromString("NW");
}

void UMinimapSystem::AddMapMarker(FMapMarker Marker)
{
    Markers.Add(Marker);
}

void UMinimapSystem::RemoveMapMarker(FName MarkerID)
{
    Markers.RemoveAll([&](FMapMarker M) { return M.MarkerID == MarkerID; });
}

TArray<FMapMarker> UMinimapSystem::GetVisibleMarkers(FVector PlayerLoc, float Range)
{
    TArray<FMapMarker> Visible;
    for (auto& Marker : Markers)
    {
        if (Marker.bIsVisible && FVector::Distance(Marker.Location, PlayerLoc) <= Range)
            Visible.Add(Marker);
    }
    return Visible;
}

void UMinimapSystem::SetZoom(float Zoom)
{
    Settings.ZoomLevel = FMath::Clamp(Zoom, 0.5f, 4.0f);
}

float UMinimapSystem::GetZoom()
{
    return Settings.ZoomLevel;
}

void UMinimapSystem::SetSettings(FMinimapSettings NewSettings)
{
    Settings = NewSettings;
}

FMinimapSettings UMinimapSystem::GetSettings()
{
    return Settings;
}

void UMinimapSystem::CenterMap()
{
}

void UMinimapSystem::ToggleFullMap()
{
}