#pragma once

#include "CoreMinimal.h"
#include "EmotionSystem.generated.h"

USTRUCT(BlueprintType)
struct FEmotionQuestion
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Question;

    UPROPERTY(BlueprintReadWrite)
    TMap<FString, FString> Options; // "A", "B", "C", "D"
};

UCLASS(Blueprintable)
class YOURGAME_API UEmotionSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    bool LoadQuestionsFromJSON(const FString& FilePath);

    UFUNCTION(BlueprintCallable)
    void RegisterAnswer(const FString& OptionLetter);

    UFUNCTION(BlueprintCallable)
    void CalculateEmotionPercentages();

    UPROPERTY(BlueprintReadOnly)
    TArray<FEmotionQuestion> Questions;

private:
    int32 Happy = 0;
    int32 Sad = 0;
    int32 Neutral = 0;
    int32 Angry = 0;
};
