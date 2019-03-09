#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "IDZEDataSeal.h"
#include "DZBaseExtConfigDataSeal.generated.h"

DECLARE_LOG_CATEGORY_CLASS(BaseExtConfigDataSeleLog, Log, All);

UCLASS()
class DZFILETOOLKIT_API UDZBaseExtConfigDataSeal :public UObject, public IIDZEDataSeal
{
	GENERATED_UCLASS_BODY()

public:
	bool SetupLocFile(const FString path, EDZFolder dirctionType);

protected:
	virtual bool SetupSourceData(const FString dataString) override;
	
public:
/**
 * This function will write the supplied key and value to the JsonWriter
 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String", CompactNodeTitle = "->", Keywords = "cast text convert serialize"), Category = "DZExtConfigData|DZFileToolKit")
	virtual FString ToString();

	/**
	* Tries to get a string from the field data by key, returns the string when successful
	*
	* @param	key			Key
	* @param	success		Was the string field found?
	*
	* @return	The requested string, empty if failed
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Field"), Category = "DZExtConfigData|DZFileToolKit")
	virtual FString GetString(const FString& key, bool& success) const;

	/**
	* Tries to get a boolean from the field data by key, returns the boolean when successful
	*
	* @param	key			Key
	* @param	success		Was the boolean field found?
	*
	* @return	The requested boolean, always false when failed
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Boolean Field"), Category = "DZExtConfigData|DZFileToolKit")
	virtual bool GetBool(const FString& key, bool& success) const;

	/**
	* Tries to get an integer from the field data by key, returns the integer when successful
	*
	* @param	key			Key
	* @param	success		Was the integer field found?
	*
	* @return	The requested integer, always 0 when failed
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Integer Field"), Category = "DZExtConfigData|DZFileToolKit")
		virtual int32 GetInt(const FString& key, bool& success) const;

	/**
	* Tries to get a float from the field data by key, returns the float when successful
	*
	* @param	key			Key
	* @param	success		Was the float field found?
	*
	* @return	The requested float, always 0.0 when failed
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Float Field"), Category = "DZExtConfigData|DZFileToolKit")
		virtual float GetFloat(const FString& key, bool& success) const;

	/**
	* Checks if a field is null
	*
	* @param	key			Key
	* @param	fieldExists		Was the field found?
	*
	* @return	If the field is null. False if it's not or it was not found.
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Field Is Null"), Category = "DZExtConfigData|DZFileToolKit")
		virtual bool GetIsNull(const FString& key, bool& fieldExists) const;

	/**
	* Gets a string array from the post data with the given key
	*
	* @param	key						Key
	* @param	success		Was the field found?
	*
	* @return	The requested array of strings
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Array Field"), Category = "DZExtConfigData|DZFileToolKit")
		virtual TArray<FString> GetStringArray(const FString& key, bool& success);

	/**
	* Gets a boolean array from the post data with the given key
	*
	* @param	key						Key
	* @param	success		Was the field found?
	*
	* @return	The requested array of booleans
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Boolean Array Field"), Category = "DZExtConfigData|DZFileToolKit")
		virtual TArray<bool> GetBoolArray(const FString& key, bool& success);

	/**
	* Gets an integer array from the post data with the given key
	*
	* @param	key						Key
	* @param	success		Was the field found?
	*
	* @return	The requested array of integers
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Integer Array Field"), Category = "DZExtConfigData|DZFileToolKit")
		virtual TArray<int32> GetIntArray(const FString& key, bool& success);

	/**
	* Gets a float array from the post data with the given key
	*
	* @param	key			Key
	* @param	success		Was the field found?
	*
	* @return	The requested array of floats
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Float Array Field"), Category = "DZExtConfigData|DZFileToolKit")
		virtual TArray<float> GetFloatArray(const FString& key, bool& success);

	/**
	* Gets the post data object from the post data with the given key
	*
	* @param	key						Key
	* @param	success		Was the object field found?
	*
	* @return	The object itself
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Field"), Category = "DZExtConfigData|DZFileToolKit")
		virtual UDZBaseExtConfigDataSeal* GetObject(const FString& key, bool& success);

	/**
	* Gets an object array from the post data with the given key
	*
	* @param	key						Key
	* @param	success		Was the field found?
	*
	* @return	The requested post data objects
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Array Field"), Category = "DZExtConfigData|DZFileToolKit")
		virtual TArray<UDZBaseExtConfigDataSeal*> GetObjectArray(const FString& key, bool& success);

	/**
	* Gets the keys from the supplied object
	*
	* @param	key						Key
	*
	* @return	Array of keys
	*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Keys"), Category = "DZExtConfigData|DZFileToolKit")
		virtual TArray<FString> GetObjectKeys();

public:
	UPROPERTY(BlueprintReadOnly, Category = "DZExtConfigData")
	FString mPath;
};
