// Fill out your copyright notice in the Description page of Project Settings.


#include "HotelManager.h"

// Sets default values
AHotelManager::AHotelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

AHotelManager::~AHotelManager()
{
	delete _TimeManager;
	delete _FinanceManager;
}

// Called when the game starts or when spawned
void AHotelManager::BeginPlay()
{
	Super::BeginPlay();
	RoomManger->HotelManager = HotelManagerBP;
	_TimeManager = new TimeManager(SunLight, HotelManagerBP);
	_FinanceManager = new FinanceManager();
}

// Called every frame
void AHotelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_TimeManager)
	{
		_TimeManager->Tick(DeltaTime);
		HandleTimedEvents();
	}
}

FString AHotelManager::GetTimeString()
{
	if (_TimeManager)
	{
		return _TimeManager->GetTimeInStandardFormat();
	}
	return FString("Error");
}

FString AHotelManager::GetMoneyString()
{
	if (_FinanceManager)
	{
		return FString::FromInt(_FinanceManager->GetMoney());
	}
	return FString("Error");
}

void AHotelManager::AssignGuestToRoom(RoomInfo* ri)
{
	if (ri)
	{
		APerson* person;
		if (PeopleManger->GetWaitingPerson(person))
		{
			if (person)
			{
				ri->PersonRef = person;
				ri->RoomStatus = ARoomManager::RoomStatus::OCCUPIED;

				person->MoveToLocation(ri->RoomRef->GetActorLocation(), [this](bool success)
					{
						UE_LOG(LogTemp, Warning, TEXT("Move done - %s"), (success ? TEXT("true") : TEXT("false")));
					});
			}
		}
	}
}

void AHotelManager::AssignHousekeeperToRoom(RoomInfo* ri)
{
	if (ri)
	{
		APerson* employee = PeopleManger->GetAvailableHousekeeper();
		if(employee)	
		{
			employee->MoveToLocation(ri->RoomRef->GetActorLocation(), [this,ri,employee](bool success)
				{
					UE_LOG(LogTemp, Warning, TEXT("Move done - %s"), (success ? TEXT("true") : TEXT("false")));
					FinancialTransactionHelper(FinanceManager::TransactionType::CLEAN, false);
					//LastRoomClicked->RoomStatus = RoomStatus::READY;
					ri->RoomStatus = ARoomManager::RoomStatus::READY;
					PeopleManger->ReturnHousekeeper(employee);
				});
		}
	}
}

void AHotelManager::CheckOutGuests()
{
	TArray<APerson*> guests = RoomManger->GetGuestInRooms();
	for (APerson* person : guests)
	{
		person->DecrementNightsLeft();
		//Only check out guest who are done
		if (person->GetNightsLeft() == 0)
		{
			FString guestID = person->GetID();
			person->MoveToLocation(PeopleManger->GetExit(), [this, guestID](bool success)
				{
					//For now, just delete them
					//Need to clean up room data
					RoomManger->CheckOutGuest(guestID);
			//Need to clean up people data
			PeopleManger->RemoveGuest(guestID);

			_FinanceManager->FinancialTransaction(FinanceManager::TransactionType::NIGHT, true);
				});
		}
	}
}

void AHotelManager::FinancialTransactionHelper(FinanceManager::TransactionType tt, bool add)
{
	if (_FinanceManager)
	{
		_FinanceManager->FinancialTransaction(tt, add);
	}
}

void AHotelManager::HandleTimedEvents()
{
	float time = _TimeManager->GetActualTime();
	int day = _TimeManager->GetDay();

	//Checkout
	if (_LastCheckoutDay != day && (int)time == CheckoutTime)
	{
		_LastCheckoutDay = day;
		CheckOutGuests();
	}
}

