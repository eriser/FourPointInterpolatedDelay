/*
  ==============================================================================

    HanningWindow.h
    Created: 14 Oct 2015 10:04:50pm
    Author:  Jacob Penn

  ==============================================================================
*/

#ifndef HANNINGWINDOW_H_INCLUDED
#define HANNINGWINDOW_H_INCLUDED

class HanningWindow
{
public: 
    HanningWindow();
    ~HanningWindow();
    void setWindowLength(int sampleRate, float seconds);
    float doHanningWindow(float input, float& logicSwitch);
private:
    const float PI;
    int incrementer;
    int timeInSamples;
    double multiplier;
    
    
};

#endif  // HANNINGWINDOW_H_INCLUDED
