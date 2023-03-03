// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Person.generated.h"

UCLASS()
class UNITYHOTELPROJECT_API APerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void MoveToLocationBP();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToLocation(FVector);

	FString GuestID;
};
