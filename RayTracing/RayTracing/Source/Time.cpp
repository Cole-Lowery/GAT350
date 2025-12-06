#include "Time.h"

    void Time::Tick()
    {
        // Capture the current high-resolution time point
        clock::time_point now = clock::now();

        // Calculate total elapsed time since start/reset
        // Convert from chrono duration to float seconds
        m_time = std::chrono::duration<float>(now - m_startTime).count();

        // Calculate time elapsed since last frame
        // This gives us the unscaled delta time in seconds
        m_deltaTime = std::chrono::duration<float>(now - m_frameTime).count();

        // Update frame time for next delta calculation
        // Store current time as the reference point for the next frame
        m_frameTime = now;
    }
