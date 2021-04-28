// Fill out your copyright notice in the Description page of Project Settings.


#include "PGLandMass.h"
#include "ProceduralMeshComponent.h"

APGLandMass::APGLandMass()
{
	PrimaryActorTick.bCanEverTick = false;

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

