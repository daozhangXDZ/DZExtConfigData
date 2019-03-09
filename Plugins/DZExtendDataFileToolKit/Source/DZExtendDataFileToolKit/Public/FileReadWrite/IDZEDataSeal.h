#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDZEDataSeal.generated.h"

UENUM(BlueprintType, Category = "DZToolKit|Runtime|DZFUNLIB")
enum class EDZFolder : uint8
{
	Content,
	Project
};

UENUM(BlueprintType, Category = "DZToolKit|Runtime|DZFUNLIB")
enum class EDZFileLoadResult : uint8
{
	Success = 0,
	HttpFailed,
	ParsingFailed
};
/**
 * This is Extend Render or Wirte BaseData
 */
UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class DZTOOLKITRUNTIME_API UIDZEDataSeal :public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class DZTOOLKITRUNTIME_API IIDZEDataSeal
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "DZToolKit|Runtime|DZFUNLIB")
	virtual bool SetupLocFile(const FString path, EDZFolder dirctionType) = 0;

	/**
	 * Setup from String
	 * @param dataString: this json string
	 */
	UFUNCTION(BlueprintCallable, Category = "DZToolKit|Runtime|DZFUNLIB")
	virtual bool SetupSourceData(const FString dataString) = 0;
};
