workspace "GameEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)

IncludeDir = {}
IncludeDir["GLFW"] = "Engine/Dependencies/GLFW/include"
IncludeDir["spdlog"] = "Engine/Dependencies/spdlog/include"

include "Engine/Dependencies/GLFW" -- Same Include as C++ , takes GLFW premake5.lua file and use it 
include "Engine/Dependencies/spdlog"

project "Engine"
    location "Engine"
	kind "StaticLib"
	language "C++"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "enpch.h"
	pchsource "Engine/src/enpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.spdlog}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"spdlog"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		buildoptions 
		{
			"/utf-8"
		}

		defines
		{
			"EN_PLATFORM_WINDOWS",
			"SPDLOG_COMPLIED_LIB"
		}

		buildoptions 
        {
            "/utf-8"
        }

	filter "configurations:Debug"
		defines "EN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EN_RELEASE"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines "EN_DIST"
		optimize "Full"
		symbols "On"

	filter {}


project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.spdlog}",
		"Engine/src"
	}

	links
	{
		"Engine",
		"spdlog",
		"GLFW"
	}

	filter "system:windows"
		staticruntime "On"
		cppdialect "C++20"
		systemversion "latest"

		buildoptions 
		{
			"/utf-8"
		}

		defines
		{
			"EN_PLATFORM_WINDOWS",
			"SPDLOG_COMPILED_LIB"
		}

		buildoptions 
        {
            "/utf-8"
        }


	filter "configurations:Debug"
		defines "EN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EN_RELEASE"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines "EN_DIST"
		optimize "Full"
		symbols "On"

	filter {}	