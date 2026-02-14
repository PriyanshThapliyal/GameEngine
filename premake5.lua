workspace "GameEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

project "Engine"
    location "Engine"
	kind "StaticLib"
	language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/dependencies/GLFW/include"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EN_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "EN_DIST"
		symbols "On"


project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"Engine/dependencies/GLFW/include",
		"Engine/src"
	}

	links
	{
		"Engine"
	}