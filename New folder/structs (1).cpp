USTRUCT()
struct FEmotionOptions
{
    GENERATED_BODY()

    UPROPERTY()
    FString A;
    UPROPERTY()
    FString B;
    UPROPERTY()
    FString C;
    UPROPERTY()
    FString D;
};

USTRUCT()
struct FEmotionQuestion
{
    GENERATED_BODY()

    UPROPERTY()
    int32 id;

    UPROPERTY()
    FString question;

    UPROPERTY()
    FEmotionOptions options;
};
