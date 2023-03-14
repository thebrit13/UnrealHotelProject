// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealHotelProjectGameModeBase.h"
#include "UnrealHotelProject.h"


UUserWidget* AUnrealHotelProjectGameModeBase::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
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

void AUnrealHotelProjectGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    //ChangeMenuWidget(RoomUI);
}
