#include "EmotionSystem.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Json.h"
#include "JsonUtilities.h"

bool UEmotionSystem::LoadQuestionsFromJSON(const FString& FilePath)
{
    FString FullPath = FPaths::ProjectContentDir() + FilePath;
    FString JsonString;

    if (!FFileHelper::LoadFileToString(JsonString, *FullPath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file."));
        return false;
    }

    TSharedPtr<FJsonValue> ParsedValue;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

    if (!FJsonSerializer::Deserialize(Reader, ParsedValue) || !ParsedValue.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON."));
        return false;
    }

    const TArray<TSharedPtr<FJsonValue>>* QuestionsArray;
    if (!ParsedValue->TryGetArray(QuestionsArray))
    {
        UE_LOG(LogTemp, Error, TEXT("JSON root is not an array."));
        return false;
    }

    for (const TSharedPtr<FJsonValue>& Entry : *QuestionsArray)
    {
        const TSharedPtr<FJsonObject>* Obj;
        if (Entry->TryGetObject(Obj))
        {
            FEmotionQuestion Q;
            Q.Question = (*Obj)->GetStringField("question");

            const TSharedPtr<FJsonObject>* OptionsObj;
            if ((*Obj)->TryGetObjectField("options", OptionsObj))
            {
                for (auto& Pair : (*OptionsObj)->Values)
                {
                    FString Key = Pair.Key;
                    FString Value;
                    if (Pair.Value->TryGetString(Value))
                    {
                        Q.Options.Add(Key, Value);
                    }
                }
            }

            Questions.Add(Q);
        }
    }

    return true;
}

void UEmotionSystem::RegisterAnswer(const FString& OptionLetter)
{
    if (OptionLetter == "A") Happy++;
    else if (OptionLetter == "B") Sad++;
    else if (OptionLetter == "C") Neutral++;
    else if (OptionLetter == "D") Angry++;
}

void UEmotionSystem::CalculateEmotionPercentages()
{
    int32 Total = Happy + Sad + Neutral + Angry;

    if (Total == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No answers recorded."));
        return;
    }

    float HappyPercent = static_cast<float>(Happy) / Total * 100.0f;
    float SadPercent = static_cast<float>(Sad) / Total * 100.0f;
    float NeutralPercent = static_cast<float>(Neutral) / Total * 100.0f;
    float AngryPercent = static_cast<float>(Angry) / Total * 100.0f;

    UE_LOG(LogTemp, Warning, TEXT("Happy: %.2f%%"), HappyPercent);
    UE_LOG(LogTemp, Warning, TEXT("Sad: %.2f%%"), SadPercent);
    UE_LOG(LogTemp, Warning, TEXT("Neutral: %.2f%%"), NeutralPercent);
    UE_LOG(LogTemp, Warning, TEXT("Angry: %.2f%%"), AngryPercent);
}