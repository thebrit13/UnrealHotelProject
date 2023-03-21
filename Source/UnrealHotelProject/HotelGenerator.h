// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HotelDataAsset.h"
#include "HotelObjectDataAsset.h"
#include "PeopleManager.h"
#include "HotelManager.h"
#include "RoomManager.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "HotelGenerator.generated.h"

UCLASS()
class UNREALHOTELPROJECT_API AHotelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHotelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UHotelDataAsset* HotelDataAsset;

	UPROPERTY(EditDefaultsOnly)
	UHotelObjectDataAsset* HotelObjectDataAsset;

	UPROPERTY(EditInstanceOnly)
	APeopleManager* PeopleManager;

	UPROPERTY(EditInstanceOnly)
	AHotelManager* HotelManager;

	UPROPERTY(EditInstanceOnly)
	ARoomManager* RoomManager;

	UPROPERTY(EditInstanceOnly)
	AVolume* NavMesh;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void GenerateHotel();

	TSubclassOf<AActor> GetActorForID(FString id,TArray<FHotelObject> activeArray);

	TArray<TArray<AActor*>*> CreatedHotelActors;
};
