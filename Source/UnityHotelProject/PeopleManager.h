// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "TaskManager.h"
#include "Person.h"
#include "PeopleManager.generated.h"

UCLASS()
class UNITYHOTELPROJECT_API APeopleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APeopleManager();

	TaskManager* taskManager;

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

private:
	void CreatePerson();
};
