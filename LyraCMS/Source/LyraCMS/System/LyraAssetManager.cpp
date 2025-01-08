// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraCMS/LyraLogChannels.h"
#include "LyraCMS/System/LyraAssetManager.h"

ULyraAssetManager& ULyraAssetManager::Get()
{
	// TODO: ���⿡ return ���� �����մϴ�.
	check(GEngine);

	if (ULyraAssetManager* Singleton = Cast<ULyraAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogCMS, Fatal, TEXT("invalid AssetManagerClassname in DefaultEngine.ini(project settings); it must be LyraAssetManager"));

	// ���� Fatal�� ���� Crash�� ���� ������ �������� ������ �������� ���� ���̷� ����
	return *NewObject<ULyraAssetManager>();
}

bool ULyraAssetManager::ShouldLogAssetLoads()
{
	// Command Line�� ���ڸ� ������ͼ� �߰������� ǥ���� �� �ִ� ���
	const TCHAR* CommandLineContent = FCommandLine::Get();
	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

// ��������� �ε��� �Ѵ�.
// ����İ� �񵿱�� �ε��� ���� 
UObject* ULyraAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	// �ش� �Լ��� ���� ����� ������ 'sychronous load asset�� ���ʿ��ϰ� �ϴ� ���� ������ Ȯ���ϱ� ����.'
	if (AssetPath.IsValid())
	{
		// FScopeLogTime�� Ȯ���غ���
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads())
		{
			// �ܼ��� �α��ϸ鼭, �� ������ �α� ����
			// �� �Լ��� �󸶳� �ɷȴ��� �� �� ����.
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("synchronous loaded assets [%s]"), *AssetPath.ToString(), nullptr, FScopeLogTime::ScopeLog_Seconds));
		}

		// ���⼭ �� ���� �б�
		// 1. AssetManager�� ������, AssetManager�� StreambleManager�� ���� ���� �ε�
		// 2. �ƴϸ�, FSoftObjectPath�� ���� �ٷ� ���� �ε�
		if (UAssetManager::IsValid())
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}

		// if AssetManager is not ready, use LoadObject()
		// StaticLoadObject�� ���δ� :
		// ����� �׻� StaticLoadObject�ϱ� ���� StaticFindObject�� ���� Ȯ���ϰ� �����ϸ� ��¥ �ε���.
		// TryLoad�� very slow
		return AssetPath.TryLoad();
	}
	
	return nullptr;
}



