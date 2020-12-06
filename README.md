# lua-wincon

`wincon` is a [Lua](https://www.lua.org/) module for interacting with the console on Windows.

```lua
local wincon = require('wincon')

-- Clear the screen
wincon.clear()

-- Get the console size
local w, h = wincon.size()

-- Move the cursor to the center
wincon.movecursor(w / 2, h / 2)

-- Hide the cursor
wincon.showcursor(false)
```

## Installation
With [Luarocks](https://luarocks.org):

*[not published yet]*

```
luarocks install wincon
```

## API Reference

### `wincon.showcursor([state = true])`
Sets the visibility of the cursor to `state`. On success, returns `true`.

### `wincon.movecursor(x, y)`
Moves the cursor to the given coordinates. On success, returns `true`; otherwise, returns `nil, errmsg`.

### `wincon.clear()`
Clears the screen. On success, returns `true`; otherwise, returns `nil, errmsg`.

### `wincon.size()`
Returns the width and height of the console.
