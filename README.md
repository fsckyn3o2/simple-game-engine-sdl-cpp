# Simple Engine


## Documentation

- ### [GraphicAsset](documentation/GraphicAsset.md)
- ### [Plugin](documentation/Plugin.md)
- ### [ Table](documentation/Table.md)



Simple Game Engine is coding in C++ with SDL2.<br/>
Configuration files are based on Lua scripts.

## Structure of project

### Assets

#### Cursors
- common
#### Fonts
- common
#### Graphics
- common
#### Sounds
- common

#### Configs
Configuration of game engine.
- game.lua :
  - debug
    - contains options for debugger to active it and select size of font and plugins attached to debugger
  - plugin
    - contains list of active plugins and options
  - title
    - window title
- input.lua :
  - player_x
    - contains touch mapping for each player (1-4)
    - action linked to enum in game engine, device, port and key code
- network.lua :
  - will contain all network configuration required by game engine for a secured connection to a server
- sound.lua :
  - musicLevel, effectLevel : volume of sound effect for music and effect
  - mode : stereo, mono, surround. (current sound file check require mono mode _(but it's just a check)_)
- video.lua :
  - fullscreen : true/false to active fullscreen mode on start or not
  - resolution : width/height is default resolution for game engine
#### MetaTable
#### NameTable
index.lua of subdirectories contains only the list of nametable enabled.
- common
  - contains default nametable used by game engine by default to start game, generic, title for example
#### PatternTable
#### Screens
contains configuration of screen declared in other configuration file


## Main concept

### Nametable

__A nametable is split in 2 files :__

__- Lua file to setup :__
  - id
  - filename : path of nametable file
  - virtual resolution and number of layers
  - mapping : list of items/layers with a position (in relative reference) and a value used by nametable file
  - renderer mode : list of layer has to be renderered or ALL for all layers

__- nametable file to setup content of nametable:__
  - first line begins with '=' to configuration the type of layer, parameters and the name
  - other lines contains a value


### Screen



