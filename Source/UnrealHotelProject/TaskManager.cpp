// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManager.h"
#include "Person.h"

TaskManager::TaskManager(APerson* person)
{
	_Person = person;
}

TaskManager::~TaskManager()
{
}

void TaskManager::Tick(float deltaTime)
{
	_CurrentCount += deltaTime;
	if (_CurrentCount >= TASK_UPDATE_TIME)
	{
		_CurrentCount = 0;
		UpdateTasks();
	}
}

void TaskManager::AddTask(TaskType tt,float taskTime)
{

}

void TaskManager::AddTask(TaskType tt, TFunction<void(bool)> callback)
{
}

void TaskManager::AddTask(TaskType tt, float taskTime, TFunction<void(bool)> callback)
{
}

void TaskManager::UpdateTasks()
{
}

