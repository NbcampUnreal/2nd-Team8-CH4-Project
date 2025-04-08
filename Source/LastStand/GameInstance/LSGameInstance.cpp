// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/LSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULSGameInstance::ApplyVolumeSettings()
{
    if (MasterSoundClass && MasterSoundMix)
    {
        UGameplayStatics::SetSoundMixClassOverride(this, MasterSoundMix, MasterSoundClass, MasterVolume, 1.0f, 0.0f);
        UGameplayStatics::PushSoundMixModifier(this, MasterSoundMix);
    }
}