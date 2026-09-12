#pragma once

#include <string_view>

// ANSI Select Graphic Rendition (SGR) sequences used by the terminal logger.
// Keep terminal styling here so the logger palette can be changed in one place.
namespace game::ansi {

inline constexpr std::string_view escape = "\x1b[";
inline constexpr std::string_view reset = "\x1b[0m";

namespace style {
inline constexpr std::string_view bold = "\x1b[1m";
inline constexpr std::string_view dim = "\x1b[2m";
inline constexpr std::string_view italic = "\x1b[3m";
inline constexpr std::string_view underline = "\x1b[4m";
inline constexpr std::string_view reverse = "\x1b[7m";
inline constexpr std::string_view strikethrough = "\x1b[9m";
} // namespace style

namespace foreground {
inline constexpr std::string_view black = "\x1b[30m";
inline constexpr std::string_view red = "\x1b[31m";
inline constexpr std::string_view green = "\x1b[32m";
inline constexpr std::string_view yellow = "\x1b[33m";
inline constexpr std::string_view blue = "\x1b[34m";
inline constexpr std::string_view magenta = "\x1b[35m";
inline constexpr std::string_view cyan = "\x1b[36m";
inline constexpr std::string_view white = "\x1b[37m";
inline constexpr std::string_view defaultColor = "\x1b[39m";
inline constexpr std::string_view brightBlack = "\x1b[90m";
inline constexpr std::string_view brightRed = "\x1b[91m";
inline constexpr std::string_view brightGreen = "\x1b[92m";
inline constexpr std::string_view brightYellow = "\x1b[93m";
inline constexpr std::string_view brightBlue = "\x1b[94m";
inline constexpr std::string_view brightMagenta = "\x1b[95m";
inline constexpr std::string_view brightCyan = "\x1b[96m";
inline constexpr std::string_view brightWhite = "\x1b[97m";
} // namespace foreground

namespace background {
inline constexpr std::string_view black = "\x1b[40m";
inline constexpr std::string_view red = "\x1b[41m";
inline constexpr std::string_view green = "\x1b[42m";
inline constexpr std::string_view yellow = "\x1b[43m";
inline constexpr std::string_view blue = "\x1b[44m";
inline constexpr std::string_view magenta = "\x1b[45m";
inline constexpr std::string_view cyan = "\x1b[46m";
inline constexpr std::string_view white = "\x1b[47m";
inline constexpr std::string_view defaultColor = "\x1b[49m";
inline constexpr std::string_view brightBlack = "\x1b[100m";
inline constexpr std::string_view brightRed = "\x1b[101m";
inline constexpr std::string_view brightGreen = "\x1b[102m";
inline constexpr std::string_view brightYellow = "\x1b[103m";
inline constexpr std::string_view brightBlue = "\x1b[104m";
inline constexpr std::string_view brightMagenta = "\x1b[105m";
inline constexpr std::string_view brightCyan = "\x1b[106m";
inline constexpr std::string_view brightWhite = "\x1b[107m";
} // namespace background

namespace erase {
inline constexpr std::string_view toEndOfLine = "\x1b[0K";
inline constexpr std::string_view entireLine = "\x1b[2K";
inline constexpr std::string_view screen = "\x1b[2J";
} // namespace erase

} // namespace game::ansi
