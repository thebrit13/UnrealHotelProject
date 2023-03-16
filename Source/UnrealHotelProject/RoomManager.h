// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.h"
#include "Person.h"
#include "RoomManager.generated.h"

class AHotelManager;

UCLASS()
class UNREALHOTELPROJECT_API ARoomManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomManager();

	enum RoomStatus
	{
		READY,
		DIRTY,
		OCCUPIED
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void RoomClickedBP(bool empty,bool dirty);

	UPROPERTY(EditInstanceOnly)
	ARoomManager* ARoomManagerBP;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<ARoomActor*> RoomList;

	UFUNCTION(BlueprintCallable)
	void AssignRoomClickedBP();

	UFUNCTION(BlueprintCallable)
	void CleanRoomClickedBP();

	TArray<APerson*> GetGuestInRooms();

	bool CheckOutGuest(FString guestID);

	void RoomClicked(FString roomID);

	int GetEmptyRoomCount();

	AHotelManager* HotelManager;

private:
	struct RoomInfo* LastRoomClicked;
	TArray<RoomInfo*> RoomInfoList;
};

struct RoomInfo
{
	FString ID;
	UPROPERTY()
	ARoomActor* RoomRef;
	UPROPERTY()
	APerson* PersonRef;
	ARoomManager::RoomStatus RoomStatus;
};
