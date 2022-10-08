/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    //Low shelf frequency
    knobLowShelf = new juce::AudioParameterFloat("1", "Knob Low Shelf", 0, 24000, 100);
    addParameter(knobLowShelf);

    //Low shelf Gain
    lowShelfGain = new juce::AudioParameterFloat("2", "Gain Low shelf", -10, 10, 0);
    addParameter(lowShelfGain);

    //High Shelf Freq
    knobHighShelf = new juce::AudioParameterFloat("3", "Knob High Shelf", 0, 24000, 10000);
    addParameter(knobHighShelf);

    //High Shelf Gain
    highShelfGain = new juce::AudioParameterFloat("4", "Gain Low shelf", -10, 10, 0);
    addParameter(highShelfGain);


    //LowPass
    lowPass  = new juce::AudioParameterFloat("5", "Knob Low Pass", 0, 24000, 1000);
    addParameter(lowPass);

    //HighPass
    highPass = new juce::AudioParameterFloat("6", "Knob High Pass", 0, 24000, 5000);
    addParameter(highPass);

    peakFreq = new juce::AudioParameterFloat("7", "Knob Peak Freq", 0, 24000, 100);
    addParameter(peakFreq);

    //High Shelf Gain
    peakGain = new juce::AudioParameterFloat("8", "Knob Peak Gain", -10, 10, 0);
    addParameter(peakGain);


    gainParameter = new juce::AudioParameterFloat("9", "Gain", -24, 12, 0);
    addParameter(gainParameter);


}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    lowShelfL.setSampleRate(sampleRate);
    lowShelfR.setSampleRate(sampleRate);

    highShelfL.setSampleRate(sampleRate);
    highShelfR.setSampleRate(sampleRate);


    lowPassL.setSampleRate(sampleRate);
    lowPassR.setSampleRate(sampleRate);

    highPassL.setSampleRate(sampleRate);
    highPassR.setSampleRate(sampleRate);

    peakL.setSampleRate(sampleRate);
    peakR.setSampleRate(sampleRate);

}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewProjectAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    lowShelfL.setParameters(2 * (*knobLowShelf), 0, *lowShelfGain, "lowshelf");

    lowShelfR.setParameters(2 * (*knobLowShelf), 0, *lowShelfGain, "lowshelf");

    highShelfL.setParameters(2 * (*knobHighShelf), 0, *highShelfGain, "highshelf");

    highShelfR.setParameters(2 * (*knobHighShelf), 0, *highShelfGain, "highshelf");

    lowPassL.setParameters(2 * (*lowPass), 0, 0 , "lowpass");

    lowPassR.setParameters(2 * (*lowPass), 0, 0, "lowpass");

    highPassL.setParameters(2 * (*highPass), 0, 0, "highpass");

    highPassR.setParameters(2 * (*highPass), 0, 0, "highpass");

    peakL.setParameters(2 * (*peakFreq), 2500, *peakGain, "peak");

    peakR.setParameters(2 * (*peakFreq), 2500, *peakGain, "peak");


    for (int i = 0; i < buffer.getNumSamples(); i++) {

    }
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.





    for (uint32_t i = 0; i < buffer.getNumChannels(); i++) {

        for (uint32_t j = 0; j < buffer.getNumSamples(); j++) {
            if (i == 0) {
                buffer.setSample(0, j, lowShelfL.processAudioSample(buffer.getSample(0, j)));
               buffer.setSample(0, j, highShelfL.processAudioSample(buffer.getSample(0, j)));

                buffer.setSample(0, j, lowPassL.processAudioSample(buffer.getSample(0, j)));
               buffer.setSample(0, j, highPassL.processAudioSample(buffer.getSample(0, j)));

               buffer.setSample(0, j, peakL.processAudioSample(buffer.getSample(0, j)));







            }
            else if (i == 1) {
                buffer.setSample(1, j, lowShelfR.processAudioSample(buffer.getSample(1, j)));
               buffer.setSample(1, j, highShelfR.processAudioSample(buffer.getSample(1, j)));


               buffer.setSample(1, j, lowPassR.processAudioSample(buffer.getSample(1, j)));
               buffer.setSample(1, j, highPassR.processAudioSample(buffer.getSample(1, j)));

               buffer.setSample(1, j, peakR.processAudioSample(buffer.getSample(1, j)));








            }
            float gain = powf(10, *gainParameter / 20);
            buffer.setSample(i, j, buffer.getSample(i, j) * gain);

        }
    }
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
