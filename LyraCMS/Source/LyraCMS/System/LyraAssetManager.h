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
	*  GetAsset�� ���� �ε����� BP Class�� Object �ε�
	*  - �ָ��ؾ� �� �κ��� bKeepInMemory
	*/
	template <typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftClassPtr<AssetType>& AssetPoninter, bool bKeepInMemory = true);

	// [THREAD-SAFE] �޸𸮿� �ε��� ���� ĳ��
	void AddLoadedAsset(const UObject* Asset);
	
	// GC�� ���
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	// Object ���� Locking
	FCriticalSection SyncObject;

};

template<typename AssetType>
inline AssetType* ULyraAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	return nullptr;
}
