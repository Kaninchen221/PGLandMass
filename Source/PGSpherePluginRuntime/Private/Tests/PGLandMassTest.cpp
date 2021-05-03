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

    {
        APGLandMass* LandMass = CreateLandMass();

        FIntPoint VerticesLength(5, 8);
        FVector2D VerticesSpace(0.f, 0.f);
        LandMass->CreateVertices(VerticesLength, VerticesSpace);
        const TArray<FVector>& Vertices = LandMass->GetVertices();

        int ExpectedVerticesCount = VerticesLength.X * VerticesLength.Y;
        int ActualVerticesCount = Vertices.Num();
        TestEqual("Expected and Actual vertices count must be equal", ActualVerticesCount, ExpectedVerticesCount);
    }

    {
        APGLandMass* LandMass = CreateLandMass();

        FIntPoint VerticesLength(3, 3);
        FVector2D VerticesSpace(1.f, 1.f);
        LandMass->CreateVertices(VerticesLength, VerticesSpace);
        const TArray<FVector>& Vertices = LandMass->GetVertices();

        FVector ExpectedVertex(0.f, 0.f, 0.f);
        for (int VertexIndexY = 0; VertexIndexY < VerticesLength.Y; ++VertexIndexY)
        {
            for (int VertexIndexX = 0; VertexIndexX < VerticesLength.X; ++VertexIndexX)
            {
                int VertexRealIndex = (VertexIndexY * VerticesLength.X) + VertexIndexX;
                FVector ActualVertex = Vertices[VertexRealIndex];
                TestEqual("Actual and Expected vertex must be equal", ActualVertex, ExpectedVertex);

                ExpectedVertex.X += VerticesSpace.X;
            }
            ExpectedVertex.X = 0.f;
            ExpectedVertex.Y += VerticesSpace.Y;
        }
    }

    {
        APGLandMass* LandMass = CreateLandMass();

        FIntPoint VerticesLength(2, 2);
        FVector2D VerticesSpace(1.f, 1.f);
        LandMass->CreateVertices(VerticesLength, VerticesSpace);
        LandMass->CreateTriangles();

        const TArray<int>& Triangles = LandMass->GetTriangles();
        int ActualTrianglesCount = Triangles.Num();
        int ExpectedTrianglesCount = 6;
        TestEqual("Actual and Expected triangles count must be equal", ActualTrianglesCount, ExpectedTrianglesCount);

        TArray<int> ActualSecondTriangleBuffer({ Triangles[3], Triangles[4], Triangles[5] });
        TArray<int> ExpectedSecondTriangleBuffer({ 1, 2, 3 });
        for (int Index = 0; Index < 3; Index++) {
            int ActualIndex = ActualSecondTriangleBuffer[Index];
            int ExpectedIndex = ExpectedSecondTriangleBuffer[Index];
            TestEqual("Actual and Expected vertex index in buffer must be equal", ActualIndex, ExpectedIndex);
        }
    }

    {
        APGLandMass* LandMass = CreateLandMass();

        FIntPoint VerticesLength(4, 4);
        FVector2D VerticesSpace(1.f, 1.f);
        LandMass->CreateVertices(VerticesLength, VerticesSpace);
        float Lacunarity = 2.f;
        float Persistance = 0.5f;
        float Octaves = 3.f;
        LandMass->GenerateHeight(Lacunarity, Persistance, Octaves);

        const TArray<FVector>& Vertices = LandMass->GetVertices();
        float PreviousHeight = -1.f;
        for (const FVector& Vertex : Vertices)
        {
            float Height = Vertex.Z;

            TestNotEqual("Current and Previouse height shouldn't be equal", Height, PreviousHeight);

            PreviousHeight = Height;
        }
    }

    {
        APGLandMass* LandMass = CreateLandMass();
        FIntPoint VerticesLength(4, 4);
        FVector2D VerticesSpace(1.f, 1.f);
        LandMass->CreateVertices(VerticesLength, VerticesSpace);

        float Lacunarity = 2.f;
        float Persistance = 0.5f;
        float OctaveNumber = 1.f;
        TArray<float> Octave = LandMass->GenerateOctave(Lacunarity, Persistance, OctaveNumber);

        TestNotEqual("Octave can't be empty", Octave.Num(), 0);
    }

    return true;
}

#endif /// WITH_DEV_AUTOMATION_TESTS