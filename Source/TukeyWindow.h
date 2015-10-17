/*
  ==============================================================================

    TukeyWindow.h
    Created: 16 Oct 2015 9:55:30pm
    Author:  Jacob Penn

  ==============================================================================
*/

#ifndef TUKEYWINDOW_H_INCLUDED
#define TUKEYWINDOW_H_INCLUDED

class TukeyWindow
{
public:
    TukeyWindow();
    ~TukeyWindow();
    void setWindowLength(int sampleRate, float seconds);
    float doTukeyWindow(float input, float& logicSwitch);
private:
    const float PI;
    int incrementer;
    int timeInSamples;
    double multiplier;
    
    
};



#endif  // TUKEYWINDOW_H_INCLUDED
