// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraCMS.h"
#include "Modules/ModuleManager.h"
// UE_LOG에서 LogTemp라고 하던 부분을 LyraLogChannels를 만들고 LogCMS로 변경해주었다.
#include "LyraLogChannels.h"

class FLyraCMSModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;	
	virtual void ShutdownModule() override;
};

// Module은 기본적으로 하나는 있어야 한다.
IMPLEMENT_PRIMARY_GAME_MODULE(FLyraCMSModule, LyraCMS, "LyraCMS" );

void FLyraCMSModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	
	// LyraLogChannels를 만들기 전 사용하던 LogTemp
	//UE_LOG(LogTemp, Warning, TEXT("CMS_ModuleTest"));
	
	UE_LOG(LogCMS, Warning, TEXT("CMS_ModuleTest"));
}

void FLyraCMSModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}
