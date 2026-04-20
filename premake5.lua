include "Vendor/premake/customization/solutionitems.lua"
include "dependencies.lua"

OUT_DIR = "%{wks.location}/bin/build/%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}/Intricate Recovery"
INT_DIR = "%{wks.location}/bin/intermediate/%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}/%{prj.name}"

workspace "IntricateRecovery"
    architecture "x86_64"
    startproject "IntricateRecovery"
    multiprocessorcompile "On"

    configurations
    {
        "Debug",
        "Dev",
        "Release"
    }

    solutionitems
    {
        ".editorconfig",
        ".gitattributes",
        ".gitignore",
        "raptor.toml"
    }

    defines
    {
        "_CRT_SECURE_NO_DEPRECATE",
        "_CRT_SECURE_NO_WARNINGS",
        "_CRT_NONSTDC_NO_WARNINGS",
        "_SILENCE_ALL_CXX20_DEPRECATION_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "Off"
        defines "INTRICATE_PLATFORM_WINDOWS"

    filter "system:linux"
        systemversion "latest"
        pic "On"
        staticruntime "Off"
        defines "INTRICATE_PLATFORM_LINUX"

    filter "system:macosx"
        systemversion "latest"
        pic "On"
        staticruntime "Off"
        defines "INTRICATE_PLATFORM_OSX"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "Full"

        defines
        {
            "INTRICATE_DEBUG",
            "_DEBUG"
        }

    filter "configurations:Dev"
        runtime "Release"
        symbols "On"
        optimize "On"

        defines
        {
            "INTRICATE_DEV",
            "NDEBUG"
        }

    filter "configurations:Release"
        runtime "Release"
        symbols "Off"
        optimize "Full"
        linktimeoptimization "On"
        incrementallink "Off"
        buffersecuritycheck "Off"
        runtimechecks "Off"

        defines
        {
            "INTRICATE_RELEASE",
            "NDEBUG"
        }

include "IntricateRecovery"
