#pragma once

#include "CoreMinimal.h"
#include "XmlNode.h"
#include "UObject/Object.h"
#include "XmlNodeWrapper.generated.h"


UCLASS(BlueprintType)
class XMLPARSERWRAPPER_API UXmlAttributeWrapper : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static UXmlAttributeWrapper* Create(const FString& InTag, const FString& InValue);
    static UXmlAttributeWrapper* CreateFromExternalPtr(FXmlAttribute* NativeAttribute);
    void BeginDestroy() override;

    UFUNCTION(BlueprintCallable, BlueprintPure)
    const FString& GetTag() const;

    UFUNCTION(BlueprintCallable, BlueprintPure)
    const FString& GetValue() const;

    inline FXmlAttribute* GetPtr(){return AttributePtr;}
private:
    FXmlAttribute* AttributePtr;
    bool bIsExternal;
};

UCLASS(BlueprintType)
class XMLPARSERWRAPPER_API UXmlNodeWrapper : public UObject
{
    GENERATED_BODY()
public:
    static UXmlNodeWrapper* CreateFromExternalPtr(FXmlNode* NativeNode);
    void BeginDestroy() override;

    UFUNCTION(BlueprintCallable, BlueprintPure)
    UXmlNodeWrapper* GetNextNode();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<UXmlNodeWrapper*> GetChildrenNodes();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    UXmlNodeWrapper* GetFirstChildNode();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    UXmlNodeWrapper* FindChildNode(const FString& InTag);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    const FString& GetTag();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    const FString& GetContent();

    UFUNCTION(BlueprintCallable)
    void SetContent(const FString& InContent);

    UFUNCTION(BlueprintCallable)
    void SetAttributes(const TArray<UXmlAttributeWrapper*>& InAttributes);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    const TArray<UXmlAttributeWrapper*> GetAttributes();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    FString GetAttribute(const FString& InTag);

    UFUNCTION(BlueprintCallable)
    void AppendChildNode(const FString& InTag);

private:
    FXmlNode* NodePtr;
};
