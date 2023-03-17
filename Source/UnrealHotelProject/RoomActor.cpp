// Fill out your copyright notice in the Description page of Project Settings.



#include "RoomActor.h"
#include "RoomManager.h"

// Sets default values
ARoomActor::ARoomActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RoomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh"));
	SetRootComponent(RoomMesh);

	StatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusWidget"));
	StatusWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ARoomActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoomActor::OnRoomClicked()
{
	RoomManager->RoomClicked(roomID);
}

// Called every frame
void ARoomActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

