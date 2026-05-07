#pragma once

#include <string>

namespace Engine
{
	class TagComponent
	{
		public:
			std::string Tag;
		
			TagComponent() = default;

			TagComponent(const std::string tag)
				: Tag(tag) {}
	};
}