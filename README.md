# lua-windcon

`windcon` is a [Lua](https://www.lua.org/) module for interacting with the console on Windows.

```lua
local windcon = require('windcon')

-- Clear the screen
windcon.clear()

-- Get the console size
local w, h = windcon.size()

-- Move the cursor to the center
windcon.movecursor(w / 2, h / 2)

-- Hide the cursor
windcon.showcursor(false)
```

## Installation
With [Luarocks](https://luarocks.org):

*[not published yet]*

```
luarocks install windcon
```

## API Reference

### `windcon.showcursor([state = true])`
Sets the visibility of the cursor to `state`. On success, returns `true`.

### `windcon.movecursor(x, y)`
Moves the cursor to the given coordinates. On success, returns `true`; otherwise, returns `nil, errmsg`.

### `windcon.clear()`
Clears the screen. On success, returns `true`; otherwise, returns `nil, errmsg`.

### `windcon.size()`
Returns the width and height of the console.
