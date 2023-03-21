// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HotelDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UNREALHOTELPROJECT_API UHotelDataAsset : public UDataAsset
{
	GENERATED_BODY()

public :
	UPROPERTY(EditDefaultsOnly)
	int TileSize = 200;

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> HotelDataArray;

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> HotelDataRotationArray;
};
