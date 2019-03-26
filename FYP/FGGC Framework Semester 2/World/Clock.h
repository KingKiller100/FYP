#pragma once
#include <chrono>


template<class TimeType = std::chrono::milliseconds> 
class Clock final
{
typedef std::chrono::high_resolution_clock HighResolution;
public:
	Clock() = default;
	~Clock() = default;

	static double GetElapsedTime()
	{
		prevTime = currentTime;
		currentTime = HighResolution::now();

		const auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - prevTime).count();

		return elapsedTime;
	}
	
private:
	static HighResolution::time_point prevTime;
	static HighResolution::time_point currentTime;
};

std::chrono::high_resolution_clock::time_point Clock<>::prevTime = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point Clock<>::currentTime = std::chrono::high_resolution_clock ::now();

