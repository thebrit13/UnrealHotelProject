// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomManager.h"
#include "HotelManager.h"

// Sets default values
ARoomManager::ARoomManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void ARoomManager::BeginPlay()
{
	Super::BeginPlay();
	for (ARoomActor* actor : RoomList)
	{
		//Add to info list
		RoomInfo* roomInfo = new RoomInfo();
		roomInfo->ID = actor->roomID;
		roomInfo->RoomRef = actor;
		roomInfo->RoomStatus = ARoomManager::RoomStatus::READY;

		//Assign reference
		actor->RoomManager = ARoomManagerBP;

		RoomInfoList.Add(roomInfo);
	}
}

// Called every frame
void ARoomManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoomManager::AssignRoomClickedBP()
{
	UE_LOG(LogTemp, Warning, TEXT("ASSIGN"));
	HotelManager->AssignGuestToRoom(LastRoomClicked);
}

void ARoomManager::CleanRoomClickedBP()
{
	UE_LOG(LogTemp, Warning, TEXT("CLEAN"));
	HotelManager->AssignHousekeeperToRoom(LastRoomClicked);
}

TArray<APerson*> ARoomManager::GetGuestInRooms()
{
	TArray<APerson*> personList;
	for (RoomInfo* ri : RoomInfoList)
	{
		if (ri->PersonRef)
		{
			personList.Add(ri->PersonRef);
		}
	}
	return personList;
}

bool ARoomManager::CheckOutGuest(FString guestID)
{
	for (RoomInfo* ri : RoomInfoList)
	{
		if (ri->PersonRef && ri->PersonRef->GetID() == guestID)
		{
			ri->PersonRef = nullptr;
			ri->RoomStatus = RoomStatus::DIRTY;
			return true;
		}
	}
	return false;
}

void ARoomManager::RoomClicked(FString roomID)
{
	for (RoomInfo* ri : this->RoomInfoList)
	{
		if (ri->ID == roomID)
		{
			RoomClickedBP(ri->RoomStatus == RoomStatus::READY,ri->RoomStatus == RoomStatus::DIRTY);
			LastRoomClicked = ri;
		}
	}
}




