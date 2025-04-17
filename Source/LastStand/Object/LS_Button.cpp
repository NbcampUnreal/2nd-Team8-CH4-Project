#include "LS_Button.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "LS_ObjectSpawnBox.h"
#include "LS_MovingActor.h"

ALS_Button::ALS_Button()
{
    PrimaryActorTick.bCanEverTick = true;

    Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
    RootComponent = Cube;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    Box->SetupAttachment(RootComponent);
    Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Box->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ALS_Button::BeginPlay()
{
    Super::BeginPlay();

    Box->OnComponentBeginOverlap.AddDynamic(this, &ALS_Button::OnBeginOverlap);

    if (UnpressedMesh)
    {
        Cube->SetStaticMesh(UnpressedMesh);
    }

    if (HasAuthority())
    {
        StartMovingActor();
    }
}

void ALS_Button::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!bActivated && OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Log, TEXT("OnBeginOverlap Triggered!"));
        ActivateButton();
    }
}

void ALS_Button::ActivateButton()
{
    bActivated = true;

    UE_LOG(LogTemp, Log, TEXT("Button Pressed!"));

    if (ActivateSound)
    {
        float RandomPitch = FMath::FRandRange(0.95f, 1.05f);
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
        UE_LOG(LogTemp, Log, TEXT("Timer started for spawning snowballs"));
        GetWorld()->GetTimerManager().SetTimer(
            SpawnTimerHandle,
            this,
            &ALS_Button::SpawnSnowballStep,
            SpawnInterval,
            true
        );
    }

    // 파티클 효과 활성화
    if (SpawnedMoveActor)
    {
        SpawnedMoveActor->ServerActivateKnockbackEffect();
    }
}

void ALS_Button::SpawnSnowballStep()
{
    if (!SnowballClass || !SpawnBoxRef || SnowballSpawnCount >= TotalSnowballsToSpawn)
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        return;
    }

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

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AActor* Snowball = GetWorld()->SpawnActor<AActor>(SnowballClass, SpawnLocation, SpawnRotation, SpawnParams);
    if (Snowball)
    {
        UE_LOG(LogTemp, Log, TEXT("Snowball spawned at %s"), *SpawnLocation.ToString());
    }

    SnowballSpawnCount++;
}

void ALS_Button::StartMovingActor()
{
    if (!SpawnBoxRef || !MoveActorClass) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    if (HasAuthority())
    {
        SpawnedMoveActor = GetWorld()->SpawnActor<ALS_MovingActor>(MoveActorClass, SpawnBoxRef->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
        if (SpawnedMoveActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("MoveActor Spawned"));
            SpawnedMoveActor->StartMoving(SpawnBoxRef->GetActorLocation());
        }
    }
}