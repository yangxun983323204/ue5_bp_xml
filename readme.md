# UE5蓝图使用XML
plugin中的插件是对UE XmlParser的包装，以暴露接口给蓝图使用。  
没有用蓝图测试，不过用AngelScript脚本测试了下，理论上蓝图也是可用的：  
```
// 测试对UE XmlParse模块的蓝图导出
class ATest_XmlParserWrapper_AS : AActor
{
    FString XmlStr = """
    <?xml version="1.0" encoding="UTF-8"?>
    <site>
        <name>RUNOOB</name>
        <url>https://www.runoob.com</url>
        <logo>runoob-logo.png</logo>
        <desc>编程学习网站</desc>
        <li>
            <item id="0">Item0</item>
            <item id="1">Item1</item>
            <item id="2">Item2</item>
        </li>
    </site>
    """;

    UFUNCTION(CallInEditor)
    void Parse()
    {
        UXmlFileWrapper XmlFile = Cast<UXmlFileWrapper>(NewObject(nullptr, UXmlFileWrapper::StaticClass()));
        XmlFile.LoadString(XmlStr);
        auto RootNode = XmlFile.GetRootNode();
        auto NameNode = RootNode.FindChildNode("name");
        auto UrlNode = RootNode.FindChildNode("url");
        auto LogoNode = RootNode.FindChildNode("logo");
        auto DescNode = RootNode.FindChildNode("desc");
        auto ListNode = RootNode.FindChildNode("li");
        auto ItemNodeArray = ListNode.GetChildrenNodes();

        Log(f"{RootNode.Tag}:{RootNode.Content}");
        Log(f"{NameNode.Tag}:{NameNode.Content}");
        Log(f"{UrlNode.Tag}:{UrlNode.Content}");
        Log(f"{LogoNode.Tag}:{LogoNode.Content}");
        Log(f"{DescNode.Tag}:{DescNode.Content}");
        Log(f"{ListNode.Tag}:{ListNode.Content}");

        for(auto ItemNode : ItemNodeArray)
        {
            auto Id = ItemNode.GetAttribute("id");
            Log(f"{ItemNode.Tag}:{ItemNode.Content}    id={Id}");
        }
    }

    UFUNCTION(CallInEditor)
    void Save()
    {
        UXmlFileWrapper XmlFile = Cast<UXmlFileWrapper>(NewObject(nullptr, UXmlFileWrapper::StaticClass()));
        XmlFile.LoadString("<site></site>");
        auto RootNode = XmlFile.GetRootNode();
        RootNode.AppendChildNode("name");
        RootNode.AppendChildNode("desc");
        RootNode.AppendChildNode("li");

        auto NameNode = RootNode.FindChildNode("name");
        NameNode.SetContent("axun");
        auto DescNode = RootNode.FindChildNode("desc");
        DescNode.SetContent("test my xmlparser wrapper");
        auto ListNode = RootNode.FindChildNode("li");

        for(int Idx = 0; Idx<3; ++Idx)
        {
            ListNode.AppendChildNode("item");
        }

        auto ItemNodes = ListNode.GetChildrenNodes();
        for(int Idx = 0; Idx<ItemNodes.Num(); ++Idx)
        {
            ItemNodes[Idx].SetContent(f"Item{Idx}");
            TArray<UXmlAttributeWrapper> Attrs;
            Attrs.Add(UXmlAttributeWrapper::Create("id", f"{Idx}"));
            ItemNodes[Idx].SetAttributes(Attrs);
        }

        FString Path = "d:/ue_test.xml";
        XmlFile.Save(Path);
        Log(f"Save:{Path}");
    }
};
```