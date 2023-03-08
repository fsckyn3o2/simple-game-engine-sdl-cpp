# Simple Game Engine :: xTable

## Core - Table

Tables are simple containers / interpreter of configuration file.

### NameTable

Comes from NES development define background map of pixels (limited by a size).
Here a NameTable is a matrix in 3 dimension (y, x, layer) to map integer values.
NameTable contains :
 - Matrix of value (y,x,layer) -> integer
 - Map of value <integer, GraphicAssetReference> :
   - GraphicAssetReference is a pointer to a part of a SDL_Surface
 - Layers contain parameters for each layer defined in nameTable
 - Resolution (width, height, layers) in unit (not in pixels) to define limited space of nameTable.

A nameTable file is an ASCII file like this :
```
= { type = '<LAYER_PLUGIN_ID>', name = 'TestSolidLayer', myParameter = 'Hello!' }
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10

= { type = '<LAYER_PLUGIN_ID>', name = 'TestEffectLayer' }
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
```

### PatternTable

PatternTable is the same as NameTable but specialize for character with a alignment and an origin.

### LayerTable

A LayerTable contains parameter of layer defined in NameTable file.
This object is encoded inside nameTable with next convention :
 - Line starts with character '='
 - Next character have to define a variable in LUA script

What engine does with that :
 - First character is just to detect a new layer, it will be deleted just after extract the rest of the line.
 - This "rest" have to be a LUA script to define a structure like this :
```
{ type = '<LAYER_PLUGIN_ID>', name = 'TestSolidLayer', myParameter = 'Hello!' }
```
 - This scripte will be prepend by next value to get structure value in C++ variable:
```
LayerParameter = 
``` 
 - Accepted type of value for this structure is STRING only.
 - Values are passed to the LayerPlugin (like AnimationLayer) which use it and update it in list or others expected type/value.


So LayerTable is like C++ container for the LUA structure.

