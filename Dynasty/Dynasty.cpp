#include "Dynasty.h"

UDynastySystem::UDynastySystem()
{
}

FDynasty UDynastySystem::CreateDynasty(FText Name)
{
    return FDynasty();
}

void UDynastySystem::AddMember(FDynasty& Dynasty, FFamilyMember Member)
{
}

void UDynastySystem::RemoveMember(FDynasty& Dynasty, FName MemberID)
{
}

void UDynastySystem::Marry(FDynasty& Dynasty, FName Member1ID, FName Member2ID)
{
}

FFamilyMember UDynastySystem::BirthChild(FDynasty& Dynasty, FName Parent1ID, FName Parent2ID)
{
    return FFamilyMember();
}

void UDynastySystem::PassAway(FDynasty& Dynasty, FName MemberID)
{
}

void UDynastySystem::AdvanceGeneration(FDynasty& Dynasty)
{
}