// Fill out your copyright notice in the Description page of Project Settings.


#include "PGLandMass.h"
#include "ProceduralMeshComponent.h"

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
