#include "Particles/ParticleSystemComponent.h"
#include "LS_MovingActor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


ALS_MovingActor::ALS_MovingActor()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    SetReplicateMovement(true);

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    KnockbackEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("KnockbackEffect"));
    KnockbackEffect->SetupAttachment(RootComponent);
    KnockbackEffect->bAutoActivate = false;
    KnockbackEffect->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    KnockbackEffect->SetCollisionResponseToAllChannels(ECR_Ignore);
    KnockbackEffect->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ALS_MovingActor::ActivateKnockbackEffect()
{
    if (KnockbackEffect)
    {
        KnockbackEffect->Activate(true);
        KnockbackEffect->OnComponentBeginOverlap.AddDynamic(this, &ALS_MovingActor::OnKnockbackOverlap);
    }
}

void ALS_MovingActor::OnKnockbackOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (ACharacter* HitPlayer = Cast<ACharacter>(OtherActor))
    {
        FVector Direction = (HitPlayer->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        float Strength = 1200.f;

        if (UCharacterMovementComponent* MoveComp = HitPlayer->GetCharacterMovement())
        {
            MoveComp->Velocity = Direction * Strength;
        }
    }
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

    if (HasAuthority()) // 서버에서만 이동 로직 수행
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
    if (HasAuthority()) // 서버에서만 동작
    {
        InitialStartLocation = NewStartLocation;
        EndLocation = InitialStartLocation + FVector(0, MoveRange, 0);
        CurrentTarget = EndLocation;
    }
}
