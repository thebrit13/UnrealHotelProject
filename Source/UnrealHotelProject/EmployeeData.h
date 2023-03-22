// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PersonData.h"
#include "PeopleManager.h"

/**
 * 
 */
class UNREALHOTELPROJECT_API EmployeeData : public PersonData
{
public:
	EmployeeData(FString ID,FString name,APeopleManager::EmployeeType et);
	~EmployeeData();

	APeopleManager::EmployeeType GetEmployeeType() { return _EmployeeType; };

private:
	APeopleManager::EmployeeType _EmployeeType;
};
