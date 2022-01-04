#include <MIDI.h>
#include <FastLED.h>

#define NUM_LEDS 81
#define DATA_PIN 13
#define NUMKEYS 88
#define OFFSET 21
float midi2leds = 0.9205; //calculated from 1/NUMKEYS * NUM_LEDS. Probably better to just do 1/NUMKEYS*NUM_LEDS but didn't get a good result with that so hard coding for now.
CRGBArray<NUM_LEDS> leds; //create CRGBSet
MIDI_CREATE_DEFAULT_INSTANCE(); // Create a MIDI instance to listen to UART for Midi messages
void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  MIDI.begin(); // Starts listening
  MIDI.setHandleNoteOn(TurnOnLeds); //callback when mcu receives NoteOn Message
  MIDI.setHandleNoteOff(TurnOffLeds); //callback when mcu receives NoteOff Message

}

void loop() {
  MIDI.read(); // This needs to be run as often as possible to not get too delayed from the actual key being presed
}



int Find_Center(int note){
  //Finds the pixel which should about line up with the key being pressed, Leds and keys dont line up exactly, But when physical length of keyboard and strip is about equal should line up well enough
  int center = round(note * midi2leds );
  return center;
}

void TurnOnLeds(byte channel, byte pitch, byte velocity){
  int cent = round(int(pitch-21) * midi2leds ); // Also works just as well like this, just doesn't look as pretty imo
  if (cent<=0.3333333*NUM_LEDS){ // changes colour of the led based on which third of the keyboard a key is being pressed, bass notes are blue, middle is green, and high notes are red
    leds(cent-1,cent+1) = CRGB::Blue;
  }
  else if (cent<=0.6666666*NUM_LEDS){
    leds(cent-1,cent+1) = CRGB::Green;
  }
  else{
    leds(cent-1,cent+1) = CRGB::Red;
  }
  FastLED.show();
}

void TurnOffLeds(byte channel, byte pitch, byte velocity){
  int cente = round(int(pitch-21) * midi2leds ); //Turns the LEDs off when the key is released. 
  leds(cente-1, cente+1) = CRGB::Black;
  FastLED.show();
}
