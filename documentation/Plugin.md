# Simple Game Engine :: Plugin

## Core - Plugins

### Plugin
This is an interface to initialize, update and render plugin content with a Renderer and BeanManager.

### LayerPlugin
This class implements a plugin specified for a layer.
Load Layer content and configuration...


## Plugin - Layer

### AnimationLayer

#### Parameters :
- **layers (array of string) :**  index list of layer which compose this animation (each layer is a frame).
- **frequency :** in millisecond it's the delay between 2 pictures
- **loop :** times of loop or -1 for indefinitely
- **delay :** delay between loops
- **delay_layer :** layer used to display item during delay between 2 loops.
- **readdir (array enum) :**
  - **RIGHT** to read from Left to Right
  - **LEFT**  to read from Right to Left
  - **Examples for this property :**
      - {RIGHT} : simple animation (from left to right)
      - {LEFT}  : reverse sens of animation (from right to left)
      - {RIGHT, LEFT} : from left to right and right to left like K2000
      - ...