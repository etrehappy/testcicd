#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimpleModuleTest, "ModuleTests.SimpleTest", EAutomationTestFlags::EditorContext | /*EAutomationTestFlags::CommandletContext |*/ EAutomationTestFlags::ProductFilter)

bool FSimpleModuleTest::RunTest(const FString& Parameters)
{
	const int value1 = 1;

	TestEqual("value = 1", value1, 1);

	return true;
}