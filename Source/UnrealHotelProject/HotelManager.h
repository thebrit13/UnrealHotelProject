// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomManager.h"
#include "PeopleManager.h"
#include "Engine/DirectionalLight.h"
#include "TimeManager.h"
#include "FinanceManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "HotelManager.generated.h"

UCLASS()
class UNREALHOTELPROJECT_API AHotelManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AHotelManager();
	~AHotelManager();
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditInstanceOnly)
	ADirectionalLight* SunLight;

	UFUNCTION(BlueprintCallable)
	FString GetTimeString();	
	
	UFUNCTION(BlueprintCallable)
	FString GetMoneyString();

	//UFUNCTION(BlueprintImplementableEvent)
	//void DestroyActorBP(const AActor* actor);

	void AssignGuestToRoom(RoomInfo* ri);

	void AssignHousekeeperToRoom(RoomInfo* ri);
	
	void CheckOutGuests();

	void FinancialTransactionHelper(FinanceManager::TransactionType tt, bool add);

	bool ShouldSpawnGuest();

	void StartLogic();

	FVector GetCheckInLocation() { return GuestStandLocation->GetComponentLocation(); };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly)
	ARoomManager* RoomManger;

	UPROPERTY(EditInstanceOnly)
	APeopleManager* PeopleManger;

	//UPROPERTY(EditInstanceOnly)
	//AHotelManager* HotelManagerBP;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CheckInDesk;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* GuestStandLocation;


private:
	const int CHECKOUT_TIME = 11;
	const int CHECKIN_TIME = 15;

	int _LastCheckoutDay = -1;
	void HandleTimedEvents();

	TimeManager* _TimeManager;
	FinanceManager* _FinanceManager;
};
