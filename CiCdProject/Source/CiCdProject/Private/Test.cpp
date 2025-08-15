#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimpleTrueTest, "TrainingTests.Simple",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	bool FSimpleTrueTest::RunTest(const FString& Parameters)
{
	const int value1 = 1;

	TestEqual("value = 1", value1, 1);

	return true;
}

