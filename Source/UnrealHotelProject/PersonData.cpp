// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonData.h"

PersonData::PersonData(FString id)
{
	ID = id;
	Name = FString::Printf(TEXT("Name %s"), *ID);
}

PersonData::~PersonData()
{
}
