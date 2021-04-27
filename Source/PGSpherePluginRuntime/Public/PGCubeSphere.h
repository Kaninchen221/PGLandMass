// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGCubeSphere.generated.h"

//class UProceduralMeshComponent;

UCLASS(Blueprintable)
class PGSPHEREPLUGINRUNTIME_API APGCubeSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	APGCubeSphere();

protected:

	void CreateMeshComponent();

	//UPROPERTY(BlueprintReadWrite, Category=Mesh)
	//UProceduralMeshComponent* MeshComponent;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
