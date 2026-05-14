project "Editor"
	location "."
	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	debugdir "%{wks.location}"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"../Engine/src",
		"../Engine/Dependencies/GLFW/include",
		"../Engine/Dependencies/spdlog/include",
		"../Engine/Dependencies/glad/include",
		"../Engine/Dependencies/glm",
		"../Engine/Dependencies/stb",
		"../Engine/Dependencies/json",
		"../Engine/Dependencies/ImGui"
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
			"SPDLOG_COMPILED_LIB"
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
