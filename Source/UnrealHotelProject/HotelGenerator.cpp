// Fill out your copyright notice in the Description page of Project Settings.


#include "HotelGenerator.h"

// Sets default values
AHotelGenerator::AHotelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHotelGenerator::BeginPlay()
{
	Super::BeginPlay();
	GenerateHotel();

	FVector middle = FMath::Lerp(CreatedHotelActors[0]->GetData()[0]->GetActorLocation(), CreatedHotelActors.Last(0)->Last(0)->GetActorLocation(), .5f);
	FVector cameraLocation = FVector(middle.X, middle.Y+400, 1350);
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(cameraLocation);
	NavMesh->SetActorLocation(middle);
	NavMesh->SetActorScale3D(FVector(10, 10, 10));

	HotelManager->StartLogic();
}

// Called every frame
void AHotelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHotelGenerator::GenerateHotel()
{
	FVector currentSpawnPoint = FVector::ZeroVector;
	int xMult = 1;
	int yMult = 1;
	
	for (FString line : HotelDataAsset->HotelDataArray)
	{
		TArray<FString> SubDataArray;
		int splitCount = line.ParseIntoArray(SubDataArray, TEXT("*"),true);
		CreatedHotelActors.Add(new TArray<AActor*>());

		currentSpawnPoint = FVector(HotelDataAsset->TileSize * xMult, HotelDataAsset->TileSize * yMult, 0);

		for (int i = 0; i < splitCount; i++)
		{
			FString id = SubDataArray[i];
			currentSpawnPoint = FVector(HotelDataAsset->TileSize * xMult, HotelDataAsset->TileSize * yMult, 0);

			//Tiles
			if (id[0] == 'T')
			{
				TSubclassOf<AActor> actorToSpawn = GetActorForID(id, HotelDataAsset->HotelTiles);
				AActor* tile = GetWorld()->SpawnActor<AActor>(actorToSpawn, currentSpawnPoint, FRotator::ZeroRotator);
				CreatedHotelActors[yMult - 1]->Add(tile);

				//if (id == "T3E")
				//{
				//	entrance = tile->GetActorLocation();
				//}
				//else if (id == "T3X")
				//{
				//	exit = tile->GetActorLocation();
				//}
				//else if (id == "T3S")
				//{
				//	employee = tile->GetActorLocation();
				//}
			}
			//Rooms
			else if (id[0] == 'R')
			{

			}
			//Misc
			else if (id[0] == 'M')
			{
				//Checkin
				if (id == "M1")
				{
					HotelManager->SetActorLocation(currentSpawnPoint);
					CreatedHotelActors[yMult - 1]->Add(HotelManager->GetOwner());
				}
			}
			xMult++;
		}
		
		yMult++;
		xMult = 1;
	}

	FVector entrance = CreatedHotelActors[0]->GetData()[0]->GetActorLocation();
	FVector exit = CreatedHotelActors[0]->GetData()[0]->GetActorLocation();
	FVector employee = CreatedHotelActors[0]->GetData()[1]->GetActorLocation();
	PeopleManager->SetPoints(entrance,exit,employee);
}

TSubclassOf<AActor> AHotelGenerator::GetActorForID(FString id,TArray<FHotelObject> activeArray)
{
	for (FHotelObject fho : activeArray)
	{
		if (id == fho.ItemID)
		{
			return fho.ItemActor;
		}
	}
	return NULL;
}

