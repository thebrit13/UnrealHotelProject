// Fill out your copyright notice in the Description page of Project Settings.


#include "HotelManager.h"

// Sets default values
AHotelManager::AHotelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AHotelManager::BeginPlay()
{
	Super::BeginPlay();
	RoomManger->HotelManager = HotelManagerBP;
	_TimeManager = new TimeManager(SunLight, HotelManagerBP);
}

// Called every frame
void AHotelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_TimeManager)
	{
		_TimeManager->Tick(DeltaTime);
	}
}

FString AHotelManager::GetTimeString()
{
	if (_TimeManager)
	{
		return _TimeManager->GetTimeInStandardFormat();
	}
	return FString("Error");
}

void AHotelManager::AssignGuestToRoom(RoomInfo* ri)
{
	if (ri)
	{
		APerson* person;
		PeopleManger->GetWaitingPerson(person);
		if (person)
		{
			ri->PersonRef = person;
			ri->RoomStatus = ARoomManager::RoomStatus::OCCUPIED;

			person->MoveToLocation(ri->RoomRef->GetActorLocation());
		}
	}
}

void AHotelManager::CheckOutTime()
{
}

