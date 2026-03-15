#pragma once

#include <memory>

// Only define it if the build system hasn't already!
#ifndef SPDLOG_COMPILED_LIB
	#define SPDLOG_COMPILED_LIB
#endif

#include "spdlog/spdlog.h" 

namespace Engine {
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#ifdef EN_DEBUG
	// Core log macros
	#define EN_CORE_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define EN_CORE_INFO(...)  ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define EN_CORE_WARN(...)  ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define EN_CORE_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define EN_CORE_FATAL(...) ::Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)
	// Client log macros
	#define EN_TRACE(...) ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define EN_INFO(...)  ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
	#define EN_WARN(...)  ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define EN_ERROR(...) ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
	#define EN_FATAL(...) ::Engine::Log::GetClientLogger()->critical(__VA_ARGS__)
#else 	
	#define EN_CORE_TRACE(...)
	#define EN_CORE_INFO(...)
	#define EN_CORE_WARN(...)
	#define EN_CORE_ERROR(...)
	#define EN_CORE_FATAL(...)

	#define EN_TRACE(...)
	#define EN_INFO(...)
	#define EN_WARN(...)
	#define EN_ERROR(...)
	#define EN_FATAL(...)
#endif