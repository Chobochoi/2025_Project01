// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LyraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LYRACMS_API ULyraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public :
	ULyraAssetManager();

	static ULyraAssetManager& Get();

	static bool ShouldLogAssetLoads();

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	/*
	*  GetAsset은 정적 로딩으로 BP Class와 Object 로딩
	*  - 주목해야 할 부분은 bKeepInMemory
	*/
	template <typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftClassPtr<AssetType>& AssetPoninter, bool bKeepInMemory = true);

	// [THREAD-SAFE] 메모리에 로딩된 에셋 캐싱
	void AddLoadedAsset(const UObject* Asset);
	
	// GC의 대상
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	// Object 단위 Locking
	FCriticalSection SyncObject;

};

template<typename AssetType>
inline AssetType* ULyraAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	return nullptr;
}
