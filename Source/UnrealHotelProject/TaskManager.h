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

	void AddTask(TaskType tt,float taskTime);
	void AddTask(TaskType tt, TFunction<void(bool)> callback);
	void AddTask(TaskType tt,float taskTime, TFunction<void(bool)> callback);

private:
	APerson* _Person;

	const float TASK_UPDATE_TIME = .25f;

	float _CurrentCount;

	void UpdateTasks();

	TQueue<struct TaskObject*> TaskQueue;

};

struct TaskObject
{
	TaskManager::TaskType TaskType;
};

