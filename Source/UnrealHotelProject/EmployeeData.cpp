// Fill out your copyright notice in the Description page of Project Settings.


#include "EmployeeData.h"

EmployeeData::EmployeeData(FString ID,APeopleManager::EmployeeType et):PersonData(ID)
{
	_EmployeeType = et;
}

EmployeeData::~EmployeeData()
{
}
