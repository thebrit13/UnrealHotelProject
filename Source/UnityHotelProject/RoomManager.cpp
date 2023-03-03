// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomManager.h"
#include "HotelManager.h"

// Sets default values
ARoomManager::ARoomManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	for (ARoomActor* actor : RoomList)
	{
		//Add to info list
		RoomInfo* roomInfo = new RoomInfo();
		roomInfo->ID = actor->roomID;
		roomInfo->RoomRef = actor;
		roomInfo->RoomStatus = ARoomManager::RoomStatus::READY;

		//Assign reference
		actor->RoomManager = this;

		RoomInfoList.Add(roomInfo);
	}

}

// Called when the game starts or when spawned
void ARoomManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoomManager::RoomClicked(FString ID)
{
	
}



