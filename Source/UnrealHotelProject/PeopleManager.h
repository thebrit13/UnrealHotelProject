// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Person.h"
#include "PeopleManager.generated.h"

class AHotelManager;

UCLASS()
class UNREALHOTELPROJECT_API APeopleManager : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere)
	//class UStaticMeshComponent* Floor_Entrance;

	//UPROPERTY(VisibleAnywhere)
	//class UStaticMeshComponent* Floor_Exit;

	//UPROPERTY(VisibleAnywhere)
	//class UStaticMeshComponent* Employee_Entrance;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* EntrancePoint;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* ExitPoint;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* EmployeePoint;

public:
	// Sets default values for this actor's properties
	APeopleManager();

	enum EmployeeType
	{
		HOUSEKEEP
	};

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APerson> Person1Character;

	bool GetWaitingPerson(APerson*& person);

	APerson* GetAvailableHousekeeper();

	bool RemoveGuest(FString guestID);

	FVector GetEntrance();
	FVector GetExit();

	void ReturnHousekeeper(APerson* person);

	FVector GetEmployeePoint() { return EmployeePoint->GetComponentLocation(); };

	AHotelManager* HotelManager;

	int GetWaitingGuestCount() { return _GuestWaitingCount; };

	void SetPoints(FVector entrance, FVector exit, FVector employee);

	void StartLogic();

private:
	APerson* CreatePerson(FVector loc, APerson::PersonType pt);
	void CreateGuest();
	void CreateEmployee(EmployeeType et);
	void ReadInNames();
	FString GetRandomName();

	TArray<APerson*> GuestList;

	TArray<APerson*> AllCreatedPeople;

	TArray<APerson*> EmployeeList;

	TQueue<APerson*> GuestWaiting;

	int _GuestWaitingCount;

	const float MIN_NEXT_PERSON_TIME = 2.0f;
	const float MAX_NEXT_PERSON_TIME = 5.0f;
	float _NextCreationTime = 0;
	float _CurrentTick = 0;	
	TArray<FString> FirstNames;
};
