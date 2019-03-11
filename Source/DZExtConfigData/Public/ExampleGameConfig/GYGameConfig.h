#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ToolCore/DZBaseExtConfigDataSeal.h"
#include "ToolCore/DZJSonDataSeal.h"
#include "GYPlayerConfig.h"
#include "GYGameChapterConfig.h"
#include "GYGameConfig.generated.h"


const FString ConfigData_PropertyLab = "BaseProperty";
DECLARE_LOG_CATEGORY_CLASS(GYGameConfigLog, Log, All);
USTRUCT(BlueprintType)
struct FGYGameConfig
{
	GENERATED_BODY()
public:
	void ReadGameConfigData(FString GameConfigFilePath)
	{
		UDZJSonDataSeal* configData = NewObject<UDZJSonDataSeal>();
		CurrConfigFilePath = GameConfigFilePath;
		if (configData->SetupLocFile(CurrConfigFilePath, EDZFolder::Project))
		{
			bool vIsSuccess = false;
			UDZBaseExtConfigDataSeal* vPropertyData = configData->GetObject(ConfigData_PropertyLab, vIsSuccess);
			if (vIsSuccess)
			{
				UE_LOG(GYGameConfigLog, Error, TEXT("GameConfig BaseProperty is unvalid! Input:\n'%s'"), *CurrConfigFilePath);
				this->MaxPlayerCount = vPropertyData->GetInt("MaxPlayerCount", vIsSuccess);
				this->GameMaxTime = vPropertyData->GetFloat("GameMaxTime", vIsSuccess);
				this->GameName = vPropertyData->GetString("GameName", vIsSuccess);
			}
			UDZBaseExtConfigDataSeal* vPlayerConfig = configData->GetObject("Player", vIsSuccess);
			if (vIsSuccess)
			{
				GamePlayerConfig.ReadGameConfigData(vPlayerConfig);
				UE_LOG(GYGameConfigLog, Error, TEXT("GameConfig's Player is unvalid! Input:\n'%s'"), *CurrConfigFilePath);
			}
			UDZBaseExtConfigDataSeal* vChapterConfig = configData->GetObject("Chapter", vIsSuccess);
			if (vIsSuccess)
			{
				GameChapterConfig.ReadGameConfigData(vChapterConfig);
				UE_LOG(GYGameConfigLog, Error, TEXT("GameConfig's Chapter is unvalid! Input:\n'%s'"), *CurrConfigFilePath);
			}
		}
		else
		{
			UE_LOG(GYGameConfigLog, Error, TEXT("GameConfig Path is unvalid! Input:\n'%s'"), *CurrConfigFilePath);
		}
	}

public:
	UPROPERTY(BlueprintReadWrite, Category = "GYGameConfig|BaseProperty")
	FString CurrConfigFilePath;
	UPROPERTY(BlueprintReadWrite, Category= "GYGameConfig|BaseProperty")
	FString GameName;
	UPROPERTY(BlueprintReadWrite, Category = "GYGameConfig|BaseProperty")
	float GameMaxTime;
	UPROPERTY(BlueprintReadWrite, Category = "GYGameConfig|BaseProperty")
	int32 MaxPlayerCount;


	UPROPERTY(BlueprintReadWrite, Category = "GYGameConfig|Property")
	FGYPlayerConfig GamePlayerConfig;

	UPROPERTY(BlueprintReadWrite, Category = "GYGameConfig|Property")
	FGYGameChapterConfig GameChapterConfig;
}; 