// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PersonData.h"

/**
 * 
 */
class UNITYHOTELPROJECT_API GuestData: public PersonData
{
public:
	GuestData(int nights, FString ID);
	~GuestData();
	
	int NightsLeft;
};
