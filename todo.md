# Editor System

## Components

- `SetType` or similar component allowing the user to change what type something is, should be like the clickable component but with an argument for `Type`

## System

- `SetTypeSystem` the system for setting the type of a block
  - Should iterate over TypeName and Position or something while checking for click, if click try and find whatever holds currently selected and change to that, wooooo

## Bind functions

- `SaveScene` ~~a function that takes all components and saves them to a file~~

# Game System

- Camera lock
- Enemy ai

# Blä

- Make scene deletion queued so lua clean scene doesn't fuck iteration
