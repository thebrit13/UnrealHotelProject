// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"

TimeManager::TimeManager(ADirectionalLight* sunLight)
{
	SunLight = sunLight;
	_DayTimeSeconds = DayTimeMinutes * 60.0f;
	_NightTimeSeconds = NightTimeMinutes * 60.0f;
}

TimeManager::~TimeManager()
{
}

void TimeManager::Tick(float deltaTime)
{
	
	_TimeSeconds += deltaTime;
	if (_TimeSeconds >= _DayTimeSeconds + _NightTimeSeconds)
	{
		_TimeSeconds = 0;
	}
	//UE_LOG(LogTemp, Warning, TEXT("CALLED %f %f %f"),_TimeSeconds,_DayTimeSeconds,_NightTimeSeconds);
	SetSunRotation();
}

void TimeManager::SetSunRotation()
{
	if (!SunLight)
	{
		return;
	}

	FRotator sunRot = SunLight->GetActorRotation();
	if (_TimeSeconds < _DayTimeSeconds)
	{
		sunRot.Pitch = FMath::Lerp(MinDay, MaxDay, _TimeSeconds / _DayTimeSeconds);
	}
	else
	{
		sunRot.Pitch = FMath::Lerp(MinNight, MaxNight, _TimeSeconds / (_DayTimeSeconds + _NightTimeSeconds));
	}

	sunRot.Roll = 0;
	sunRot.Yaw = 250;

	SunLight->SetActorRotation(sunRot);
}
