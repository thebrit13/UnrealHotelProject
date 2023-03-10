// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DirectionalLight.h"
#include "CoreMinimal.h"

/**
 * 
 */
class UNITYHOTELPROJECT_API TimeManager
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

	float _TimeSeconds;
	float _DayTimeSeconds;
	float _NightTimeSeconds;
	float _ActualTime;

	int _DayCount = 0;

	ADirectionalLight* SunLight;

	void SetSunRotation();

	void UpdateActualTime(float time);
		
	AHotelManager* _HotelManagerRef;
};
