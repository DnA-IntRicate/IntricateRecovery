project "IntricateRecovery"
    kind "ConsoleApp"   -- TODO: In future can make this a library that may be used by other apps, such as in Intricate Engine, or by CLIs
    language "C++"

    debugdir (OUT_DIR)
    targetdir (OUT_DIR)
    objdir (INT_DIR)

    pchsource "irpch.cpp"
    pchheader "irpch.hpp"

    files
    {
        "./irpch.hpp",
        "./irpch.cpp",
        "src/include/**.hpp",
        "src/source/**.cpp"
    }

    includedirs
    {
        ".",
        "src/include"
    }

    libdirs
    {
        OUT_DIR
    }

    bindirs
    {
        OUT_DIR
    }

    filter "files:not src/**.cpp"
        flags
        {
            "NoPCH"
        }

    filter "system:windows"
        cppdialect "C++20"

    filter "system:linux"
        cppdialect "gnu++20"

    filter "system:macosx"
        cppdialect "C++latest"
