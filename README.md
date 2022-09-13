# HouseLights

An Arduino project, run on a NodeMCU, driving a string of NeoPixels to light up the front of my house.

There are three animation classes to choose from:
  Sprites: random colors from a chosen palette twinkle
  ColorParade: colors from a chosen palette parade across in a loop
  Morse: Twinkling light blink pattern is a message in morse code
  
Given a timezone and position, NTP and Sunset are used to turn the lights on at dusk and off at dawn.
