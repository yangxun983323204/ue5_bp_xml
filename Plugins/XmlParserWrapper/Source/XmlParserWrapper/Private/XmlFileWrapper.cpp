#include "XmlFileWrapper.h"

#include "XmlNodeWrapper.h"

UXmlFileWrapper::UXmlFileWrapper()
{
    XmlFile = MakeUnique<FXmlFile>();
}

bool UXmlFileWrapper::LoadFile(const FString& Path)
{
    return XmlFile->LoadFile(Path, EConstructMethod::Type::ConstructFromFile);
}

bool UXmlFileWrapper::LoadString(const FString& Content)
{
    return XmlFile->LoadFile(Content, EConstructMethod::Type::ConstructFromBuffer);
}

void UXmlFileWrapper::Clear()
{
    XmlFile->Clear();
}

bool UXmlFileWrapper::IsValid() const
{
    return XmlFile->IsValid();
}

UXmlNodeWrapper* UXmlFileWrapper::GetRootNode()
{
    return UXmlNodeWrapper::CreateFromExternalPtr(XmlFile->GetRootNode());
}

bool UXmlFileWrapper::Save(const FString& Path)
{
    return XmlFile->Save(Path);
}
