#include "LS_ObjectSpawnBox.h"
#include "Components/BoxComponent.h"

ALS_ObjectSpawnBox::ALS_ObjectSpawnBox()
{
    PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
    SpawnBox->SetupAttachment(RootComponent);
    SpawnBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
    SpawnBox->SetHiddenInGame(true);
    SpawnBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// GetComponentLocation()으로 위치 가져오기
FVector ALS_ObjectSpawnBox::GetBoxLocation() const
{
    return SpawnBox ? SpawnBox->GetComponentLocation() : FVector::ZeroVector; // SpawnBox가 유효할 때만 위치 반환
}