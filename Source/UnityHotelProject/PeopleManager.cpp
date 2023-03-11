// Fill out your copyright notice in the Description page of Project Settings.


#include "PeopleManager.h"


// Sets default values
APeopleManager::APeopleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Floor_Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor_Entrance"));
	SetRootComponent(Floor_Entrance);
	EntrancePoint = CreateDefaultSubobject<USceneComponent>(TEXT("EntrancePoint"));
	EntrancePoint->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	Floor_Exit = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor_Exit"));
	Floor_Exit->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExitPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ExitPoint"));
	ExitPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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

bool APeopleManager::GetWaitingPerson(APerson* &person)
{
	return GuestWaiting.Dequeue(person);
}

bool APeopleManager::RemoveGuest(FString guestID)
{
	for (int i = 0; i < GuestList.Num(); i++)
	{
		if (GuestList[i]->GetID() == guestID)
		{
			GetWorld()->DestroyActor(GuestList[i]);
			GuestList.RemoveAt(i);
			return true;
		}
	}
	return false;
}

FVector APeopleManager::GetEntrance()
{
	return EntrancePoint->GetComponentLocation();
}

FVector APeopleManager::GetExit()
{
	return ExitPoint->GetComponentLocation();
}

void APeopleManager::CreatePerson()
{
	APerson* createdPerson = GetWorld()->SpawnActor<APerson>(Person1Character, EntrancePoint->GetComponentLocation(), FRotator(0,180,0));
	createdPerson->Setup(APerson::PersonType::GUEST, FString::FromInt(GuestList.Num() + 1));

	GuestList.Add(createdPerson);
	GuestWaiting.Enqueue(createdPerson);

	_NextCreationTime = FMath::RandRange(MIN_NEXT_PERSON_TIME, MAX_NEXT_PERSON_TIME);
}

