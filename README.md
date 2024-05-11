# mouse-macos

> A MacOS mouse automation module to simulate mouse operations programmatically.

[![Version](https://img.shields.io/badge/version-0.1.0-green.svg)](https://github.com/mathieuschimmerling/mouse-macos)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This module provides a simple API to control the mouse, allowing you to perform actions like click, press, release, set position, and get position on MacOS.

## Installation

```bash
npm install mouse-macos
```

## Usage

Here's how you can use the `mouse-macos` module to automate mouse operations:

```js
import mouse from 'mouse-macos';

// Click at the current position
mouse.click();

// Set mouse position to x=100, y=150 and click
mouse.clickOnPosition(100, 150);

// Get current mouse position
const position = mouse.getPosition();
console.log(`Mouse is at x=${position.x}, y=${position.y}`);
```

## API

- `click()`: Simulate a mouse click at the current position.
- `press()`: Simulate pressing down the mouse button.
- `release()`: Simulate releasing the mouse button.
- `setPosition(x, y)`: Move the mouse to the specified x and y coordinates.
- `getPosition()`: Get the current position of the mouse.
- `clickOnPosition(x, y)`: Move the mouse to a specified position and perform a click.

## License

MIT © [Mathieu Schimmerling](mailto:mathieu.schimmerling@protonmail.com)

---

Feel free to contribute to the project by submitting pull requests or issues.
