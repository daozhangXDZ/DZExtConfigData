#include "DZJSonDataSeal.h"
#include "Engine/Engine.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"


#define LOCTEXT_NAMESPACE "DZJSonDataSeal"
UDZJSonDataSeal::UDZJSonDataSeal(const FObjectInitializer& objs)
	:Super(objs)
{

}


bool UDZJSonDataSeal::SetupSourceData(const FString dataString)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(dataString);
	bool isDeserialized = FJsonSerializer::Deserialize(JsonReader, mData);

	if (!isDeserialized || !mData.IsValid())
	{
		UE_LOG(DZJsonDataSealLog, Error, TEXT("JSON data is invalid! Input:\n'%s'"), *dataString);
		return false;
	}
	return true;
}

FString UDZJSonDataSeal::ToString()
{
	FString outStr;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&outStr);
	WriteObject(JsonWriter, "", new FJsonValueObject(mData));
	JsonWriter->Close();

	return outStr;
}

void UDZJSonDataSeal::WriteObject(TSharedRef<TJsonWriter<TCHAR>> writer, FString key, FJsonValue* value)
{
	if (value->Type == EJson::Null)
	{
		if (key.Len() > 0)
		{
			writer->WriteNull(key);
		}
		else
		{
			writer->WriteNull();
		}
	}
	if (value->Type == EJson::String)
	{
		if (key.Len() > 0)
		{
			writer->WriteValue(key, value->AsString());
		}
		else
		{
			writer->WriteValue(value->AsString());
		}
	}
	if (value->Type == EJson::Boolean)
	{
		if (key.Len() > 0)
		{
			writer->WriteValue(key, value->AsBool());
		}
		else
		{
			writer->WriteValue(value->AsBool());
		}
	}
	if (value->Type == EJson::Number)
	{
		if (key.Len() > 0)
		{
			writer->WriteValue(key, value->AsNumber());
		}
		else
		{
			writer->WriteValue(value->AsNumber());
		}
	}
	else if (value->Type == EJson::Object)
	{
		if (key.Len() > 0)
		{
			writer->WriteObjectStart(key);
		}
		else
		{
			writer->WriteObjectStart();
		}
		TSharedPtr<FJsonObject> objectData = value->AsObject();
		for (auto objectValue = objectData->Values.CreateIterator(); objectValue; ++objectValue)
		{			WriteObject(writer, objectValue.Key(), objectValue.Value().Get());
		}

		writer->WriteObjectEnd();
	}
	else if (value->Type == EJson::Array)
	{
		writer->WriteArrayStart(key);

		TArray<TSharedPtr<FJsonValue>> objectArray = value->AsArray();
		for (int32 i = 0; i < objectArray.Num(); i++)
		{
			WriteObject(writer, "", objectArray[i].Get());
		}

		writer->WriteArrayEnd();
	}
}

FString UDZJSonDataSeal::GetString(const FString & key, bool & success) const
{
	FString outData = "";
	success = false;
	if (mData.IsValid())
	{
		if (mData->TryGetStringField(key, outData))
		{
			UE_LOG(DZJsonDataSealLog, Error, TEXT("entry '%s' not found in the field data!"), *key);
			success = true;
		}
		else
		{
			success = false;
		}
	}
	return outData;
}

bool UDZJSonDataSeal::GetBool(const FString & key, bool & success) const
{
	bool outData = "";
	success = false;
	if (mData.IsValid())
	{
		if (mData->TryGetBoolField(key, outData))
		{
			UE_LOG(DZJsonDataSealLog, Error, TEXT("entry '%s' not found in the field data!"), *key);
			success = true;
		}
		else
		{
			success = false;
		}
	}
	
	return outData;
}

int32 UDZJSonDataSeal::GetInt(const FString & key, bool & success) const
{
	double outData = 0.0;
	success = false;
	if (mData.IsValid())
	{
		if (mData->TryGetNumberField(key, outData))
		{
			UE_LOG(DZJsonDataSealLog, Error, TEXT("entry '%s' not found in the field data!"), *key);
				success = true;
		}
		else
		{
			success = false;
		}
	}
	return outData;
}

float UDZJSonDataSeal::GetFloat(const FString & key, bool & success) const
{
	double outData = 0.0;
	success = false;
	if (mData.IsValid())
	{
		if (mData->TryGetNumberField(key, outData))
		{
			UE_LOG(DZJsonDataSealLog, Error, TEXT("entry '%s' not found in the field data!"), *key);
			success = true;
		}
		else
		{
			success = false;
		}
	}
	return static_cast<float>(outData);
}

bool UDZJSonDataSeal::GetIsNull(const FString & key, bool & success) const
{
	if (!mData->HasField(key))
	{
		UE_LOG(DZJsonDataSealLog, Error, TEXT("entry '%s' not found in the field data!"), *key);
		success = false;
		return false;
	}

	success = true;
	return mData->HasTypedField<EJson::Null>(key);
}

TArray<FString> UDZJSonDataSeal::GetStringArray(const FString & key, bool & success)
{
	TArray<FString> stringArray;
	success = false;
	if (mData.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>> *arrayPtr;
		if (mData->TryGetArrayField(*key, arrayPtr))
		{
			for (int32 i = 0; i < arrayPtr->Num(); i++)
			{
				stringArray.Add((*arrayPtr)[i]->AsString());
			}
			success = true;
		}
		else
		{
			UE_LOG(DZJsonDataSealLog, Error, TEXT("Array entry '%s' not found in the field data!"), *key);
			success = false;
		}
	}
	return stringArray;
}

TArray<bool> UDZJSonDataSeal::GetBoolArray(const FString & key, bool & success)
{
	TArray<bool> DataArray;
	success = false;
	if (mData.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>> *arrayPtr;
		if (mData->TryGetArrayField(*key, arrayPtr))
		{
			for (int32 i = 0; i < arrayPtr->Num(); i++)
			{
				DataArray.Add((*arrayPtr)[i]->AsBool());
			}
			success = true;
		}
		else
		{
			UE_LOG(DZJsonDataSealLog, Error, TEXT("Array entry '%s' not found in the field data!"), *key);
			success = false;
		}
	}
	return DataArray;
}

TArray<int32> UDZJSonDataSeal::GetIntArray(const FString & key, bool & success)
{
	TArray<int32> DataArray;
	const TArray<TSharedPtr<FJsonValue>> *arrayPtr;
	success = false;
	if (mData.IsValid())
	{
		if (mData->TryGetArrayField(*key, arrayPtr))
		{
			for (int32 i = 0; i < arrayPtr->Num(); i++)
			{
				DataArray.Add(static_cast<int32>((*arrayPtr)[i]->AsNumber()));
			}
			success = true;
		}
		else
		{
			UE_LOG(DZJsonDataSealLog, Error, TEXT("Array entry '%s' not found in the field data!"), *key);
			success = false;
		}
	}
	return DataArray;
}

TArray<float> UDZJSonDataSeal::GetFloatArray(const FString & key, bool & success)
{
	TArray<float> DataArray;
	success = false;
	if (mData.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>> *arrayPtr;

		if (mData->TryGetArrayField(*key, arrayPtr))
		{
			for (int32 i = 0; i < arrayPtr->Num(); i++)
			{
				DataArray.Add(static_cast<float>((*arrayPtr)[i]->AsNumber()));
			}
			success = true;
		}
		else
		{
			UE_LOG(DZJsonDataSealLog, Error, TEXT("Array entry '%s' not found in the field data!"), *key);
			success = false;
		}
	}

	return DataArray;
}

UDZBaseExtConfigDataSeal * UDZJSonDataSeal::GetObject(const FString & key, bool & success)
{
	UDZJSonDataSeal* fieldObj = NULL;
	success = false;
	if (mData.IsValid())
	{
		const TSharedPtr<FJsonObject> *outPtr;
		if (mData->TryGetObjectField(*key, outPtr))
		{
			fieldObj = UDZJSonDataSeal::Create();
			fieldObj->mData = *outPtr;
			success = true;
		}
		else
		{
			UE_LOG(DZJsonDataSealLog, Error, TEXT("Entry '%s' not found in the field data!"), *key);
			success = false;
			return NULL;
		}
	}
	
	return fieldObj;
}

TArray<UDZBaseExtConfigDataSeal*> UDZJSonDataSeal::GetObjectArray(const FString & key, bool & success)
{
	TArray<UDZBaseExtConfigDataSeal*> objectArray;
	success = false;
	if (mData.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>> *arrayPtr;
		if (mData->TryGetArrayField(*key, arrayPtr))
		{
			for (int32 i = 0; i < arrayPtr->Num(); i++)
			{
				UDZJSonDataSeal* pageData = Create();
				pageData->mData = (*arrayPtr)[i]->AsObject();
				objectArray.Add(pageData);
			}
			success = true;
		}
		else
		{
			UE_LOG(DZJsonDataSealLog, Error, TEXT("Array entry '%s' not found in the field data!"), *key);
			success = false;
		}
	}
	return objectArray;
}

TArray<FString> UDZJSonDataSeal::GetObjectKeys()
{
	TArray<FString> stringArray;
	if (mData.IsValid())
	{
		for (auto currJsonValue = mData->Values.CreateConstIterator(); currJsonValue; ++currJsonValue)
		{
			stringArray.Add((*currJsonValue).Key);
		}
	}

	return stringArray;
}

UDZJSonDataSeal * UDZJSonDataSeal::Create()
{
	UDZJSonDataSeal* vSeal = NewObject<UDZJSonDataSeal>();
	return vSeal;
}
#undef LOCTEXT_NAMESPACE