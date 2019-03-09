#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "DZBaseExtConfigDataSeal.h"
#include "Serialization/JsonWriter.h"
#include "Dom/JsonValue.h"
#include "DZJSonDataSeal.generated.h"


DECLARE_LOG_CATEGORY_CLASS(DZJsonDataSealLog, Log, All);

UCLASS()
class DZFILETOOLKIT_API UDZJSonDataSeal :public UDZBaseExtConfigDataSeal
{
	GENERATED_UCLASS_BODY()

protected:
	virtual bool SetupSourceData(const FString dataString) override;

public:

	void WriteObject(TSharedRef<TJsonWriter<TCHAR>> writer, FString key, FJsonValue* value);



public:
    // Implement IIDZEDataSeal 
	virtual FString ToString() override;
	virtual FString GetString(const FString& key, bool& success) const override;
	virtual bool GetBool(const FString& key, bool& success) const override;
	virtual int32 GetInt(const FString& key, bool& success) const override;
	virtual float GetFloat(const FString& key, bool& success) const override;
	virtual bool GetIsNull(const FString& key, bool& fieldExists) const override;
	virtual TArray<FString> GetStringArray(const FString& key, bool& success)override;
	virtual TArray<bool> GetBoolArray(const FString& key, bool& success) override;
	virtual TArray<int32> GetIntArray(const FString& key, bool& success) override;
	virtual TArray<float> GetFloatArray(const FString& key, bool& success) override;
	UDZBaseExtConfigDataSeal* GetObject(const FString& key, bool& success)override;
	TArray<UDZBaseExtConfigDataSeal*> GetObjectArray(const FString& key, bool& success)override;
	virtual TArray<FString> GetObjectKeys() override;

private:
	static UDZJSonDataSeal* Create();
	//End Implement IIDZEDataSeal 
private:
	TSharedPtr<FJsonObject> mData;
};