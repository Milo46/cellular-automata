#pragma once    

#include "StaticArray.hpp"

template<typename _StateType>
class SimulationSpace
{
public:
    SimulationSpace(uint32_t width, uint32_t height)
        : m_Space(width* height), m_Width(width), m_Height(height) {}

private:
    StaticArray<_StateType> m_Space;

    uint32_t m_Width;
    uint32_t m_Height;
};
