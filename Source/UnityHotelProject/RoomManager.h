// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.h"
#include "Person.h"
#include "RoomManager.generated.h"

UCLASS()
class UNITYHOTELPROJECT_API ARoomManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomManager();

	enum RoomStatus
	{
		READY,
		DIRTY,
		OCCUPIED
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<ARoomActor*> RoomList;

	TArray<struct RoomInfo*> RoomInfoList;

	//Mostly for testing
	void RoomClicked(FString ID);
};


struct RoomInfo
{
	FString ID;
	UPROPERTY()
	ARoomActor* RoomRef;
	UPROPERTY()
	APerson* PersonRef;
	ARoomManager::RoomStatus RoomStatus;
};
