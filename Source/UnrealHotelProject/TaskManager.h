// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Person.h"
#include "RoomManager.h"
#include "CoreMinimal.h"

/**
 * 
 */
class UNREALHOTELPROJECT_API TaskManager
{
public:
	TaskManager(ARoomManager* roomManager);
	~TaskManager();

	enum PersonState
	{
		IDLE,
		WALKING
	};

	void AddPerson(APerson* person);

	void Tick(float deltaTime);

private:
	TArray<struct PersonTaskObject*> _PersonTaskList;

	float currentTime = 0;
	const float TASK_UPDATE_TIME = .5f;

	void UpdateTasks();

	UPROPERTY()
	ARoomManager* _RoomManager;


};

struct PersonTaskObject
{
	UPROPERTY()
	APerson* Person;

	TaskManager::PersonState CurrentState;
};
