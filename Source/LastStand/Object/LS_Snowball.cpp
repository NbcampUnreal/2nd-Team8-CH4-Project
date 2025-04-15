#include "LS_Snowball.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Actor_Component/LS_KnockbackComponent.h"

ALS_Snowball::ALS_Snowball()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    // 네트워크 복제 설정
    SetReplicates(true);
    SetReplicateMovement(true);

    // 서버에서만 물리 활성화
    if (HasAuthority())
    {
        Mesh->SetSimulatePhysics(true);
    }
    else
    {
        Mesh->SetSimulatePhysics(false);
    }

    Mesh->SetNotifyRigidBodyCollision(true);
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
    Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    Mesh->SetCollisionObjectType(ECC_PhysicsBody);
}

void ALS_Snowball::BeginPlay()
{
    Super::BeginPlay();

    Mesh->OnComponentHit.AddDynamic(this, &ALS_Snowball::OnHit);
}

void ALS_Snowball::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        if (OtherActor->ActorHasTag("Player"))
        {
            if (ULS_KnockbackComponent* Knockback = OtherActor->FindComponentByClass<ULS_KnockbackComponent>())
            {
                Knockback->ApplyKnockback(GetActorLocation(), 5000.0f, 0.6f);
            }
        }

        if (HitSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
        }

        if (HitEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorTransform());
        }

        Destroy();
    }
}