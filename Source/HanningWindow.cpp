/*
  ==============================================================================

    HanningWindow.cpp
    Created: 14 Oct 2015 10:04:50pm
    Author:  Jacob Penn

  ==============================================================================
*/

#include "HanningWindow.h"
#include "../JuceLibraryCode/JuceHeader.h"

HanningWindow::HanningWindow(): PI(3.14159265359),
                                incrementer(0),
                                timeInSamples(0),
                                multiplier(0)
{
}
HanningWindow::~HanningWindow(){}

void HanningWindow::setWindowLength(int sampleRate, float seconds)
{
    timeInSamples = sampleRate * seconds;
}

float HanningWindow::doHanningWindow(float input, float& logicSwitch)
{
    if (logicSwitch == 1)
    {
        multiplier = 0.5 * (1-cos((2*PI*incrementer)/(timeInSamples-1)));
        incrementer++;
        //std::cout << multiplier << std::endl;
    
        if (incrementer == timeInSamples)
        {
            logicSwitch = 0;
            incrementer = 0;
        }
        return input * multiplier;
    }
    if (logicSwitch == 0)
    {
        return input * 0;
    }
    else
    {
        return input * 0;
    }
    
}
