// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreTypes.h"
#include "Misc/AutomationTest.h"

#include "PGCubeSphere.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPGCubeSphereTest, "PGSphere.UnitTests.APGCubeSphere", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FPGCubeSphereTest::RunTest(const FString& Parameters)
{
    auto CreateCubeSphere = [&]() -> APGCubeSphere*
    {
        APGCubeSphere* CubeSphere = NewObject<APGCubeSphere>();
        TestNotNull("CubeSphere can't be null", CubeSphere);
        return CubeSphere;
    };

    {
        APGCubeSphere* CubeSphere = CreateCubeSphere();
    }

    return true;
}

#endif /// WITH_DEV_AUTOMATION_TESTS