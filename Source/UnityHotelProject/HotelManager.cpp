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
	
}

// Called every frame
void AHotelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AHotelManager::AssignGuestToRoom(FString roomID)
//{
//
//}

