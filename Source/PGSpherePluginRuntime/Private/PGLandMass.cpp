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

	FDateTime ActualTime = FDateTime::Now();
	int Time = ActualTime.GetMillisecond();

	int Octaves = 1;

	for (const FVector& Vertex : Vertices)
	{
		float X = (Vertex.X + 0.01f) * Frequency;
		float Y = (Vertex.Y + 0.01f) * Frequency;
		float Z = PerlinNoise->NormalizedOctaveNoise3D(X, Y, Time, Octaves);
		Z *= Amplitude;
		Octave.Add(Z);

		++Time;
	}

	return Octave;
}
