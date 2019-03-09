#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "IDZEDataSeal.h"
#include "DZJSonDataSeal.generated.h"


DECLARE_LOG_CATEGORY_CLASS(JSONQueryLog, Log, All);

UCLASS(BlueprintType)
class DZTOOLKITRUNTIME_API UDZJSonDataSeal :public UObject, public IIDZEDataSeal
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool SetupLocFile(const FString path, EDZFolder dirctionType) override;

	virtual bool SetupSourceData(const FString dataString) override;

public:

	/**
	 * This function will write the supplied key and value to the JsonWriter
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "JSON To String", CompactNodeTitle = "->", Keywords = "cast text convert serialize"), Category = "DZJSonData")
	FString ToString();

	/**
	* This function will write the supplied key and value to the JsonWriter
		*
		* @param	writer			The JsonWriter to use
		* @param	key				Object key
		* @param	value			Object value
	*/
	void WriteObject(TSharedRef<TJsonWriter<TCHAR>> writer, FString key, FJsonValue* value);

private:
	//UPROPERTY()
	FString mPath;
	TSharedPtr<FJsonObject> mData;
};