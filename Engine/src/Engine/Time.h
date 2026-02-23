#pragma

namespace Engine
{
	class Time
	{
	public:
		static float GetTime();

	private:
		static double m_LastTime;
		static double m_DeltaTime;
	};
}