workspace "cellular-automata"
    architecture "x64"
    startproject "cellular-automata"

    configurations {
        "Debug",
        "Release"
    }

    platforms {
        "Win32",
        "Win64",
        "Unix",
        "Mac"
    }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "on"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "on"

    filter { "platforms:Win32" }
        system "windows"
        defines { "WINDOWS", "WINDOWS32" }
        architecture "x86"
        systemversion "latest"

    filter { "platforms:Win64" }
        system "windows"
        defines { "WINDOWS", "WINDOWS64" }
        systemversion "latest"

    filter { "platforms:Unix" }
        system "linux"
        defines { "LINUX" }

    filter { "platforms:Mac" }
        system "macosx"
        defines { "MACOSX" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "cellular-automata"
