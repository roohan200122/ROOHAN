TArray<FEmotionQuestion> LoadQuestionsFromJson()
{
    TArray<FEmotionQuestion> Questions;

    FString JsonPath = FPaths::ProjectContentDir() + "Data/EmotionQuestions.json";
    FString JsonRaw;

    if (FFileHelper::LoadFileToString(JsonRaw, *JsonPath))
    {
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonRaw);
        TArray<TSharedPtr<FJsonValue>> JsonArray;

        if (FJsonSerializer::Deserialize(Reader, JsonArray))
        {
            for (const TSharedPtr<FJsonValue>& Value : JsonArray)
            {
                TSharedPtr<FJsonObject> Obj = Value->AsObject();
                FEmotionQuestion Q;
                Q.id = Obj->GetIntegerField("id");
                Q.question = Obj->GetStringField("question");

                TSharedPtr<FJsonObject> Opt = Obj->GetObjectField("options");

                Q.options.A = Opt->GetStringField("A");
                Q.options.B = Opt->GetStringField("B");
                Q.options.C = Opt->GetStringField("C");
                Q.options.D = Opt->GetStringField("D");

                Questions.Add(Q);
            }
        }
    }

    return Questions;
}