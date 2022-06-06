#pragma once

#include "Struct_TooltipProperties.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FStructTooltipProperties
{
	GENERATED_BODY()

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		FString TooltipText;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		UTexture2D* TooltipImage;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		float TooltipDuration;
};

USTRUCT(BlueprintType)
struct FStructTooltips
{
	GENERATED_BODY()

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		TArray<FStructTooltipProperties> ToolTips;
};