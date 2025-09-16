
#pragma once

// Key codes for _getch() on Windows console.
namespace Keys {
    // Prefix codes emitted before arrow keys
    constexpr char Prefix0 = 0;
    constexpr char PrefixExt = -32;

    // Arrow key codes (second byte after prefix)
    constexpr char ArrowUp = 72;
    constexpr char ArrowDown = 80;
    constexpr char ArrowLeft = 75;
    constexpr char ArrowRight = 77;
}