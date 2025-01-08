// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraCMS/LyraLogChannels.h"
#include "LyraCMS/System/LyraAssetManager.h"

ULyraAssetManager& ULyraAssetManager::Get()
{
	// TODO: 여기에 return 문을 삽입합니다.
	check(GEngine);

	if (ULyraAssetManager* Singleton = Cast<ULyraAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogCMS, Fatal, TEXT("invalid AssetManagerClassname in DefaultEngine.ini(project settings); it must be LyraAssetManager"));

	// 위의 Fatal로 인해 Crash가 나기 때문에 도달하지 않지만 컴파일을 위해 더미로 리턴
	return *NewObject<ULyraAssetManager>();
}

bool ULyraAssetManager::ShouldLogAssetLoads()
{
	// Command Line에 인자를 가지고와서 추가적으로 표현할 수 있는 방식
	const TCHAR* CommandLineContent = FCommandLine::Get();
	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

// 동기식으로 로딩을 한다.
// 동기식과 비동기식 로딩의 차이 
UObject* ULyraAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	// 해당 함수를 따로 만드는 이유는 'sychronous load asset이 불필요하게 하는 것이 없는지 확인하기 위함.'
	if (AssetPath.IsValid())
	{
		// FScopeLogTime을 확인해보좌
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads())
		{
			// 단순히 로깅하면서, 초 단위로 로깅 진행
			// 이 함수가 얼마나 걸렸는지 알 수 있음.
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("synchronous loaded assets [%s]"), *AssetPath.ToString(), nullptr, FScopeLogTime::ScopeLog_Seconds));
		}

		// 여기서 두 가지 분기
		// 1. AssetManager가 있으면, AssetManager의 StreambleManager를 통해 정적 로딩
		// 2. 아니면, FSoftObjectPath를 통해 바로 정적 로딩
		if (UAssetManager::IsValid())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}

		// if AssetManager is not ready, use LoadObject()
		// StaticLoadObject가 보인다 :
		// 참고로 항상 StaticLoadObject하기 전에 StaticFindObject를 통해 확인하고 실패하면 진짜 로딩함.
		// TryLoad는 very slow
		return AssetPath.TryLoad();
	}
	
	return nullptr;
}



