// Fill out your copyright notice in the Description page of Project Settings.

//Based on Millington's Maze alg (AI for Games 3rd Ed.)
#include "GridLevel.h"
#include "Engine.h"
#include "Math/RandomStream.h"

// Sets default values
AGridLevel::AGridLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	wid = hgt = 10;
	NEIGHBOURS.Add(FExitsByIndex(1, 0, 0));	//dx, dy, idx
	NEIGHBOURS.Add(FExitsByIndex(0, 1, 1));
	NEIGHBOURS.Add(FExitsByIndex(0, -1, 2));
	NEIGHBOURS.Add(FExitsByIndex(-1, 0, 3));
}

// Called when the game starts or when spawned
void AGridLevel::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AGridLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<FConnections>& AGridLevel::createGrid(int seed, FVector2D start) 
{
	RandomStream.Initialize(seed);
	cells[start.X + start.Y * wid].inMaze = true;
	locations.Push(start);

	while (locations.Num() > 0) //check stack
	{	
		FVector2D current = locations.Top();
		FVector2D next = makeConnection(current);

		if (next != INALID_LOC) //if not invalid loc
		{
			locations.Push(next);
		}
		else
		{
			locations.Pop();
		}
	}

	return cells;
}

bool AGridLevel::canPlaceCorridor(int x, int y, int dir) 
{
	return ((x >= 0 && x < wid) && (y >= 0 && y < hgt) && (!cells[x + y * wid].inMaze));
}

FVector2D AGridLevel::makeConnection(FVector2D loc) 
{
	int x, y, nx, ny, fromDir;
	TArray <FExitsByIndex>neighbours = NEIGHBOURS;
	shuffle(neighbours);	//randomly select exits
	x = loc.X;
	y = loc.Y;

	for (int i = 0; i < neighbours.Num(); i++) //try each exit
	{ 
		nx = x + neighbours[i].dx;	//get next pos
		ny = y + neighbours[i].dy;
		fromDir = 3 - neighbours[i].index;	//calc from dir for next cell

		if (canPlaceCorridor(nx, ny, fromDir)) //if possible to place
		{	
			cells[x + y * wid].directions[neighbours[i].index] = true;
			cells[nx + ny * wid].inMaze = true;
			cells[nx + ny * wid].directions[fromDir] = true;

			return FVector2D(nx, ny);
		}
	}

	return INALID_LOC;
}

void AGridLevel::shuffle(TArray<FExitsByIndex>& na) 
{
	for (int32 i = na.Num() - 1; i > 0; i--) 
	{
		int32 j = RandomStream.RandRange(0, na.Num() - 1);
		FExitsByIndex temp = na[i];	//swap rand elements
		na[i] = na[j];
		na[j] = temp;
	}
}

void AGridLevel::initConnections(uint8 w, uint8 h) 
{
	wid = w; hgt = h;	//update attributes

	for (int i = 0; i < w; i++) 
	{
		for (int j = 0; j < h; j++) 
		{
			FConnections conn;
			conn.inMaze = false;

			for (int k = 0; k < 4; k++)
			{
				conn.directions[k] = 255; //invalid dir
			}

			cells.Add(conn);	//init cells
		}
	}
}

