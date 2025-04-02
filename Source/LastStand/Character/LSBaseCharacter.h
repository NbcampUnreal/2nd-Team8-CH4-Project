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

};
