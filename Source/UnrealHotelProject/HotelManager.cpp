// Fill out your copyright notice in the Description page of Project Settings.


#include "HotelManager.h"

// Sets default values
AHotelManager::AHotelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CheckInDesk = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CheckInDesk"));
	SetRootComponent(CheckInDesk);
	GuestStandLocation = CreateDefaultSubobject<USceneComponent>(TEXT("GuestStandLocation"));
	GuestStandLocation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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
	RoomManger->HotelManager = this;//HotelManagerBP;
	PeopleManger->HotelManager = this;//HotelManagerBP;
	_TimeManager = new TimeManager(SunLight, this);
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
				ri->RoomRef->SetStatus("OCCUPIED");

				person->AddTask(TaskManager::TaskType::GO_TO, -1, ri->RoomRef->GetActorLocation(), nullptr);
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
			employee->AddTask(TaskManager::TaskType::GO_TO, -1, ri->RoomRef->GetActorLocation(), nullptr);
			employee->AddTask(TaskManager::TaskType::CLEAN, 2.5f, FVector::ZeroVector, [this, ri, employee](bool success)
				{
					FinancialTransactionHelper(FinanceManager::TransactionType::CLEAN, false);
					ri->RoomStatus = ARoomManager::RoomStatus::READY;
					ri->RoomRef->SetStatus("READY");
				});
			employee->AddTask(TaskManager::TaskType::GO_TO, -1, PeopleManger->GetEmployeePoint(), nullptr);
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
			UE_LOG(LogTemp, Warning, TEXT("Check Out"));
			person->AddTask(TaskManager::TaskType::GO_TO, -1, PeopleManger->GetExit(), [this, guestID](bool success)
				{
					RoomManger->CheckOutGuest(guestID);
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

bool AHotelManager::ShouldSpawnGuest()
{
	int emptyRoomCount = RoomManger->GetEmptyRoomCount();
	int guestWaiting = PeopleManger->GetWaitingGuestCount();

	bool shouldSpawn = true;
	shouldSpawn &= (int)_TimeManager->GetActualTime() >= CHECKIN_TIME;
	shouldSpawn &= emptyRoomCount > guestWaiting-1;
	return shouldSpawn;
}

void AHotelManager::StartLogic()
{
	PeopleManger->StartLogic();
}

void AHotelManager::HandleTimedEvents()
{
	float time = _TimeManager->GetActualTime();
	int day = _TimeManager->GetDay();

	//Checkout
	if (_LastCheckoutDay != day && (int)time == CHECKOUT_TIME)
	{
		_LastCheckoutDay = day;
		CheckOutGuests();
	}
}

