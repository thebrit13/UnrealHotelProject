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
	EmployeeData(FString ID,APeopleManager::EmployeeType et);
	~EmployeeData();

private:
	APeopleManager::EmployeeType _EmployeeType;
};
