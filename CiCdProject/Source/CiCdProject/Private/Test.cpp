#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

#include "Editor/EditorEngine.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Tests/AutomationCommon.h"
#include "Tests/AutomationEditorCommon.h"
//#include "Logging/StructuredLog.h" // <- для UE::SerializeForLog
//#include "Math/Vector.h"           // <- для FVector

#include "MyClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyTests, Log, All);

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSimpleTrueTest, "TrainingTests.Simple", EAutomationTestFlags::EditorContext |  EAutomationTestFlags::CommandletContext | EAutomationTestFlags::ProductFilter)

	bool FSimpleTrueTest::RunTest(const FString& Parameters)
{
	const int value1 = 1;

	TestEqual("value = 1", value1, 1);

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetActorTest, "TrainingTests.PIE.GetActor",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::ProductFilter)

	bool FGetActorTest::RunTest(const FString& Parameters)
{
	UE_LOG(LogMyTests, Log, TEXT(" ---------------------------------- ====TEST START=== ----------------------------------"));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(false));
	ADD_LATENT_AUTOMATION_COMMAND(FWaitLatentCommand(1.0f));

	ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool
		{
			UWorld* World = GEditor->GetPIEWorldContext()->World();
			if (!TestNotNull(TEXT("World must be valid after map load"), World))
			{
				return false; // Без мира тест дальше нет смысла
			}

			// Загружаем BP-класс
			const TCHAR* BpClassPath = TEXT("/Game/TestActor.TestActor_C");
			TSubclassOf<AActor> BpClass = StaticLoadClass(AMyClass::StaticClass(), nullptr, BpClassPath);
			if (!TestNotNull(TEXT("BP class must be loaded"), *BpClass))
			{
				return false;
			}

			// Ищем актёра этого класса
			auto FoundActor = UGameplayStatics::GetActorOfClass(World, BpClass);
			AMyClass* TestActor = Cast<AMyClass>(FoundActor);

			if (!TestNotNull(TEXT("TestActor is found"), TestActor))
			{
				return false;
			}
			const auto Location = TestActor->GetActorLocation();		

			//UE_LOGFMT(LogMyTests, Log, "Location = {} ", Location.ToString());
			UE_LOG(LogMyTests, Log, TEXT("Location = %s"), *Location.ToString());

			// Проверка позиции
			TestNotEqual(TEXT("Actor's location not equal null"), Location, FVector::ZeroVector);

			return true;
		}));

	UE_LOG(LogMyTests, Log, TEXT(" ---------------------------------- ====TEST END=== ----------------------------------"));
	return true;
}

#endif