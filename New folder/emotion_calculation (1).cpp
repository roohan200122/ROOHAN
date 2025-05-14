TMap<FString, int32> EmotionCount = {
    {"Happy", 0},
    {"Sad", 0},
    {"Neutral", 0},
    {"Angry", 0}
};

void RecordAnswer(FString SelectedOption)
{
    if (SelectedOption == "A") EmotionCount["Happy"]++;
    else if (SelectedOption == "B") EmotionCount["Sad"]++;
    else if (SelectedOption == "C") EmotionCount["Neutral"]++;
    else if (SelectedOption == "D") EmotionCount["Angry"]++;
}

TMap<FString, float> GetEmotionPercentages()
{
    int32 Total = EmotionCount["Happy"] + EmotionCount["Sad"] + EmotionCount["Neutral"] + EmotionCount["Angry"];
    TMap<FString, float> EmotionPercentages;

    for (auto& Elem : EmotionCount)
    {
        EmotionPercentages.Add(Elem.Key, (float)Elem.Value / Total * 100.f);
    }

    return EmotionPercentages;
}