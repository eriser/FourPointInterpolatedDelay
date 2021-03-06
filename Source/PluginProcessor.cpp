/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "FourPointDelay.h"
#include "FourPointInterpolate.h"
#include <string.h>


//==============================================================================
FourPointDelayAudioProcessor::FourPointDelayAudioProcessor() : m_knob1(0),
                                                               m_knob2(0),
                                                               m_knob3(0),
                                                               m_fRunWindowL(0),
                                                               m_fRunWindowR(0)
{
    
    m_fFeedback = 0;
    m_fWetLevel = 0;
    
    m_fDelayTime = m_knob1;
    m_fFeedback = m_knob2;
    m_fWetLevel = m_knob3;
    
    FourPDelayL = FourPointDelay();
    FourPDelayL.setMaxDelay(m_sampleRate, 1.0);
    FourPDelayL.setDelayTime(m_sampleRate, m_fDelayTime);
    FourPDelayL.setWetMix(m_fWetLevel);
    FourPDelayL.setFeedback(m_fFeedback);
    FourPDelayL.setPlayheads();
    
    FourPDelayR = FourPointDelay();
    FourPDelayR.setMaxDelay(m_sampleRate, 1.0);
    FourPDelayR.setDelayTime(m_sampleRate, m_fDelayTime);
    FourPDelayR.setWetMix(m_fWetLevel);
    FourPDelayR.setFeedback(m_fFeedback);
    FourPDelayR.setPlayheads();
    
    m_fRunWindowL = 0;
    m_fRunWindowR = 0;
    //std::cout << "Run Window = " << m_fRunWindow << std::endl;
}

FourPointDelayAudioProcessor::~FourPointDelayAudioProcessor()
{
}


//==============================================================================
const String FourPointDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int FourPointDelayAudioProcessor::getNumParameters()
{
    return totalNumParams;
}

float FourPointDelayAudioProcessor::getParameter (int index)
{
    switch (index) {
        case knob1Param: return m_knob1;
        case knob2Param: return m_knob2;
        case knob3Param: return m_knob3;
        case runWindowParam: return m_fRunWindowL;
        default: return 0.0;
    }
}

void FourPointDelayAudioProcessor::setParameter (int index, float newValue)
{
    switch (index) {
            //Delay Time Knob
        case knob1Param: m_knob1 = newValue;
           m_fDelayTime = m_knob1;
            
            FourPDelayL.setDelayTime(m_sampleRate, m_fDelayTime);
            FourPDelayL.setPlayheads();
            
            FourPDelayR.setDelayTime(m_sampleRate, m_fDelayTime);
            FourPDelayR.setPlayheads();break;
            //Feedback Knob
        case knob2Param: m_knob2 = newValue;
            m_fFeedback = m_knob2;
            FourPDelayL.setFeedback(m_fFeedback);
            FourPDelayR.setFeedback(m_fFeedback);break;
            //Mix Knob
        case knob3Param: m_knob3 = newValue;
            m_fWetLevel = m_knob3;
            FourPDelayL.setWetMix(m_fWetLevel);
            FourPDelayR.setWetMix(m_fWetLevel); break;
            //Run Window
        case runWindowParam: m_fRunWindowL = 1;
            m_fRunWindowR = 1;
            //std::cout << "Run Window = " << m_fRunWindow << std::endl;
        default: break;
    }
}

const String FourPointDelayAudioProcessor::getParameterName (int index)
{
    switch (index){
        case knob1Param: return "Delay Time";
        case knob2Param: return "Feedback";
        case knob3Param: return "Dry / Wet";
        case runWindowParam: return "Run Window";
        default: return String::empty;
    }
}

const String FourPointDelayAudioProcessor::getParameterText (int index)
{
    return String(getParameter(index),2);
}

const String FourPointDelayAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String FourPointDelayAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool FourPointDelayAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool FourPointDelayAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool FourPointDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FourPointDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FourPointDelayAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double FourPointDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FourPointDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FourPointDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FourPointDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String FourPointDelayAudioProcessor::getProgramName (int index)
{
    return String();
}

void FourPointDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FourPointDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    m_sampleRate = sampleRate;
    m_fDelayTime = m_knob1;
    m_fFeedback = m_knob2;
    m_fWetLevel = m_knob3;
    
    FourPDelayL.setMaxDelay(m_sampleRate, 1.0);
    FourPDelayL.setDelayTime(m_sampleRate, m_fDelayTime);
    FourPDelayL.setWetMix(m_fWetLevel);
    FourPDelayL.setFeedback(m_fFeedback);
    FourPDelayL.prepareToPlay();
    FourPDelayL.setPlayheads();
    
    FourPDelayR.setMaxDelay(m_sampleRate, 1.0);
    FourPDelayR.setDelayTime(m_sampleRate, m_fDelayTime);
    FourPDelayR.setWetMix(m_fWetLevel);
    FourPDelayR.setFeedback(m_fFeedback);
    FourPDelayR.prepareToPlay();
    FourPDelayR.setPlayheads();
    
    m_fRunWindowL = 0;
    m_fRunWindowR = 0;
    HanningWindowL.setWindowLength(sampleRate, 2);
    HanningWindowR.setWindowLength(sampleRate, 2);
    TukeyWindowL.setWindowLength(sampleRate, .02);
    TukeyWindowR.setWindowLength(sampleRate, .02);
    
    
    //m_fDelayTimeZ = m_fDelayTime;
    
    //std::cout << "Run Window = " << m_fRunWindow << std::endl;
}

void FourPointDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void FourPointDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < getNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        
        for ( int i = 0; i < buffer.getNumSamples(); i++ )
        {

            if(channel == 0)
            {
                channelData[i] = FourPDelayL.process(channelData[i]);
                channelData[i] = TukeyWindowL.doTukeyWindow(channelData[i], m_fRunWindowL);
            }
            else if(channel == 1)
            {
                channelData[i] = FourPDelayR.process(channelData[i]);
                channelData[i] = TukeyWindowR.doTukeyWindow(channelData[i], m_fRunWindowR);
            }
        }
    }
    

    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
}

//==============================================================================
bool FourPointDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FourPointDelayAudioProcessor::createEditor()
{
    return new FourPointDelayAudioProcessorEditor (*this);
}

//==============================================================================
void FourPointDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FourPointDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FourPointDelayAudioProcessor();
}
