// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManager.h"

TaskManager::TaskManager(ARoomManager* roomManager)
{
	_RoomManager = roomManager;
}

TaskManager::~TaskManager()
{
}

void TaskManager::AddPerson(APerson* person)
{
	PersonTaskObject* taskObject = new PersonTaskObject();
	taskObject->Person = person;

	_PersonTaskList.Add(taskObject);
}

void TaskManager::Tick(float deltaTime)
{
	currentTime += deltaTime;
	if (currentTime >= TASK_UPDATE_TIME)
	{
		currentTime = 0;
		UpdateTasks();
	}
}

void TaskManager::UpdateTasks()
{
	for (int i = 0; i < _PersonTaskList.Num(); i++)
	{
		if (_PersonTaskList[i]->CurrentState == PersonState::IDLE)
		{
			//_PersonTaskList[i]->Person->MoveToLocation(_RoomManager->RoomList[0]->GetActorLocation());
			//_PersonTaskList[i]->CurrentState = PersonState::WALKING;
		}
	}
}
