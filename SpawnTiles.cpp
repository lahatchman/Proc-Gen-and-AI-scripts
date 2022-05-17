// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnTiles.h"
#include "Tile.h"
#include "Goal.h"

// Sets default values
ASpawnTiles::ASpawnTiles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	xGap = yGap = 10.0f;
	xStart = yStart = zStart = 0.0f;
	numHorizTiles = numVertTiles = seed = 5;
	grid = CreateDefaultSubobject<AGridLevel>(TEXT("grid"));

}

// Called when the game starts or when spawned
void ASpawnTiles::BeginPlay()
{
	Super::BeginPlay();
	
	grid->initConnections(numHorizTiles, numVertTiles);
	TArray<FConnections> connections = grid->createGrid(seed, FVector2D(0, 0)); //start with seed, and init cell
	FRandomStream RandomStream;
	RandomStream.Initialize(seed);
	int entrance = (numHorizTiles * numVertTiles) / 2;
	int enemySpawn = RandomStream.RandRange(numHorizTiles * numVertTiles / 2, numHorizTiles * numVertTiles - 1);
	int exit = ((numHorizTiles * numVertTiles) - 1) / 2;

	for (int i = 0; i < connections.Num(); i++) 
	{
		int x = xStart + float(i % numHorizTiles) * xGap;
		int y = yStart + float(i / numHorizTiles) * yGap;

		if (i == entrance)
		{
			spawnATile(entranceTile, x, y, zStart);
			continue; //get out of loop, but carry on
		}

		if (i == exit)
		{
			//spawnGoal(goal, x, y, zStart);
			spawnATile(tileExit, x, y, zStart);
			continue; //get out of loop, but carry on
		}

		spawnATile(floorTile, x, y, zStart);

		for (int j = 0; j < 4; j++) 
		{
			int dx = grid->NEIGHBOURS[j].dx;
			int dy = grid->NEIGHBOURS[j].dy;
			int idx = grid->NEIGHBOURS[j].index;

			if (connections[i].directions[j] != 1) 
			{
				if (dx != 0)
				{
					spawnATile(vertWall, x + (float)dx * (xGap + 2.0f) / 2.0f, y, zStart);
				}
				else 
				{
					spawnATile(horizWall, x, y + (float)dy * (yGap + 2.0f) / 2.0f, zStart);
				}
			}
		}
	}

}

// Called every frame
void ASpawnTiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnTiles::spawnATile(TSubclassOf<class ATile>tileClass, float x, float y, float z) 
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FVector spawnLoc = FVector(x, y, z);
	FRotator rot = FRotator::ZeroRotator;
	AActor* a = GetWorld()->SpawnActor<ATile>(tileClass, spawnLoc, rot, spawnParams);
}

void ASpawnTiles::spawnGoal(TSubclassOf<class AGoal> goalClass, float x, float y, float z)
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FVector spawnLoc = FVector(x, y, z);
	FRotator rot = FRotator::ZeroRotator;
	AActor* a = GetWorld()->SpawnActor<AGoal>(goalClass, spawnLoc, rot, spawnParams);
}
