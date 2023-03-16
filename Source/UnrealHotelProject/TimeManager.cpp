// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"
#include "HotelManager.h"


TimeManager::TimeManager(ADirectionalLight* sunLight,AHotelManager* hotelManager)
{
	SunLight = sunLight;
	_DayTimeSeconds = DayTimeMinutes * 60.0f;
	_NightTimeSeconds = NightTimeMinutes * 60.0f;
	_HotelManagerRef = hotelManager;
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
		_DayCount++;
	}
	//UE_LOG(LogTemp, Warning, TEXT("CALLED %f"), _ActualTime);
	SetSunRotation();
}

FString TimeManager::GetTimeInStandardFormat()
{
	FString timeString;
	if (_TimeSeconds < _DayTimeSeconds)
	{
		float hour = FMath::Lerp(DayTimeStart, DayTimeStart+DayTimeHours, _TimeSeconds / _DayTimeSeconds);
		UpdateActualTime(hour);
		if (hour >= 13)
		{
			hour -= 12;
		}
		int minute = FMath::Lerp(0, 59,hour - (int)hour);
		timeString = FString::Printf(TEXT("Time: %d:%d"), (int)hour, minute);	
	}
	else
	{
		float hour = FMath::Lerp(DayTimeStart + DayTimeHours, DayTimeStart + DayTimeHours + NightTimeHours, (_TimeSeconds - _DayTimeSeconds) / _NightTimeSeconds);
		UpdateActualTime(hour);
		if (hour >= 13)
		{
			if (hour < 25)
			{
				hour -= 12;
			}
			else
			{
				hour -= 24;
			}
			
		}
		int minute = FMath::Lerp(0, 59, hour - (int)hour);
		timeString = FString::Printf(TEXT("Time: %d:%d"), (int)hour, minute);
	}
	return timeString;
}

float TimeManager::GetActualTime()
{
	return _ActualTime;
}

int TimeManager::GetDay()
{
	return _DayCount;
}

//void TimeManager::RegisterEventAtTime(TFunction<void> func, int hour, int minute)
//{
//}

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

void TimeManager::UpdateActualTime(float time)
{
	if (time >= 24)
	{
		time -= 24;
	}

	_ActualTime = time;
}
