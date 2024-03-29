// Fill out your copyright notice in the Description page of Project Settings.


#include "PeopleManager.h"
#include "EmployeeData.h"
#include "HotelManager.h"


// Sets default values
APeopleManager::APeopleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Floor_Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor_Entrance"));
	//SetRootComponent(Floor_Entrance);
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("PeopleManagerParent")));

	EntrancePoint = CreateDefaultSubobject<USceneComponent>(TEXT("EntrancePoint"));
	EntrancePoint->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	//Floor_Exit = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor_Exit"));
	//Floor_Exit->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExitPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ExitPoint"));
	ExitPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//Employee_Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Employee_Entrance"));
	//Employee_Entrance->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	EmployeePoint = CreateDefaultSubobject<USceneComponent>(TEXT("EmployeePoint"));
	EmployeePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APeopleManager::BeginPlay()
{
	Super::BeginPlay();

	ReadInNames();

}

// Called every frame
void APeopleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_CurrentTick += DeltaTime;
	if (_CurrentTick >= _NextCreationTime)
	{
		CreateGuest();
		_CurrentTick = 0;
	}
}

bool APeopleManager::GetWaitingPerson(APerson* &person)
{
	_GuestWaitingCount--;
	return GuestWaiting.Dequeue(person);
}

APerson* APeopleManager::GetAvailableHousekeeper()
{
	for (APerson* person : EmployeeList)
	{
		if (person->GetEmployeeData() && person->GetEmployeeData()->GetEmployeeType() == APeopleManager::EmployeeType::HOUSEKEEP)
		{
			return person;
		}
	}
	return nullptr;
}

bool APeopleManager::RemoveGuest(FString guestID)
{
	for (int i = 0; i < GuestList.Num(); i++)
	{
		if (GuestList[i]->GetID() == guestID)
		{
			GetWorld()->DestroyActor(GuestList[i]);
			GuestList.RemoveAt(i);
			return true;
		}
	}
	return false;
}

FVector APeopleManager::GetEntrance()
{
	return EntrancePoint->GetComponentLocation();
}

FVector APeopleManager::GetExit()
{
	return ExitPoint->GetComponentLocation();
}

void APeopleManager::ReturnHousekeeper(APerson* person)
{
	person->AddTask(TaskManager::TaskType::GO_TO, -1, EmployeePoint->GetComponentLocation(), nullptr);
}

void APeopleManager::SetPoints(FVector entrance, FVector exit, FVector employee)
{
	EntrancePoint->SetWorldLocation(entrance + FVector(0,0,20));
	ExitPoint->SetWorldLocation(exit + FVector(0, 0, 20));
	EmployeePoint->SetWorldLocation(employee + FVector(0, 0, 20));
}

void APeopleManager::StartLogic()
{
	CreateEmployee(EmployeeType::HOUSEKEEP);
}

APerson* APeopleManager::CreatePerson(FVector loc,APerson::PersonType pt)
{
	APerson* createdPerson = GetWorld()->SpawnActor<APerson>(Person1Character, loc, FRotator(0, 180, 0));
	createdPerson->Setup(pt, FString::FromInt(AllCreatedPeople.Num() + 1), GetRandomName());
	AllCreatedPeople.Add(createdPerson);
	return createdPerson;
}

void APeopleManager::CreateGuest()
{
	if (!HotelManager->ShouldSpawnGuest())
	{
		return;
	}

	APerson* person = CreatePerson(EntrancePoint->GetComponentLocation(), APerson::PersonType::GUEST);

	GuestList.Add(person);
	GuestWaiting.Enqueue(person);
	_GuestWaitingCount++;

	_NextCreationTime = FMath::RandRange(MIN_NEXT_PERSON_TIME, MAX_NEXT_PERSON_TIME);

	person->AddTask(TaskManager::TaskType::GO_TO, -1, HotelManager->GetCheckInLocation(), nullptr);
}

void APeopleManager::CreateEmployee(EmployeeType et)
{
	APerson* person = CreatePerson(EmployeePoint->GetComponentLocation(), APerson::PersonType::EMPLOYEE);
	EmployeeList.Add(person);
}

void APeopleManager::ReadInNames()
{
	FString file = FPaths::ProjectContentDir();
	file.Append(TEXT("DataFiles/first-names.txt"));
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (FileManager.FileExists(*file))
	{
		if (FFileHelper::LoadFileToStringArray(FirstNames, *file))
		{
			UE_LOG(LogTemp, Warning, TEXT("Successfully loaded names"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not load first names file"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find first names file"));
	}
}

FString APeopleManager::GetRandomName()
{
	if (FirstNames.Num() > 0)
	{
		return FirstNames[FMath::RandRange(0, FirstNames.Num() - 1)];
	}
	return TEXT("Bob");
}

