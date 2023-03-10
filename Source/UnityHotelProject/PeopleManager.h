// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Person.h"
#include "PeopleManager.generated.h"

UCLASS()
class UNITYHOTELPROJECT_API APeopleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APeopleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Floor;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SpawnPoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APerson> Person1Character;

	APerson* GetWaitingPerson(APerson*& person);

	bool RemoveGuest(FString guestID);

private:
	void CreatePerson();

	TArray<APerson*> GuestList;

	TQueue<APerson*> GuestWaiting;

	const float MIN_NEXT_PERSON_TIME = 50.0f;
	const float MAX_NEXT_PERSON_TIME = 200.0f;
	float _NextCreationTime;
	float _CurrentTick;
};
