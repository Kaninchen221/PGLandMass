// Fill out your copyright notice in the Description page of Project Settings.


#include "PGLandMass.h"
#include "ProceduralMeshComponent.h"
#include "Misc/DateTime.h"
#include "PGPerlinNoise.h"

APGLandMass::APGLandMass()
{
	PrimaryActorTick.bCanEverTick = false;

	CreateMeshComponent();
	RootComponent = MeshComponent;
}

void APGLandMass::CreateMeshComponent()
{
	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("MeshComponent");
}

void APGLandMass::BeginPlay()
{
	Super::BeginPlay();

}

void APGLandMass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APGLandMass::CreateVertices(FIntPoint InVerticesLength, FVector2D InVerticesSpace)
{
	Vertices.Empty();

	VerticesLength = InVerticesLength;
	VerticesSpace = InVerticesSpace;

	int VerticesCount = VerticesLength.X * VerticesLength.Y;
	Vertices.Reserve(VerticesCount);

	FVector Vertex(0.f, 0.f, 0.f);
	for (int VertexIndexY = 0; VertexIndexY < VerticesLength.Y; ++VertexIndexY)
	{
		for (int VertexIndexX = 0; VertexIndexX < VerticesLength.X; ++VertexIndexX)
		{
			Vertices.Add(Vertex);
			Vertex.X += VerticesSpace.X;
		}
		Vertex.X = 0.f;
		Vertex.Y += VerticesSpace.Y;
	}
}

const TArray<FVector>& APGLandMass::GetVertices() const
{
	return Vertices;
}

void APGLandMass::CreateTriangles()
{
	Triangles.Empty();
	
	int OneBeforeLastRow = VerticesLength.Y - 1;
	for (int VertexRow = 0; VertexRow < OneBeforeLastRow; VertexRow++)
	{
		int OneBeforeLastColumn = VerticesLength.X - 1;
		for (int VertexColumn = 0; VertexColumn < OneBeforeLastColumn; VertexColumn += 1)
		{
			int CurrentVertexIndex = (VertexRow * VerticesLength.X) + VertexColumn;

			int LeftTopIndex = CurrentVertexIndex;
			int RightTopIndex = CurrentVertexIndex + 1;
			int LeftBottomIndex = CurrentVertexIndex + VerticesLength.X;
			int RightBottomIndex = LeftBottomIndex + 1;

			Triangles.Add(RightTopIndex);
			Triangles.Add(LeftTopIndex);
			Triangles.Add(LeftBottomIndex);

			Triangles.Add(RightTopIndex);
			Triangles.Add(LeftBottomIndex);
			Triangles.Add(RightBottomIndex);
		}
	}
}

const TArray<int>& APGLandMass::GetTriangles() const
{
	return Triangles;
}

void APGLandMass::GenerateHeight(float Lacunarity, float Persistance, float Octaves)
{
	for (float OctaveIndex = 0; OctaveIndex < Octaves; OctaveIndex++)
	{
		TArray<float> Octave = GenerateOctave(Lacunarity, Persistance, OctaveIndex);
		
		for (int Index = 0; Index < Octave.Num(); Index++)
		{
			Vertices[Index].Z += Octave[Index];
			//Vertices[Index].Z += Octave[Index] / Octaves;
		}
	}

}

TArray<float> APGLandMass::GenerateOctave(float Lacunarity, float Persistance, float OctaveNumber) const
{
	UPGPerlinNoise* PerlinNoise = NewObject<UPGPerlinNoise>();
	if (!PerlinNoise) {
		return TArray<float>();
	}

	const float MinOctaveNumber = 0.f;
	const float MaxOctaveNumber = 100.f;
	OctaveNumber = FMath::Clamp(OctaveNumber, MinOctaveNumber, MaxOctaveNumber);
	OctaveNumber = FMath::Floor(OctaveNumber);

	float Frequency = FMath::Pow(Lacunarity, OctaveNumber);
	float Amplitude = FMath::Pow(Persistance, OctaveNumber);

	TArray<float> Octave;
	Octave.Reserve(Vertices.Num());

	int Octaves = 1;

	FDateTime StartTime = FDateTime::Now();
	int Miliseconds = 0;

	for (const FVector& Vertex : Vertices)
	{
		FDateTime NowTime = FDateTime::Now();
		FTimespan ElapsedTime = NowTime - StartTime;
		Miliseconds += ElapsedTime.GetTotalMilliseconds() / 1000.f;

		float X = Vertex.X * Frequency;
		float Y = Vertex.Y * Frequency;
		float Z = static_cast<float>(Miliseconds) * Frequency;
		float Value = PerlinNoise->NormalizedOctaveNoise3D(X, Y, Z, Octaves);
		Value *= Amplitude;
		Octave.Add(Value);

	}

	return Octave;
}

void APGLandMass::ShuffleXY()
{
	UPGPerlinNoise* PerlinNoise = NewObject<UPGPerlinNoise>();

	FDateTime ActualTime = FDateTime::Now();
	int Time = ActualTime.GetMillisecond();

	auto Noise1D = [&PerlinNoise, &Time](float X, float MaxValue) -> float
	{
		++Time;
		float Octaves = 1.f;
		float Noise = PerlinNoise->NormalizedOctaveNoise2D(X, Time, Octaves);
		Noise /= 2.f;
		Noise *= MaxValue;
		return Noise;
	};

	for (FVector& Vertex : Vertices)
	{
		FVector Offset(0.f, 0.f, 0.f);
		Offset.X = Noise1D(Vertex.Y, VerticesSpace.X);
		Offset.Y = Noise1D(Vertex.X, VerticesSpace.Y);

		Vertex += Offset;
	}
}
