#pragma once

#include "CoreMinimal.h"
#include "XmlFile.h"
#include "UObject/Object.h"
#include "XmlFileWrapper.generated.h"

class UXmlNodeWrapper;

UCLASS(BlueprintType)
class XMLPARSERWRAPPER_API UXmlFileWrapper : public UObject
{
    GENERATED_BODY()
public:
    UXmlFileWrapper();

    UFUNCTION(BlueprintCallable)
    bool LoadFile(const FString& Path);

    UFUNCTION(BlueprintCallable)
    bool LoadString(const FString& Content);

    /** Clears the file of all internals. Note: Makes any existing pointers to FXmlNode's INVALID */
    UFUNCTION(BlueprintCallable)
    void Clear();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsValid() const;

    /**
     * Returns the root node of the loaded file. nullptr if no file loaded.
     * It is assumed that there will always be one and only one root node.
     * @return						Pointer to root node
     */
    UFUNCTION(BlueprintCallable)
    UXmlNodeWrapper* GetRootNode();

    UFUNCTION(BlueprintCallable)
    bool Save(const FString& Path);

private:
    TUniquePtr<FXmlFile> XmlFile;
};
