// Fill out your copyright notice in the Description page of Project Settings.


#include "GuestData.h"

GuestData::GuestData(int nights,FString ID): PersonData(ID)
{
	NightsLeft = nights;
}

GuestData::~GuestData()
{
}
