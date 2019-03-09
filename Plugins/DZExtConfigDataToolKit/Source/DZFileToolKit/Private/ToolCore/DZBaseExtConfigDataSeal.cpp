#include "DZBaseExtConfigDataSeal.h"
#include "Engine/Engine.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"


#define LOCTEXT_NAMESPACE "BaseExtConfigDataSeal"
UDZBaseExtConfigDataSeal::UDZBaseExtConfigDataSeal(const FObjectInitializer& objs)
	:Super(objs)
{

}

bool UDZBaseExtConfigDataSeal::SetupLocFile(const FString path, EDZFolder dirctionType)
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
		UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("Can't load json data from %s"), *FullJsonPath);
		return false;
	}
	return SetupSourceData(Result);
}

bool UDZBaseExtConfigDataSeal::SetupSourceData(const FString dataString)
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple:\n'%s'"), *dataString);
	return false;
}

FString UDZBaseExtConfigDataSeal::ToString()
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	FString outStr;
	return outStr;
}

FString UDZBaseExtConfigDataSeal::GetString(const FString & key, bool & success) const
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return FString("none");
}

bool UDZBaseExtConfigDataSeal::GetBool(const FString & key, bool & success) const
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return false;
}

int32 UDZBaseExtConfigDataSeal::GetInt(const FString & key, bool & success) const
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return 0;
}

float UDZBaseExtConfigDataSeal::GetFloat(const FString & key, bool & success) const
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return 0.0f;
}

bool UDZBaseExtConfigDataSeal::GetIsNull(const FString & key, bool & fieldExists) const
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return false;
}

TArray<FString> UDZBaseExtConfigDataSeal::GetStringArray(const FString & key, bool & success)
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return TArray<FString>();
}

TArray<bool> UDZBaseExtConfigDataSeal::GetBoolArray(const FString & key, bool & success)
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return TArray<bool>();
}

TArray<int32> UDZBaseExtConfigDataSeal::GetIntArray(const FString & key, bool & success)
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return TArray<int32>();
}

TArray<float> UDZBaseExtConfigDataSeal::GetFloatArray(const FString & key, bool & success)
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return TArray<float>();
}

UDZBaseExtConfigDataSeal * UDZBaseExtConfigDataSeal::GetObject(const FString & key, bool & success)
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return nullptr;
}

TArray<UDZBaseExtConfigDataSeal*> UDZBaseExtConfigDataSeal::GetObjectArray(const FString & key, bool & success)
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return TArray<UDZBaseExtConfigDataSeal*>();
}

TArray<FString> UDZBaseExtConfigDataSeal::GetObjectKeys()
{
	UE_LOG(BaseExtConfigDataSeleLog, Error, TEXT("should Imple"));
	return TArray<FString>();
}
#undef LOCTEXT_NAMESPACE