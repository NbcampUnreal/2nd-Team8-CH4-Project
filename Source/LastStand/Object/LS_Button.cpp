#include "LS_Button.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "LS_ObjectSpawnBox.h"

ALS_Button::ALS_Button()
{
    PrimaryActorTick.bCanEverTick = false;

    Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
    RootComponent = Cube;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    Box->SetupAttachment(RootComponent);
    Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Box->SetCollisionResponseToAllChannels(ECR_Ignore);
    Box->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ALS_Button::BeginPlay()
{
   

    Box->OnComponentBeginOverlap.AddDynamic(this, &ALS_Button::OnBeginOverlap);

    if (UnpressedMesh)
    {
        Cube->SetStaticMesh(UnpressedMesh);
    }
}

void ALS_Button::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!bActivated && OtherActor && OtherActor != this)
    {
        ActivateButton();
    }
}

void ALS_Button::ActivateButton()
{
    bActivated = true;

    UE_LOG(LogTemp, Log, TEXT("Button Pressed"));

    if (ActivateSound)
    {
        float RandomPitch = FMath::FRandRange(0.95f, 1.05f); // 피치 랜덤화로 중복 재생 방지
        UGameplayStatics::PlaySoundAtLocation(this, ActivateSound, GetActorLocation(), 1.0f, RandomPitch);
    }

    if (PressedMesh)
    {
        Cube->SetStaticMesh(PressedMesh);
    }

    Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    SnowballSpawnCount = 0;

    if (SnowballClass && SpawnBoxRef)
    {
        GetWorld()->GetTimerManager().SetTimer(
            SpawnTimerHandle,
            this,
            &ALS_Button::SpawnSnowballStep,
            SpawnInterval,
            true
        );
    }
}

void ALS_Button::SpawnSnowballStep()
{
    if (!SnowballClass || !SpawnBoxRef) return;

    UBoxComponent* BoxComp = SpawnBoxRef->SpawnBox;
    if (!BoxComp) return;

    FVector Origin = BoxComp->GetComponentLocation();
    FVector Extent = BoxComp->GetScaledBoxExtent();

    FVector RandomOffset = FVector(
        FMath::FRandRange(-Extent.X, Extent.X),
        FMath::FRandRange(-Extent.Y, Extent.Y),
        FMath::FRandRange(-Extent.Z, Extent.Z)
    );

    FVector SpawnLocation = Origin + RandomOffset;
    FRotator SpawnRotation = FRotator::ZeroRotator;

    GetWorld()->SpawnActor<AActor>(SnowballClass, SpawnLocation, SpawnRotation);

    SnowballSpawnCount++;

    if (SnowballSpawnCount >= TotalSnowballsToSpawn)
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
    }
}