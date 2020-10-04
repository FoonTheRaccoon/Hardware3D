#include "Keyboard.h"

bool Keyboard::KeyIsPressed(unsigned int keyCode) const noexcept
{
    return keystates[keyCode];
}

Keyboard::Event Keyboard::ReadKey() noexcept
{
    if (keybuffer.size() > 0u)
    {
        Keyboard::Event e = keybuffer.front();
        keybuffer.pop();
        return e;
    }
    else
    {
        return Event();
    }
}

bool Keyboard::KeyIsEmpty() const noexcept
{
    return keybuffer.empty();
}

void Keyboard::ClearKey() noexcept
{
    keybuffer = std::queue<Event>();
}

char Keyboard::ReadChar() noexcept
{
    if (charbuffer.size() > 0u)
    {
        unsigned char e = charbuffer.front();
        keybuffer.pop();
        return e;
    }
    else
    {
        return 0;
    }
}

bool Keyboard::CharIsEmpty() const noexcept
{
    return charbuffer.empty();
}

void Keyboard::ClearChar() noexcept
{
    charbuffer = std::queue<char>();
}

void Keyboard::ClearAll() noexcept
{
    ClearKey();
    ClearChar();
}

void Keyboard::EnabledAutoRepeat() noexcept
{
    autoRepeatEnabled = true;
}

void Keyboard::DisableAutoRepeat() noexcept
{
    autoRepeatEnabled = false;
}

bool Keyboard::AutoRepeatIsEnabled() const noexcept
{
    return autoRepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char keyCode) noexcept
{
    keystates[keyCode] = true;
    keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, keyCode));
    TrimBuffer(keybuffer);
}

void Keyboard::OnKeyReleased(unsigned char keyCode) noexcept
{
    keystates[keyCode] = false;
    keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, keyCode));
    TrimBuffer(keybuffer);
}

void Keyboard::OnChar(char character) noexcept
{
    charbuffer.push(character);
    TrimBuffer(charbuffer);
}

void Keyboard::ClearState() noexcept
{
    keystates.reset();
}

template<typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
    while (buffer.size() > bufferSize)
    {
        buffer.pop();
    }
}

