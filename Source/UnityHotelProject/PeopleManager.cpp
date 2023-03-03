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

	_CurrentTick += DeltaTime;
	if (_CurrentTick >= _NextCreationTime)
	{
		CreatePerson();
		_CurrentTick = 0;
	}
}

void APeopleManager::CreatePerson()
{
	APerson* createdPerson = GetWorld()->SpawnActor<APerson>(Person1Character, SpawnPoint->GetComponentLocation(), FRotator(0,180,0));
	createdPerson->GuestID = FString::FromInt(GuestList.Num() + 1);

	GuestList.Add(createdPerson);
	GuestWaiting.Enqueue(createdPerson);

	_NextCreationTime = FMath::RandRange(MIN_NEXT_PERSON_TIME, MAX_NEXT_PERSON_TIME);
}

