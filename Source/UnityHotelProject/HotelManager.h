// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomManager.h"
#include "PeopleManager.h"
#include "Engine/DirectionalLight.h"
#include "TimeManager.h"
#include "HotelManager.generated.h"

UCLASS()
class UNITYHOTELPROJECT_API AHotelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHotelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly)
	AHotelManager* HotelManagerBP;

	TimeManager* _TimeManager;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly)
	ARoomManager* RoomManger;	
	
	UPROPERTY(EditInstanceOnly)
	APeopleManager* PeopleManger;

	UPROPERTY(EditInstanceOnly)
	ADirectionalLight* SunLight;

	UFUNCTION(BlueprintCallable)
	FString GetTimeString();

	void AssignGuestToRoom(RoomInfo* ri);
	
	void CheckOutGuests();

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyActorBP(const AActor* actor);

private:
	const int CheckoutTime = 11;

	int _LastCheckoutDay = -1;
	void HandleTimedEvents();
};
