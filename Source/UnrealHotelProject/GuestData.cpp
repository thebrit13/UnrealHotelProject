// Fill out your copyright notice in the Description page of Project Settings.


#include "GuestData.h"

GuestData::GuestData(int nights,FString ID,FString name): PersonData(ID,name)
{
	NightsLeft = nights;
}

GuestData::~GuestData()
{
}
