// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomActor.generated.h"

UCLASS()
class UNREALHOTELPROJECT_API ARoomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnRoomClicked();

public:	
	UPROPERTY(EditInstanceOnly,BlueprintReadOnly)
	FString roomID;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ARoomManager* RoomManager;


};
