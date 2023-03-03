// Fill out your copyright notice in the Description page of Project Settings.


#include "HotelManager.h"
#include "RoomActor.h"
#include "PeopleManager.h"

// Sets default values
AHotelManager::AHotelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TaskManagerRef = new TaskManager(RoomManager);
}

// Called when the game starts or when spawned
void AHotelManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHotelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TaskManagerRef)
	{
		if (TaskManagerRef)
		{
			TaskManagerRef->Tick(DeltaTime);
		}
	}

}

void AHotelManager::AssignGuestToRoom(FString roomID)
{
	//General idea
	//Check guest list
	//Check room status
	//Assigned to room
}

