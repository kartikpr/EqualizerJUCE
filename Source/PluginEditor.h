/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;
    juce::Slider knobLowShelf;
    juce::AudioParameterFloat* lowShelfc;

    juce::Slider knobLowShlefGain;
    juce::AudioParameterFloat* lowShelfGain;

    juce::Slider knobHighShelf;
    juce::AudioParameterFloat* highShelfc;

    juce::Slider knobHighShelffGain;
    juce::AudioParameterFloat* highShelfGain;


    juce::Slider knobLowPass;
    juce::AudioParameterFloat* lowPassfc;

    juce::Slider knobHighPass;
    juce::AudioParameterFloat* highPassfc;

    juce::Slider knobPeak;
    juce::AudioParameterFloat* peakfc;

    juce::Slider knobPeakGain;
    juce::AudioParameterFloat* peakGain;

    juce::Slider gainSlider;
    juce::AudioParameterFloat* gainParameter;

    juce::Label lowPassText;
    juce::Label lowShelfFreqText;
    juce::Label lowShelfGainText;

    juce::Label highPassText;
    juce::Label highShelfFreqTest;
    juce::Label highShelfGainText;

    juce::Label peakFreqText;
    juce::Label peakFreqGainText;


    juce::Label gainText;
    juce::Label lfText;
    juce::Label hfText;
    juce::Label peakText;
    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
