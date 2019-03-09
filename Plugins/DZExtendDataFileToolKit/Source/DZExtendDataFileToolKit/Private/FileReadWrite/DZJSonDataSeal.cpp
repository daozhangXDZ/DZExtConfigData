#include "DZJSonDataSeal.h"
#include "Engine/Engine.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"


#define LOCTEXT_NAMESPACE "JSONQuery"
UDZJSonDataSeal::UDZJSonDataSeal(const FObjectInitializer& objs)
	:Super(objs)
{

}

bool UDZJSonDataSeal::SetupLocFile(const FString path, EDZFolder dirctionType)
{
	FString Result;
	FString StartPath;
	switch (dirctionType)
	{
		case EDZFolder::Content: StartPath = FPaths::ProjectContentDir(); break;
		case EDZFolder::Project:
		default: StartPath = FPaths::ProjectDir(); break;
	}
	FString FullJsonPath = FPaths::ConvertRelativePathToFull(StartPath / path);
	mPath = path;
	if (!FFileHelper::LoadFileToString(Result, *FullJsonPath))
	{
		UE_LOG(JSONQueryLog, Error, TEXT("Can't load json data from %s"), *FullJsonPath);
		return false;
	}
	return SetupSourceData(Result);
}

bool UDZJSonDataSeal::SetupSourceData(const FString dataString)
{
	//mData = pdata;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(dataString);

	// Deserialize the JSON data
	bool isDeserialized = FJsonSerializer::Deserialize(JsonReader, mData);

	if (!isDeserialized || !mData.IsValid())
	{
		UE_LOG(JSONQueryLog, Error, TEXT("JSON data is invalid! Input:\n'%s'"), *dataString);
		return false;
	}
	return true;
}

FString UDZJSonDataSeal::ToString()
{
	FString outStr;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&outStr);

	// Start writing the response
	WriteObject(JsonWriter, "", new FJsonValueObject(mData));
	JsonWriter->Close();

	return outStr;
}

void UDZJSonDataSeal::WriteObject(TSharedRef<TJsonWriter<TCHAR>> writer, FString key, FJsonValue* value)
{
	if (value->Type == EJson::Null)
	{
		// Write simple entry, don't a key when it isn't set
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
		// Write simple string entry, don't a key when it isn't set
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
		// Write simple entry, don't a key when it isn't set
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
		// Write simple entry, don't a key when it isn't set
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
		// Write object entry
		if (key.Len() > 0)
		{
			writer->WriteObjectStart(key);
		}
		else
		{
			writer->WriteObjectStart();
		}

		// Loop through all the values in the object data
		TSharedPtr<FJsonObject> objectData = value->AsObject();
		for (auto objectValue = objectData->Values.CreateIterator(); objectValue; ++objectValue)
		{
			// Using recursion to write the key and value to the writer
			WriteObject(writer, objectValue.Key(), objectValue.Value().Get());
		}

		writer->WriteObjectEnd();
	}
	else if (value->Type == EJson::Array)
	{
		// Process array entry
		writer->WriteArrayStart(key);

		TArray<TSharedPtr<FJsonValue>> objectArray = value->AsArray();
		for (int32 i = 0; i < objectArray.Num(); i++)
		{
			// Use recursion with an empty key to process all the values in the array
			WriteObject(writer, "", objectArray[i].Get());
		}

		writer->WriteArrayEnd();
	}
}
#undef LOCTEXT_NAMESPACE