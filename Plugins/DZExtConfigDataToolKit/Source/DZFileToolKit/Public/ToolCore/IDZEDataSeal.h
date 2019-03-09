#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDZEDataSeal.generated.h"

UENUM(BlueprintType, Category = "DZFileToolKit")
enum class EDZFileType : uint8
{
	JSON,
	XML
};

UENUM(BlueprintType, Category = "DZFileToolKit")
enum class EDZFolder : uint8
{
	Content,
	Project
};

UENUM(BlueprintType, Category = "DZFileToolKit")
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
class DZFILETOOLKIT_API UIDZEDataSeal :public UInterface
{
	GENERATED_UINTERFACE_BODY()
}; 


class DZFILETOOLKIT_API IIDZEDataSeal
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "DZFileToolKit|IDataSeal")
	virtual bool SetupLocFile(const FString path, EDZFolder dirctionType) = 0;

	/**
	 * Setup from String
	 * @param dataString: this json string
	 */
	UFUNCTION(BlueprintCallable, Category = "DZFileToolKit|IDataSeal")
	virtual bool SetupSourceData(const FString dataString) = 0;
};
