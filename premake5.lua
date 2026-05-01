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
IncludeDir["glad"] = "Engine/Dependencies/glad/include"
IncludeDir["glm"] = "Engine/Dependencies/glm"
IncludeDir["stb"] = "Engine/Dependencies/stb"
IncludeDir["json"] = "Engine/Dependencies/json"

include "Engine/Dependencies/GLFW" -- Same Include as C++ , takes GLFW premake5.lua file and use it 
include "Engine/Dependencies/spdlog"
include "Engine/Dependencies/glad"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/.hpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.json}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"spdlog",
		"glad"
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
	
	debugdir "%{wks.location}"

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glad}",
		"Engine/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
	}

	links
	{
		"Engine",
		"spdlog",
		"GLFW",
		"glad"
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
			"SPDLOG_COMPILED_LIB",
			"STB_IMAGE_IMPLEMENTATION"
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
		debugdir "%{wks.location}"