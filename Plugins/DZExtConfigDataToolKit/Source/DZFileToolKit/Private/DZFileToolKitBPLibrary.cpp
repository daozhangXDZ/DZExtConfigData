// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DZFileToolKitBPLibrary.h"
#include "DZFileToolKit.h"
#include "ToolCore/DZJSonDataSeal.h"

UDZFileToolKitBPLibrary::UDZFileToolKitBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UDZBaseExtConfigDataSeal * UDZFileToolKitBPLibrary::SpawnOneExtData(const FString pPath, EDZFolder pFolderType,EDZFileType FileType, bool& isSuccess)
{
	UDZBaseExtConfigDataSeal* pObjDataSeal = NewObject <UDZBaseExtConfigDataSeal>();
	isSuccess = false;
	switch (FileType)
	{
		case EDZFileType::JSON :
			pObjDataSeal = NewObject<UDZJSonDataSeal>();
		break;

		case EDZFileType::XML:
			pObjDataSeal = NewObject<UDZJSonDataSeal>();
			break;
	} 
	if (pObjDataSeal == nullptr)
	{
		return nullptr;
	}
	pObjDataSeal->AddToRoot();
	if (pObjDataSeal->SetupLocFile(pPath, pFolderType))
	{
		isSuccess = true;
	}
	return pObjDataSeal;
}
