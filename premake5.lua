workspace "cellular-automata"
    startproject "cellular-automata"
    systemversion "latest"
    system "windows"

    defines {
        "WINDOWS",
        "GAME_PLATFORM_WINDOWS"
    }

    configurations {
        "Debug",
        "Release"
    }

    platforms {
        "Win32",
        "Win64",
    }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "on"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "on"

    filter { "platforms:Win32" }
        defines { "WINDOWS32" }
        architecture "x86"

    filter { "platforms:Win64" }
        defines { "WINDOWS64" }
        architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "cellular-automata"
