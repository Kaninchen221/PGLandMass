// Fill out your copyright notice in the Description page of Project Settings.


#include "PGCubeSphere.h"
#include "ProceduralMeshComponent.h"
//#include "/Engine/Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponent/Public/ProceduralMeshComponent.h"

APGCubeSphere::APGCubeSphere()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APGCubeSphere::CreateMeshComponent()
{
	//MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("MeshComponent");
}

void APGCubeSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

void APGCubeSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

