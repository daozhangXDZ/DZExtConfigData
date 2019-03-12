#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ToolCore/DZBaseExtConfigDataSeal.h"
#include "ToolCore/DZJSonDataSeal.h"
#include "GYGameChapterItem.h"
#include "GYGameChapterConfig.generated.h"



DECLARE_LOG_CATEGORY_CLASS(GYGameConfig_ChapterLog, Log, All);
USTRUCT(BlueprintType)
struct FGYGameChapterConfig
{
	GENERATED_BODY()
public:
	void ReadGameConfigData(UDZBaseExtConfigDataSeal* pData)
	{
		bool vIsSuccess = false;
		this->StartGame_ChapterName = pData->GetString("StartGame_ChapterName", vIsSuccess);
		TArray<UDZBaseExtConfigDataSeal*> pChapterArr = pData->GetObjectArray("ChapterData", vIsSuccess);
		ChapterData.Reset();
		for (int32 i = 0; i < pChapterArr.Num(); i++)
		{
			FChapertyItemProperty ons;
			ons.ChapterName = pChapterArr[i]->GetString("ChapterName", vIsSuccess);
			ons.NextChapeterName = pChapterArr[i]->GetString("NextChapeterName", vIsSuccess);
			ons.ProChapeterName = pChapterArr[i]->GetString("ProChapeterName", vIsSuccess);
			ons.MaxMonestCount = pChapterArr[i]->GetInt("MaxMonestCount", vIsSuccess);
			ChapterData.Add(ons);
		}
	}

public:
	UPROPERTY(BlueprintReadWrite, Category = "GYGameConfig|PlayerConfig")
		FString StartGame_ChapterName;
	UPROPERTY(BlueprintReadWrite, Category = "GYGameConfig|PlayerConfig")
		TArray<FChapertyItemProperty> ChapterData;
};