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
	TimeManager(ADirectionalLight* sunLight);
	~TimeManager();

	void Tick(float deltaTime);
private:
	const float DayTimeMinutes = 1.0f;
	const float NightTimeMinutes = .5f;
	const float MinDay = 180;
	const float MaxDay = 360;
	const float MinNight = 0;
	const float MaxNight = 180;

	float _TimeSeconds;
	float _DayTimeSeconds;
	float _NightTimeSeconds;

	ADirectionalLight* SunLight;

	void SetSunRotation();
};
