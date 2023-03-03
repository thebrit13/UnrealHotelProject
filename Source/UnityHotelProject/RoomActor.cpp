// Fill out your copyright notice in the Description page of Project Settings.



#include "RoomActor.h"
#include "RoomManager.h"

// Sets default values
ARoomActor::ARoomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoomActor::OnRoomClicked(FString ID)
{
	RoomManager->RoomClicked(ID);
}

// Called every frame
void ARoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

