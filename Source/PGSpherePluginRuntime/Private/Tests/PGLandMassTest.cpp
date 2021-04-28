// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreTypes.h"
#include "Misc/AutomationTest.h"

#include "PGLandMass.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPGLandMassTest, "PGProject.UnitTests.APGLandMass", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FPGLandMassTest::RunTest(const FString& Parameters)
{
    auto CreateLandMass = [&]() -> APGLandMass*
    {
        APGLandMass* LandMass = NewObject<APGLandMass>();
        TestNotNull("LandMass can't be null", LandMass);
        return LandMass;
    };

    {
        APGLandMass* LandMass = CreateLandMass();
    }

    return true;
}

#endif /// WITH_DEV_AUTOMATION_TESTS