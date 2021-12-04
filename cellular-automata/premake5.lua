project "cellular-automata"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int/" .. outputdir .. "/%{prj.name}")

    defines {
        "SFML_STATIC"
    }

    files {
        "src/**.cpp",
        "src/**.hpp",
        "src/**.h",
    }

    includedirs {
        "src",
        "../vendor/SFML/include"
    }

    filter { "platforms:Win32" }
        libdirs {
            "../vendor/SFML/lib32"
        }

    filter { "platforms:Win64" }
        libdirs {
            "../vendor/SFML/lib64"
        }

    filter { "configurations:Debug" }
        --buildoptions "/MDd"
        runtime "Debug"

        links {
            "sfml-audio-s-d.lib",
            "sfml-graphics-s-d.lib",
            "sfml-network-s-d.lib",
            "sfml-system-s-d.lib",
            "sfml-window-s-d.lib"
        }

    filter { "configurations:Release" }
        --buildoptions "/MD"
        runtime "Release"

        links {
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-network-s.lib",
            "sfml-system-s.lib",
            "sfml-window-s.lib"
        }

    links { --SFML libraries
        "opengl32.lib",
        "freetype.lib",
        "winmm.lib",
        "gdi32.lib",
        "openal32.lib",
        "flac.lib",
        "vorbisenc.lib",
        "vorbisfile.lib",
        "vorbis.lib",
        "ogg.lib",
        "ws2_32.lib"
    }
