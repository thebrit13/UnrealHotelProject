// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"

// Sets default values
APerson::APerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APerson::BeginPlay()
{
	Super::BeginPlay();
	
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


