// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GuestData.h"
#include "Person.generated.h"

UCLASS()
class UNREALHOTELPROJECT_API APerson : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void MoveToLocationBP(const FVector &loc);

	UFUNCTION(BlueprintCallable)
	void MoveToLocationComplete(bool success);

public:	

	enum PersonType
	{
		GUEST,
		EMPLOYEE,
		OTHER
	};

	// Sets default values for this character's properties
	APerson();
	~APerson();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Setup(PersonType personType,FString personID);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToLocation(FVector, TFunction<void(bool)> callback);

	FString GetID() { return _GuestData ? _GuestData->ID : _PersonData->ID; };

	int GetNightsLeft() { return _GuestData ? _GuestData->NightsLeft : 0; };

	void DecrementNightsLeft();

	class EmployeeData* GetEmployeeData() { return _EmployeeData; };

	class TaskManager* GetTaskManager() { return _TaskManager; };

private:
	TFunction<void(bool)> _CurrentCallback;
	GuestData* _GuestData;
	class PersonData* _PersonData;
	class EmployeeData* _EmployeeData;

	class TaskManager* _TaskManager;


};
