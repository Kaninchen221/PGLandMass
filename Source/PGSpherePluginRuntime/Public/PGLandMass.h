// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGLandMass.generated.h"

class UProceduralMeshComponent;

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

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category=LandMass)
	void CreateVertices(FIntPoint InVerticesLength, FVector2D InVerticesSpace);

	const TArray<FVector>& GetVertices() const;

	UFUNCTION(BlueprintCallable, Category=LandMass)
	void CreateTriangles();

	const TArray<int>& GetTriangles() const;

	UFUNCTION(BlueprintCallable, Category = LandMass)
	void GenerateHeight(float Lacunarity, float Persistance, float Octaves);

	TArray<float> GenerateOctave(float Lacunarity, float Persistance, float OctaveNumber) const;

protected:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = LandMass)
	TArray<FVector> Vertices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = LandMass)
	FIntPoint VerticesLength;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = LandMass)
	FVector2D VerticesSpace;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = LandMass)
	TArray<int> Triangles;

};
