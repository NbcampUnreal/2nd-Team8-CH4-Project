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

    // 서버에서만 이동 액터 생성
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
}

void ALS_Button::StartMovingActor()
{
    if (!SpawnBoxRef || !MoveActorClass) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    if (HasAuthority()) // 서버에서만 스폰
    {
        ALS_MovingActor* MovingActor = GetWorld()->SpawnActor<ALS_MovingActor>(MoveActorClass, SpawnBoxRef->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
        if (MovingActor)
        {
            MovingActor->StartMoving(SpawnBoxRef->GetActorLocation());
        }
    }
}
