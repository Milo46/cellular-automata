project "cellular-automata"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.cpp",
        "src/**.hpp",
        "src/**.h",
    }

    filter { "configurations:Debug" }
        --buildoptions "/MTd"
        runtime "Debug"

    filter { "configurations:Release" }
        --buildoptions "/MT"
        runtime "Release"
