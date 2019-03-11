#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ToolCore/DZBaseExtConfigDataSeal.h"
#include "ToolCore/DZJSonDataSeal.h"
#include "GYPlayerConfig.generated.h"

DECLARE_LOG_CATEGORY_CLASS(GYGameConfig_PlayerConfigLog, Log, All);
USTRUCT(BlueprintType)
struct FGYPlayerConfig
{
	GENERATED_BODY()
public:
	void ReadGameConfigData(UDZBaseExtConfigDataSeal* pData)
	{
		bool vIsSuccess = false;
		this->Start_Nick = pData->GetString("Start_Nick", vIsSuccess);
		this->Start_BodyHeight = pData->GetFloat("Start_BodyHeight", vIsSuccess);
		this->StartGame_MaxHp = pData->GetInt("StartGame_MaxHp", vIsSuccess);
	}

public:
	UPROPERTY(BlueprintReadWrite, Category = "GYGameConfig|PlayerConfig")
		FString Start_Nick;
	UPROPERTY(BlueprintReadWrite, Category = "GYGameConfig|PlayerConfig")
		float Start_BodyHeight;
	UPROPERTY(BlueprintReadWrite, Category = "GYGameConfig|PlayerConfig")
		int32 StartGame_MaxHp;
};