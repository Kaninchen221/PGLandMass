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

void APGLandMass::CreateVertices(FIntPoint InVerticesLength, FVector2D InVerticesSpace)
{
	Vertices.Empty();

	VerticesCount = InVerticesLength;
	VerticesSpace = InVerticesSpace;

	int VerticesCountSum = VerticesCount.X * VerticesCount.Y;
	Vertices.Reserve(VerticesCountSum);

	FVector Vertex(0.f, 0.f, 0.f);
	for (int VertexIndexY = 0; VertexIndexY < VerticesCount.Y; ++VertexIndexY)
	{
		for (int VertexIndexX = 0; VertexIndexX < VerticesCount.X; ++VertexIndexX)
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

	int OneBeforeLastRow = VerticesCount.Y - 1;
	int OneBeforeLastColumn = VerticesCount.X - 1;
	const int TrianglesIndicesCountInOneQuad = 6;
	int TrianglesCount = OneBeforeLastRow * OneBeforeLastColumn * TrianglesIndicesCountInOneQuad;
	Triangles.Reserve(TrianglesCount);

	for (int VertexRow = 0; VertexRow < OneBeforeLastRow; VertexRow++)
	{
		for (int VertexColumn = 0; VertexColumn < OneBeforeLastColumn; VertexColumn += 1)
		{
			int CurrentVertexIndex = (VertexRow * VerticesCount.X) + VertexColumn;

			int LeftTopIndex = CurrentVertexIndex;
			int RightTopIndex = CurrentVertexIndex + 1;
			int LeftBottomIndex = CurrentVertexIndex + VerticesCount.X;
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

const UMaterial* APGLandMass::GetMaterial() const
{
	return Material;
}
