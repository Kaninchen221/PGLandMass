// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGLandMass.generated.h"

class UProceduralMeshComponent;
class UMaterial;

UCLASS(Blueprintable, Category = LandMass)
class PGSPHEREPLUGINRUNTIME_API APGLandMass : public AActor
{
	GENERATED_BODY()
	
public:	
	APGLandMass();

protected:

	void CreateMeshComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Mesh)
	UProceduralMeshComponent* MeshComponent;

public:	

	UFUNCTION(BlueprintCallable, Category=LandMass)
	void CreateVertices(FIntPoint InVerticesLength, FVector2D InVerticesSpace);

	const TArray<FVector>& GetVertices() const;

	UFUNCTION(BlueprintCallable, Category=LandMass)
	void CreateTriangles();

	const TArray<int>& GetTriangles() const;

	const UMaterial* GetMaterial() const;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = LandMass)
	TArray<FVector> Vertices;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = LandMass)
	FIntPoint VerticesCount;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = LandMass)
	FVector2D VerticesSpace;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = LandMass)
	TArray<int> Triangles;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = LandMass)
	UMaterial* Material;
};
