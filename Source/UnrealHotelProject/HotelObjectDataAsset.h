// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HotelObjectDataAsset.generated.h"

USTRUCT()
struct FHotelObject
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly)
		FString ItemID;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> ItemActor;
};

/**
 * 
 */
UCLASS()
class UNREALHOTELPROJECT_API UHotelObjectDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	TArray<FHotelObject> HotelRooms;

	UPROPERTY(EditDefaultsOnly)
	TArray<FHotelObject> HotelTiles;

	UPROPERTY(EditDefaultsOnly)
	TArray<FHotelObject> HotelMisc;
};
