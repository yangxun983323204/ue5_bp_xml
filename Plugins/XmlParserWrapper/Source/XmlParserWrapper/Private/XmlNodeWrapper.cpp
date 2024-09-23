#include "XmlNodeWrapper.h"

UXmlAttributeWrapper* UXmlAttributeWrapper::Create(const FString& InTag, const FString& InValue)
{
    auto Inst = NewObject<UXmlAttributeWrapper>();
    Inst->AttributePtr = new FXmlAttribute(InTag, InValue);
    Inst->bIsExternal = false;
    return Inst;
}

UXmlAttributeWrapper* UXmlAttributeWrapper::CreateFromExternalPtr(FXmlAttribute* NativeAttribute)
{
    if(NativeAttribute == nullptr)
        return nullptr;

    auto Inst = NewObject<UXmlAttributeWrapper>();
    Inst->AttributePtr = NativeAttribute;
    Inst->bIsExternal = true;
    return Inst;
}

void UXmlAttributeWrapper::BeginDestroy()
{
    UObject::BeginDestroy();
    if (!bIsExternal)
    {
        delete AttributePtr;
    }
    AttributePtr = nullptr;
}

const FString& UXmlAttributeWrapper::GetTag() const
{
    return AttributePtr->GetTag();
}

const FString& UXmlAttributeWrapper::GetValue() const
{
    return AttributePtr->GetValue();
}




UXmlNodeWrapper* UXmlNodeWrapper::CreateFromExternalPtr(FXmlNode* NativeNode)
{
    if(NativeNode == nullptr)
        return nullptr;

    auto Inst = NewObject<UXmlNodeWrapper>();
    Inst->NodePtr = NativeNode;
    return Inst;
}

void UXmlNodeWrapper::BeginDestroy()
{
    UObject::BeginDestroy();
    NodePtr = nullptr;
}

UXmlNodeWrapper* UXmlNodeWrapper::GetNextNode()
{
    auto Node = const_cast<FXmlNode*>(NodePtr->GetNextNode());
    return UXmlNodeWrapper::CreateFromExternalPtr(Node);
}

TArray<UXmlNodeWrapper*> UXmlNodeWrapper::GetChildrenNodes()
{
    auto NativeArray = NodePtr->GetChildrenNodes();
    TArray<UXmlNodeWrapper*> WrapperArray{};
    for(auto* Node : NativeArray)
    {
        auto Wrapper = CreateFromExternalPtr(Node);
        WrapperArray.Add(Wrapper);
    }

    return WrapperArray;
}

UXmlNodeWrapper* UXmlNodeWrapper::GetFirstChildNode()
{
    auto Node = const_cast<FXmlNode*>(NodePtr->GetFirstChildNode());
    return CreateFromExternalPtr(Node);
}

UXmlNodeWrapper* UXmlNodeWrapper::GetLastChildNode()
{
    auto Node = const_cast<FXmlNode*>(NodePtr->GetFirstChildNode());
    while (Node->GetNextNode() != nullptr)
    {
        Node = const_cast<FXmlNode*>(Node->GetNextNode());
    }

    return CreateFromExternalPtr(Node);
}

int UXmlNodeWrapper::GetChildrenCount()
{
    return NodePtr->GetChildrenNodes().Num();
}

UXmlNodeWrapper* UXmlNodeWrapper::GetChildNodeAt(int Idx)
{
    if(Idx<0 || Idx>=GetChildrenCount())
        return nullptr;

    return CreateFromExternalPtr(NodePtr->GetChildrenNodes()[Idx]);
}

UXmlNodeWrapper* UXmlNodeWrapper::FindChildNode(const FString& InTag)
{
    return CreateFromExternalPtr(NodePtr->FindChildNode(InTag));
}

const FString& UXmlNodeWrapper::GetTag()
{
    return NodePtr->GetTag();
}

const FString& UXmlNodeWrapper::GetContent()
{
    return NodePtr->GetContent();
}

void UXmlNodeWrapper::SetContent(const FString& InContent)
{
    NodePtr->SetContent(InContent);
}

void UXmlNodeWrapper::SetAttributes(const TArray<UXmlAttributeWrapper*>& InAttributes)
{
    TArray<FXmlAttribute> AttrArray{};
    for(auto Wrapper : InAttributes)
    {
        AttrArray.Add(*Wrapper->GetPtr());
    }
    NodePtr->SetAttributes(AttrArray);
}

const TArray<UXmlAttributeWrapper*> UXmlNodeWrapper::GetAttributes()
{
    TArray<UXmlAttributeWrapper*> Wrappers{};
    auto AttrArray = NodePtr->GetAttributes();
    for(auto Attr : AttrArray)
    {
        auto Wrapper = UXmlAttributeWrapper::CreateFromExternalPtr(&Attr);
        Wrappers.Add(Wrapper);
    }
    return Wrappers;
}

FString UXmlNodeWrapper::GetAttribute(const FString& InTag)
{
    return NodePtr->GetAttribute(InTag);
}

void UXmlNodeWrapper::AppendChildNode(const FString& InTag)
{
    NodePtr->AppendChildNode(InTag);
}
