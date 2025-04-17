

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LS_Snowball.generated.h"

class UStaticMeshComponent;
class USoundBase;
class UParticleSystem;


UCLASS()
class LASTSTAND_API ALS_Snowball : public AActor
{
	GENERATED_BODY()
	
public:
    ALS_Snowball();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& Hit);

public:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
    USoundBase* HitSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
    UParticleSystem* HitEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
    bool bDestroyOnHit = true;
 


};
