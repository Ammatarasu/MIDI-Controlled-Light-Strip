# MIDI-Controlled-Light-Strip
An arduino sketch for an esp8266 wemos D1 mini clone


This Sketch can receive MIDI signals via a MIDI Input circuit (Loosely based of of [this article](https://www.notesandvolts.com/2015/02/midi-and-arduino-build-midi-input.html))
I'm just using a 1 resistor and a PC900V octocoupler that I ripped out of an old keyboard's midi input circuit, basically copying the circuit diagram i found in the service manual.
I'm using an esp8266 wemos D1 mini clone as a microcontroller and I'm planning to intergrate it with homeassisant at some point, so it can also just be used as a mood light. 


Current issues:
  - The LED's can be quite "flashy" when playing more aggresively. Which can be distracting or straining on the eyes
  - Sometimes when holding down a note while playing other notes, the one held down slightly jitters, moving the dot around 1 or 2 LEDs in the chain.
  - The colours also don't always behave like they should, sometimes an LED might switch from green to red while holding down a note
  
Plans to fix the issues:
  - Finding a way to dim the leds without slowing down the main loop too much, MIDI.read() needs to be run as often as possible or else the buffer will get filled up and the effect becomes delayed
  - Finding a different way of handeling how a light gets turned on by making the callback handles for midi read not execute the FastLED library but just setting flags that get handeled in the main loop.
  - I have no idea why the colour's dont always work. I have to guess that it's because im trying to execute too much in what is essentially an interrupt function.
   
 
 Future To Do's:
  - Add intergration to homeassistant
  - Add physical mode switch buttons (i.e. Turn on MIDI mode, Turn on Mood mode etc.)
  - Try it using an Esp32 module and see if that would improve performance
  
  
Thank you all for reading this and I hope my adventure can help with someone else's adventure too :)
