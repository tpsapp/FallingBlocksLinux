# SW Falling Blocks - SDL2 port

This repository is a Linux/SDL2 port of the original Win32 Falling Blocks example.

## Requirements

- SDL2 development libraries (e.g., libsdl2-dev)
- SDL2_ttf (for SDL message box)

## Build

From the project root directory, run:

```bash
make -f src/Makefile
```

All build artifacts, including the binary, will be placed in the `build/` directory.

## Run

```bash
cd build
./falling_blocks
```

- To generate a screenshot:

```bash
cd build
./falling_blocks --screenshot
```

- To generate a screenshot (headless):

```bash
cd build
SDL_VIDEODRIVER=offscreen ./falling_blocks --screenshot
```

This will write `screenshot.bmp` in the current directory.

## Assets

- The original BMP assets (`blocks.bmp`, `numbers.bmp`, `letters.bmp`) must be in the same folder as the executable.

## Screenshot

Below is a sample screenshot generated with the offscreen mode:

![screenshot](screenshot.bmp)

## Notes

- This port uses SDL2 for windowing, input, timing and rendering.
- The Game Over dialog uses the SDL native message box for cross-platform compatibility.

## Keyboard Shortcuts

- UP or SPACE: Rotate block
- LEFT: Move block left
- RIGHT: Move block right
- DOWN: Move block down
- PAUSE: Pause game
- ESCAPE: Exit game
- F10: Take a screenshot
- F12: Enable/Disable Debug Mode
- TAB: Enable/Disable Cheat Mode

### Debug Mode Shortcuts

- SHIFT: Move block up
- F1: Get a new block
- F2 through F9: Choose specific block
- PageUp: Increase game level
- PageDown: Decrease game level
- Home: Increase row count
- End: Decrease row count

### Cheat Mode Shortcuts

- SHIFT: Move block up
- F1: Get a new block
