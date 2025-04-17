#include "LS_MovingActor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ALS_MovingActor::ALS_MovingActor()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    SetReplicateMovement(true);

    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    RootComponent = SceneComponent;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);

    KnockbackEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("KnockbackEffect"));
    KnockbackEffect->SetupAttachment(RootComponent);
    KnockbackEffect->bAutoActivate = false;
    KnockbackEffect->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    KnockbackEffect->SetCollisionResponseToAllChannels(ECR_Ignore);
    KnockbackEffect->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ALS_MovingActor::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        InitialStartLocation = GetActorLocation();
        EndLocation = InitialStartLocation + FVector(0, MoveRange, 0);
        CurrentTarget = EndLocation;
    }
}

void ALS_MovingActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime); 

    if (HasAuthority())
    {
        MoveActor(DeltaTime);
    }
}

void ALS_MovingActor::MoveActor(float DeltaTime)
{
    FVector Direction = (CurrentTarget - GetActorLocation()).GetSafeNormal();
    FVector NewLocation = GetActorLocation() + Direction * MoveSpeed * DeltaTime;
    SetActorLocation(NewLocation);

    if (FVector::Dist(GetActorLocation(), CurrentTarget) < 50.0f)
    {
        CurrentTarget = (CurrentTarget == EndLocation) ? InitialStartLocation : EndLocation;
    }
}

void ALS_MovingActor::StartMoving(FVector NewStartLocation)
{
    if (HasAuthority())
    {
        InitialStartLocation = NewStartLocation;
        EndLocation = InitialStartLocation + FVector(0, MoveRange, 0);
        CurrentTarget = EndLocation;
    }
}

void ALS_MovingActor::ServerActivateKnockbackEffect_Implementation()
{
    if (KnockbackEffect)
    {
        KnockbackEffect->Activate(true);

        UE_LOG(LogTemp, Log, TEXT("KnockbackEffect activated"));
    }
}

void ALS_MovingActor::OnKnockbackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (ACharacter* HitPlayer = Cast<ACharacter>(OtherActor))
    {
        FVector Direction = (HitPlayer->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        Direction.Z += VerticalBoost;
        Direction.Normalize();

        if (UCharacterMovementComponent* MoveComp = HitPlayer->GetCharacterMovement())
        {
            MoveComp->Launch(Direction * KnockbackStrength);
        }

        UE_LOG(LogTemp, Log, TEXT("Player hit by knockback effect"));
    }
}
