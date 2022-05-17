// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridLevel.generated.h"

const FVector2D INALID_LOC = FVector2D(-1, -1);

USTRUCT()
struct FConnections //Millington p.707
{	

	GENERATED_BODY()

	UPROPERTY()
	bool inMaze;

	UPROPERTY()
		uint8 directions[4];	//can't create bool arrays in UE4

	FConnections() //default constructor 
	{	
		inMaze = false;

		for (int i = 0; i < 4; i++) 
		{
			directions[i] = false;
		}
	}
};

USTRUCT()
struct FExitsByIndex //Millington p.707
{	

	GENERATED_BODY()

	UPROPERTY()
	int dx;

	UPROPERTY()
		int dy;

	UPROPERTY()
		int index;

	FExitsByIndex() //default constructor
	{	
		dx = dy = index = 0;
	}

	FExitsByIndex(int x, int y, int i) 
	{
		dx = x; dy = y; index = i;
	}
};


UCLASS()
class PROCGEN_AND_AI_API AGridLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	int dx, dy, wid, hgt;
	TArray<FConnections> cells;	//effectively, a wid x hgt grid
	FVector2D startLocation;
	FRandomStream RandomStream;
	TArray<FVector2D> locations;	//stack

public:
	TArray<FConnections>& createGrid(int seed, FVector2D start);
	bool canPlaceCorridor(int x, int y, int dir);
	FVector2D makeConnection(FVector2D loc);
	void shuffle(TArray <FExitsByIndex>& na);
	void initConnections(uint8 w, uint8 h);
	TArray <FExitsByIndex> NEIGHBOURS; //possible exits from each cell
};
