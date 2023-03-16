// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"

/**
 * 
 */
class UNREALHOTELPROJECT_API TaskManager
{
public:
	enum TaskType
	{
		GO_TO,
		CLEAN
	};

	TaskManager(class APerson* person);
	~TaskManager();

	void Tick(float deltaTime);

	void AddTask(TaskType tt,float taskTime,FVector destination, TFunction<void(bool)> callback);

private:
	UPROPERTY()
	APerson* _Person;

	const float TASK_UPDATE_TIME = .25f;

	float _CurrentCount = 0;

	void UpdateTasks();

	void GetNextTask();

	TQueue<struct TaskObject*> _TaskQueue;
	TaskObject* _CurrentTask = nullptr;

};

struct TaskObject
{
	TaskManager::TaskType TaskType;
	TFunction<void(bool)> Callback;
	float TotalTaskTime = -1;
	float CurrentTaskTime = 0.0f;
	FVector Destination;
};

