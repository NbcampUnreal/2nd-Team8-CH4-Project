#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterData.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CharacterDisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UTexture2D> CharacterImg;
};
