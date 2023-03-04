// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomManager.h"
#include "PeopleManager.h"
#include "HotelManager.generated.h"

UCLASS()
class UNITYHOTELPROJECT_API AHotelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHotelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly)
	AHotelManager* HotelManagerBP;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly)
	ARoomManager* RoomManger;	
	
	UPROPERTY(EditInstanceOnly)
	APeopleManager* PeopleManger;

	//void AssignGuestToRoom(FString roomID);

};
