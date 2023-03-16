// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManager.h"
#include "Person.h"

TaskManager::TaskManager(APerson* person)
{
	_Person = person;
}

TaskManager::~TaskManager()
{
	if(_CurrentTask)
		delete _CurrentTask;
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

void TaskManager::AddTask(TaskType tt, float taskTime,FVector destination, TFunction<void(bool)> callback)
{
	TaskObject* to = new TaskObject();
	to->TaskType = tt;
	to->Destination = destination;
	to->TotalTaskTime = taskTime;
	to->Callback = callback;

	_TaskQueue.Enqueue(to);
}

void TaskManager::UpdateTasks()
{
	if (_CurrentTask)
	{
		switch (_CurrentTask->TaskType)
		{
		case TaskType::GO_TO:
			if (!_Person->IsMoving)
			{
				if (_CurrentTask->Callback)
				{
					_CurrentTask->Callback(true);
				}
				delete _CurrentTask;
				_CurrentTask = nullptr;
			}
			break;
		case TaskType::CLEAN:
			if (_CurrentTask->TotalTaskTime != -1)
			{
				_CurrentTask->CurrentTaskTime += TASK_UPDATE_TIME;
				if (_CurrentTask->CurrentTaskTime >= _CurrentTask->TotalTaskTime)
				{
					if (_CurrentTask->Callback)
					{
						_CurrentTask->Callback(true);
					}
					delete _CurrentTask;
					_CurrentTask = nullptr;
				}
			}
			break;
		default:
			break;
		}
	}

	if (!_CurrentTask)
	{
		GetNextTask();
	}
}

void TaskManager::GetNextTask()
{
	if (!_TaskQueue.IsEmpty())
	{
		TaskObject* temp;
		if (_TaskQueue.Dequeue(temp))
		{
			_CurrentTask = temp;

			//For movement, start moving
			if (_CurrentTask->TaskType == TaskType::GO_TO)
			{
				_Person->MoveToLocation(_CurrentTask->Destination);
			}
		}
	}
	
}

