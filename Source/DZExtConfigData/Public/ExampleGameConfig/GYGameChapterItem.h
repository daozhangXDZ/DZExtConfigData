#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GYGameChapterItem.generated.h"

USTRUCT(BlueprintType)
struct FChapertyItemProperty
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FString ChapterName;
	UPROPERTY(BlueprintReadWrite)
		FString NextChapeterName;
	UPROPERTY(BlueprintReadWrite)
		FString ProChapeterName;
	/**
	 * 章节最大怪物数目
	 */
	UPROPERTY(BlueprintReadWrite)
		int32 MaxMonestCount;
};