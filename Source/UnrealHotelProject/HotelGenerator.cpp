// Fill out your copyright notice in the Description page of Project Settings.


#include "HotelGenerator.h"
#include "Kismet/KismetStringLibrary.h"

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
	
	for (int i = 0; i < HotelDataAsset->HotelDataArray.Num();i++)
	{
		FString line = HotelDataAsset->HotelDataArray[i];
		FString lineRot = HotelDataAsset->HotelDataRotationArray[i];
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *lineRot);

		//Data
		TArray<FString> SubDataArray;
		int splitCount = line.ParseIntoArray(SubDataArray, TEXT("*"),true);
		//Rotation
		TArray<FString> SubRotationDataArray;
		int splitCountRot = lineRot.ParseIntoArray(SubRotationDataArray, TEXT("*"), true);

		if (splitCount != splitCountRot)
		{
			UE_LOG(LogTemp, Error, TEXT("Data array and rotation array are not equal"));
			return;
		}

		CreatedHotelActors.Add(new TArray<AActor*>());

		currentSpawnPoint = FVector(HotelDataAsset->TileSize * xMult, HotelDataAsset->TileSize * yMult, 0);

		for (int j = 0; j < splitCount; j++)
		{
			FString id = SubDataArray[j];
			currentSpawnPoint = FVector(HotelDataAsset->TileSize * xMult, HotelDataAsset->TileSize * yMult, 0);

			int rotationAmt = UKismetStringLibrary::Conv_StringToInt(SubRotationDataArray[j]);
			FRotator rotationOverride = FRotator(0,rotationAmt,0);

			//UE_LOG(LogTemp, Warning, TEXT("%s"), *rotationOverride.ToString());

			//Tiles
			if (id[0] == 'T')
			{
				TSubclassOf<AActor> actorToSpawn = GetActorForID(id, HotelObjectDataAsset->HotelTiles);
				if (actorToSpawn)
				{
					AActor* tile = GetWorld()->SpawnActor<AActor>(actorToSpawn, currentSpawnPoint, rotationOverride);
					CreatedHotelActors[yMult - 1]->Add(tile);
				}


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
				TSubclassOf<AActor> actorToSpawn = GetActorForID(id, HotelObjectDataAsset->HotelRooms);
				if (actorToSpawn)
				{
					ARoomActor* room = GetWorld()->SpawnActor<ARoomActor>(actorToSpawn, currentSpawnPoint, rotationOverride);
					room->roomID = FString::Printf(TEXT("Room%d&d"), i, j);
					RoomManager->AddRoom(room);
					CreatedHotelActors[yMult - 1]->Add(room);
				}
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
	return nullptr;
}
                                                                                                                                                                                                                                                          