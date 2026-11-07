#pragma once
#include <emscripten.h>
#include <iostream>
#include <limits>
#include <streambuf>

EM_ASYNC_JS(int, terminal_read_line, (char* target, int capacity), {
    const line = await Module.readLine();
    const text = line + '\n';
    stringToUTF8(text, target, capacity);
    return Math.min(lengthBytesUTF8(text), capacity - 1);
});

EM_JS(void, terminal_write, (const char* data, int length), {
    Module.write(UTF8ToString(data, length));
});

class BrowserInput : public std::streambuf {
    char buffer[4096];
protected:
    int_type underflow() override {
        if (gptr() < egptr()) return traits_type::to_int_type(*gptr());
        const int count = terminal_read_line(buffer, sizeof(buffer));
        if (count <= 0) return traits_type::eof();
        setg(buffer, buffer, buffer + count);
        return traits_type::to_int_type(*gptr());
    }
public:
    BrowserInput() { setg(buffer, buffer, buffer); }
};

class BrowserOutput : public std::streambuf {
protected:
    std::streamsize xsputn(const char* text, std::streamsize size) override {
        terminal_write(text, static_cast<int>(size));
        return size;
    }
    int_type overflow(int_type value) override {
        if (traits_type::eq_int_type(value, traits_type::eof())) return traits_type::not_eof(value);
        const char character = traits_type::to_char_type(value);
        terminal_write(&character, 1);
        return value;
    }
};

inline void setupBrowserTerminal() {
    static BrowserInput input;
    static BrowserOutput output;
    std::cin.rdbuf(&input);
    std::cout.rdbuf(&output);
    std::cerr.rdbuf(&output);
}

inline void Sleep(unsigned int milliseconds) {
    // Keep the original pauses short in the interactive demo.
    emscripten_sleep(milliseconds > 150 ? 150 : milliseconds);
}

template <typename T>
void readValue(T& value) {
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try again: ";
    }
}
