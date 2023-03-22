// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GuestData.h"
#include "TaskManager.h"
#include "Person.generated.h"

USTRUCT(BlueprintType)
struct FPersonDataPackage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString Name;
};

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

	UFUNCTION(BlueprintCallable)
	FPersonDataPackage GetPersonDataPackage();
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

	void Setup(PersonType personType,FString personID,FString name);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToLocation(FVector destination);

	FString GetID() { return _GuestData ? _GuestData->ID : _PersonData->ID; };

	int GetNightsLeft() { return _GuestData ? _GuestData->NightsLeft : 0; };

	void DecrementNightsLeft();

	class EmployeeData* GetEmployeeData() { return _EmployeeData; };

	TaskManager* GetTaskManager() { return _TaskManager; };

	void AddTask(TaskManager::TaskType tt, float taskTime, FVector destination, TFunction<void(bool)> callback);

	bool IsMoving;

private:
	TFunction<void(bool)> _CurrentCallback;
	GuestData* _GuestData = nullptr;
	class PersonData* _PersonData = nullptr;
	class EmployeeData* _EmployeeData = nullptr;

	class TaskManager* _TaskManager = nullptr;
};


