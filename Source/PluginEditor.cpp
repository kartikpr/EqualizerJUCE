/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 600);

    //Low Shelf frequency
    addAndMakeVisible(knobLowShelf);
    knobLowShelf.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knobLowShelf.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    knobLowShelf.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    knobLowShelf.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
    knobLowShelf.setTextValueSuffix(" Hz");

    auto parameterTree = audioProcessor.getParameters();
    lowShelfc = (juce::AudioParameterFloat*)parameterTree.getUnchecked(0);
    knobLowShelf.setNormalisableRange(juce::NormalisableRange<double>(lowShelfc->range.start, lowShelfc->range.end, 1, 1 / log(20)));
    knobLowShelf.setValue(100, juce::NotificationType::dontSendNotification);
    knobLowShelf.onValueChange = [this] {
        *lowShelfc = knobLowShelf.getValue();

    };


    //Low Shlef Gain
    addAndMakeVisible(knobLowShlefGain);
    knobLowShlefGain.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knobLowShlefGain.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    knobLowShlefGain.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    knobLowShlefGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 50);
    knobLowShlefGain.setTextValueSuffix(" dB");


    lowShelfGain = (juce::AudioParameterFloat*)parameterTree.getUnchecked(1);
    knobLowShlefGain.setRange(lowShelfGain->range.start, lowShelfGain->range.end, lowShelfGain->range.interval);
    knobLowShlefGain.setValue(0, juce::NotificationType::dontSendNotification);
    knobLowShlefGain.onValueChange = [this] {
        *lowShelfGain = knobLowShlefGain.getValue();

    };






    //High Shelf frequency
    addAndMakeVisible(knobHighShelf);
    knobHighShelf.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knobHighShelf.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    knobHighShelf.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    knobHighShelf.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
    knobHighShelf.setTextValueSuffix(" Hz");

    highShelfc = (juce::AudioParameterFloat*)parameterTree.getUnchecked(2);
    knobHighShelf.setNormalisableRange(juce::NormalisableRange<double>(highShelfc->range.start, highShelfc->range.end, 1, 1/log(20)));
    knobHighShelf.setValue(10000, juce::NotificationType::dontSendNotification);
    knobHighShelf.onValueChange = [this] {
        *highShelfc = knobHighShelf.getValue();

    };


    //High Shlef Gain
    addAndMakeVisible(knobHighShelffGain);
    knobHighShelffGain.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knobHighShelffGain.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    knobHighShelffGain.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    knobHighShelffGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 50);
    knobHighShelffGain.setTextValueSuffix(" dB");

    highShelfGain = (juce::AudioParameterFloat*)parameterTree.getUnchecked(3);
    knobHighShelffGain.setRange(highShelfGain->range.start, highShelfGain->range.end, highShelfGain->range.interval);
    knobHighShelffGain.setValue(0, juce::NotificationType::dontSendNotification);
    knobHighShelffGain.onValueChange = [this] {
        *highShelfGain = knobHighShelffGain.getValue();

    };


    //LowPass
    addAndMakeVisible(knobLowPass);
    knobLowPass.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knobLowPass.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    knobLowPass.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    knobLowPass.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
    knobLowPass.setTextValueSuffix(" Hz");

    lowPassfc = (juce::AudioParameterFloat*)parameterTree.getUnchecked(4);
    knobLowPass.setNormalisableRange(juce::NormalisableRange<double>(lowPassfc->range.start, lowPassfc->range.end, 1, 1 / log(20)));
    knobLowPass.setValue(1000, juce::NotificationType::dontSendNotification);
    knobLowPass.onValueChange = [this] {
        *lowPassfc = knobLowPass.getValue();

    };


    //HighPass
    addAndMakeVisible(knobHighPass);
    knobHighPass.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knobHighPass.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    knobHighPass.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    knobHighPass.setTextValueSuffix(" Hz");

    knobHighPass.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
    highPassfc = (juce::AudioParameterFloat*)parameterTree.getUnchecked(5);
    knobHighPass.setNormalisableRange(juce::NormalisableRange<double>(highPassfc->range.start, highPassfc->range.end, 1, 1 / log(20)));
    knobHighPass.setValue(5000, juce::NotificationType::dontSendNotification);
    knobHighPass.onValueChange = [this] {
        *highPassfc = knobHighPass.getValue();

    };



    //Peak


    addAndMakeVisible(knobPeak);
    knobPeak.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knobPeak.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    knobPeak.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    knobPeak.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
    knobPeak.setTextValueSuffix(" Hz");

    peakfc = (juce::AudioParameterFloat*)parameterTree.getUnchecked(6);
    knobPeak.setNormalisableRange(juce::NormalisableRange<double>(peakfc->range.start, peakfc->range.end, 1, 1 / log(20)));
    knobPeak.setValue(100, juce::NotificationType::dontSendNotification);
    knobPeak.onValueChange = [this] {
        *peakfc = knobPeak.getValue();

    };


    //Low Shlef Gain
    addAndMakeVisible(knobPeakGain);
    knobPeakGain.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    knobPeakGain.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    knobPeakGain.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    knobPeakGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 50);
    knobPeakGain.setTextValueSuffix(" dB");

    peakGain = (juce::AudioParameterFloat*)parameterTree.getUnchecked(7);
    knobPeakGain.setRange(peakGain->range.start, peakGain->range.end, peakGain->range.interval);
    knobPeakGain.setValue(0, juce::NotificationType::dontSendNotification);
    knobPeakGain.onValueChange = [this] {
        *peakGain = knobPeakGain.getValue();

    };



    //Gain

    addAndMakeVisible(gainSlider);
    gainParameter = static_cast<juce::AudioParameterFloat*>(parameterTree.getUnchecked(8));


    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 50);
    gainSlider.setTextValueSuffix(" dB");


    gainSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::bisque);
    gainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromRGB(255, 255, 255));

    gainSlider.setRange(gainParameter->range.start, gainParameter->range.end, 0.01);
    gainSlider.onValueChange = [this] {
        *gainParameter = gainSlider.getValue();
    };


    addAndMakeVisible(lowPassText);

    lowPassText.setText("Low Pass CutOff", juce::NotificationType::dontSendNotification);
    lowPassText.setSize(100, 100);


    addAndMakeVisible(lowShelfFreqText);

    lowShelfFreqText.setText("Low Shelf Frequency", juce::NotificationType::dontSendNotification);
    lowShelfFreqText.setSize(100, 100);


    addAndMakeVisible(lowShelfGainText);

    lowShelfGainText.setText("Low Shelf Gain/Cut", juce::NotificationType::dontSendNotification);
    lowShelfGainText.setSize(100, 100);


    addAndMakeVisible(highPassText);

    highPassText.setText("High Pass CutOff", juce::NotificationType::dontSendNotification);
    highPassText.setSize(100, 100);


    addAndMakeVisible(highShelfFreqTest);

    highShelfFreqTest.setText("High Shelf Frequency", juce::NotificationType::dontSendNotification);
    highShelfFreqTest.setSize(100, 100);


    addAndMakeVisible(highShelfGainText);

    highShelfGainText.setText("High Shelf Gain/Cut", juce::NotificationType::dontSendNotification);
    highShelfGainText.setSize(100, 100);


    addAndMakeVisible(peakFreqText);

    peakFreqText.setText("Peak/Notch Frequency", juce::NotificationType::dontSendNotification);
    peakFreqText.setSize(100, 100);


    addAndMakeVisible(peakFreqGainText);

    peakFreqGainText.setText("Peak/Notch Gain", juce::NotificationType::dontSendNotification);
    peakFreqGainText.setSize(100, 100);


    addAndMakeVisible(gainText);

    gainText.setText("Gain", juce::NotificationType::dontSendNotification);
    gainText.setSize(200, 200);


    addAndMakeVisible(lfText);

    lfText.setText("LF", juce::NotificationType::dontSendNotification);
    lfText.setSize(200, 200);
    lfText.setColour(54, juce::Colours::orange);


    addAndMakeVisible(hfText);

    hfText.setText("HF", juce::NotificationType::dontSendNotification);
    hfText.setSize(200, 200);


    addAndMakeVisible(peakText);

    peakText.setText("Peak/Notch", juce::NotificationType::dontSendNotification);
    peakText.setSize(200, 200);







}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::orange);

    juce::Line<float> line(juce::Point<float>(220, 10),
        juce::Point<float>(220, 550));

    juce::Line<float> lineTwo(juce::Point<float>(460, 10),
        juce::Point<float>(460, 550));

    juce::Line<float> lineThree(juce::Point<float>(700, 10),
        juce::Point<float>(700, 550));
    

    

    g.drawLine(line, 2.0f);
    g.drawLine(lineTwo, 2.0f);
    g.drawLine(lineThree, 2.0f);

   
}

void NewProjectAudioProcessorEditor::resized()
{
    auto x = getWidth() / 10;
    auto y = getHeight() / 10;

    knobLowShelf.setBounds(1 * x, 3 * y, 2 * x, 2 * y);
    knobLowShlefGain.setBounds(1 * x, 5 * y, 2 * x, 2 * y);
    lowShelfFreqText.setBounds(0.25 * x, 3 * y, 2 * x, 2 * y);
    lowShelfGainText.setBounds(0.25 * x, 5 * y, 2 * x, 2 * y);




    knobHighShelf.setBounds(4 * x, 3 * y, 2 * x, 2 * y);
    knobHighShelffGain.setBounds(4 * x, 5 * y, 2 * x, 2 * y);
    highShelfFreqTest.setBounds(3.25 * x, 3 * y, 2 * x, 2 * y);
    highShelfGainText.setBounds(3.25 * x, 5 * y, 2 * x, 2 * y);




    lowPassText.setBounds(0.25 * x, 1 * y, 2 * x, 2 * y);
    knobLowPass.setBounds(1 * x, 1 * y, 2 * x, 2 * y);
   
    highPassText.setBounds(3.25 * x, 1 * y, 2 * x, 2 * y);
    knobHighPass.setBounds(4 * x, 1 * y, 2 * x, 2 * y);

    knobPeak.setBounds(7 * x, 1 * y, 2 * x, 2 * y);
    knobPeakGain.setBounds(7 * x, 3 * y, 2 * x, 2 * y);
    peakFreqText.setBounds(6.25 * x, 1 * y, 2 * x, 2 * y);
    peakFreqGainText.setBounds(6.25 * x, 3 * y, 2 * x, 2 * y);

    gainSlider.setBounds(9 * x, 1* y, x, 5 * y);



    gainText.setBounds(9.25 * x, 7* y, x, 5 * y);

    lfText.setBounds(1.25 * x, 7*y, 2 * x, 2 * y);
    hfText.setBounds(4 * x, 7 * y, 2 * x, 2 * y);
    peakText.setBounds(7 * x, 7 * y, 2 * x, 2 * y);


    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
