#include "LSBaseCharacter.h"

ALSBaseCharacter::ALSBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ALSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

