// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManager.h"

TaskManager::TaskManager()
{
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

	}
}
