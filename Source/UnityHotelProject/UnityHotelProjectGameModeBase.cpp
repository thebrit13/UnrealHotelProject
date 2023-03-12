// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnityHotelProjectGameModeBase.h"
#include "UnityHotelProject.h"


UUserWidget* AUnityHotelProjectGameModeBase::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (CurrentWidget != nullptr && !CurrentWidget->IsA(MainHUD))
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    if (NewWidgetClass != nullptr)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        if (CurrentWidget != nullptr)
        {
            CurrentWidget->AddToViewport();
        }
    }
    return CurrentWidget;
}

void AUnityHotelProjectGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    //ChangeMenuWidget(RoomUI);
}
