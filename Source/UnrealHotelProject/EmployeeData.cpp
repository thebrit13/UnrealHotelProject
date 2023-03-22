// Fill out your copyright notice in the Description page of Project Settings.


#include "EmployeeData.h"

EmployeeData::EmployeeData(FString ID,FString name,APeopleManager::EmployeeType et):PersonData(ID,name)
{
	_EmployeeType = et;
}

EmployeeData::~EmployeeData()
{
}
