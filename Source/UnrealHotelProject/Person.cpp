// Fill out your copyright notice in the Description page of Project Settings.

#include "Person.h"
#include "PersonData.h"
#include "EmployeeData.h"
#include "TaskManager.h"

// Sets default values
APerson::APerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

APerson::~APerson()
{
	delete _PersonData;
	delete _GuestData;
	delete _EmployeeData;
	delete _TaskManager;
}

// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	Super::BeginPlay();

	_TaskManager = new TaskManager(this);
}

void APerson::MoveToLocationComplete(bool success)
{
	if (_CurrentCallback)
	{
		_CurrentCallback(success);
		_CurrentCallback = nullptr;
	}
}

// Called every frame
void APerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_TaskManager)
	{
		_TaskManager->Tick(DeltaTime);
	}
}

void APerson::Setup(PersonType personType,FString personID)
{
	switch (personType)
	{
		case APerson::GUEST:
			_GuestData = new GuestData(FMath::RandRange(1,3), personID);
			break;
		case APerson::EMPLOYEE:
			_EmployeeData = new EmployeeData(personID,APeopleManager::EmployeeType::HOUSEKEEP);
			break;
		case APerson::OTHER:
			_PersonData = new PersonData(personID);
			break;
		default:
			_PersonData = new PersonData(personID);
			break;
	}
}

// Called to bind functionality to input
void APerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APerson::MoveToLocation(FVector loc, TFunction<void(bool)> callback)
{
	_CurrentCallback = callback;
	MoveToLocationBP(loc);
}

void APerson::DecrementNightsLeft()
{
	_GuestData->NightsLeft--;
}



