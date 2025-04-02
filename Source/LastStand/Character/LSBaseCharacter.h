#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LSBaseCharacter.generated.h"

UCLASS()
class LASTSTAND_API ALSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALSBaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    // 추가된 컴포넌트들
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UCapsuleComponent* CollisionCylinder;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UBoxComponent* LedgeDetector;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UCapsuleComponent* Push;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UWidgetComponent* Widget;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USceneComponent* SpringArm;

    // 본(Bone) 구조에 부착되는 Capsule 컴포넌트
    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* Head;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* Torso;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* HandL;
    
    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* HandR;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* UpArm_l;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* UpArm_r;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* LowArm_l;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* LowArm_r;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* FootL;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* FootR;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* UpLeg_l;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* UpLeg_r;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* LowLeg_l;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class UCapsuleComponent* LowLeg_r;

    UPROPERTY(VisibleAnywhere, Category = "Bones")
    class USceneComponent* Feet;
};
