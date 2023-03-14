// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREALHOTELPROJECT_API PersonData
{
public:
	PersonData(FString ID);
	~PersonData();

	FString ID;
	FString Name;
};
