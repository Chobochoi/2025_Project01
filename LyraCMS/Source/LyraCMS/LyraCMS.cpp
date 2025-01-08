// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraCMS.h"
#include "Modules/ModuleManager.h"
// UE_LOG���� LogTemp��� �ϴ� �κ��� LyraLogChannels�� ����� LogCMS�� �������־���.
#include "LyraLogChannels.h"

class FLyraCMSModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;	
	virtual void ShutdownModule() override;
};

// Module�� �⺻������ �ϳ��� �־�� �Ѵ�.
IMPLEMENT_PRIMARY_GAME_MODULE(FLyraCMSModule, LyraCMS, "LyraCMS" );

void FLyraCMSModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	
	// LyraLogChannels�� ����� �� ����ϴ� LogTemp
	//UE_LOG(LogTemp, Warning, TEXT("CMS_ModuleTest"));
	
	UE_LOG(LogCMS, Warning, TEXT("CMS_ModuleTest"));
}

void FLyraCMSModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}
