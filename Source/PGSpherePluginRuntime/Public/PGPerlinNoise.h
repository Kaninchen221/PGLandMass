// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PerlinNoise/PerlinNoise.hpp"
#include "PGPerlinNoise.generated.h"

UCLASS(Blueprintable, Category = PerlinNoise)
class PGSPHEREPLUGINRUNTIME_API UPGPerlinNoise : public UObject
{
	GENERATED_BODY()

private:

	siv::FPerlinNoise PerlinNoise;

public:

	UFUNCTION(BlueprintCallable)
	void Reseed(int Seed) { PerlinNoise.reseed(static_cast<uint32_t>(Seed)); }

	UFUNCTION(BlueprintCallable)
	float Noise2D(float X, float Y) const noexcept { return PerlinNoise.noise2D(X, Y); }

	UFUNCTION(BlueprintCallable)
	float NormalizedOctaveNoise1D(float X, int32 Octaves) const noexcept { return PerlinNoise.normalizedOctaveNoise1D(X, Octaves); }

	UFUNCTION(BlueprintCallable)
	float NormalizedOctaveNoise2D(float X, float Y, int32 Octaves) const noexcept { return PerlinNoise.normalizedOctaveNoise2D(X, Y, Octaves); }

	UFUNCTION(BlueprintCallable)
	float NormalizedOctaveNoise3D(float X, float Y, float Z, int32 Octaves) const noexcept { return PerlinNoise.normalizedOctaveNoise3D(X, Y, Z, Octaves); }
};
