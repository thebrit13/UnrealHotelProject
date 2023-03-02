// Fill out your copyright notice in the Description page of Project Settings.


#include "PeopleManager.h"


// Sets default values
APeopleManager::APeopleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	SetRootComponent(Floor);
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	taskManager = new TaskManager();
}

// Called when the game starts or when spawned
void APeopleManager::BeginPlay()
{
	Super::BeginPlay();

	CreatePerson();
	
}

// Called every frame
void APeopleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (taskManager)
	{
		taskManager->Tick(DeltaTime);
	}
}

void APeopleManager::CreatePerson()
{
	APerson* createdPerson = GetWorld()->SpawnActor<APerson>(Person1Character, SpawnPoint->GetComponentLocation(), FRotator(0,180,0));
	taskManager->AddPerson(createdPerson);
}

