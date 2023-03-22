// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DirectionalLight.h"
#include "CoreMinimal.h"

/**
 * 
 */
class UNREALHOTELPROJECT_API TimeManager
{
public:
	TimeManager(ADirectionalLight* sunLight,class AHotelManager* hotelManager);
	~TimeManager();

	void Tick(float deltaTime);

	FString GetTimeInStandardFormat();

	float GetActualTime();
	int GetDay();

	//void RegisterEventAtTime(TFunction<void> func, int hour, int minute);
private:
	const float DayTimeMinutes = .5f;
	const float NightTimeMinutes = .25f;
	const float DayTimeStart = 6;
	const float DayTimeHours = 14;
	const float NightTimeHours = 10;
	const float MinDay = 180;
	const float MaxDay = 360;
	const float MinNight = 0;
	const float MaxNight = 180;

	float _TimeSeconds = 0.0f;
	float _DayTimeSeconds = 0.0f;
	float _NightTimeSeconds = 0.0f;
	float _ActualTime = 0.0f;

	int _DayCount = 0;

	ADirectionalLight* SunLight = nullptr;

	void SetSunRotation();

	void UpdateActualTime(float time);
		
	AHotelManager* _HotelManagerRef = nullptr;
};
