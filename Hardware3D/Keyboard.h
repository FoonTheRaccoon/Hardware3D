#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	//Event class to describe keyboard events and states.
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};
	public:
		Event() noexcept
			: type(Type::Invalid), code(0u)
		{}
		Event(Type type, unsigned int code) noexcept
			: type(type), code(code)
		{}
		bool IsPress() const noexcept
		{
			return type == Type::Press;
		}
		bool IsRelease() const noexcept
		{
			return type == Type::Release;
		}
		bool IsInvalid() const noexcept
		{
			return type == Type::Invalid;
		}
		unsigned int GetCode() const noexcept
		{
			return code;
		}
	private:
		Type type;
		unsigned int code;
	};
//----------------------------------------------------------------------//
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard operator=(const Keyboard&) = delete;
	//Key Event (Press) func
	bool KeyIsPressed(unsigned int keyCode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void ClearKey() noexcept;
	//Char Event func
	char ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void ClearChar() noexcept;
	//Clear both Key and Char.
	void ClearAll() noexcept;
	//Autorepeat control func
	void EnabledAutoRepeat() noexcept;
	void DisableAutoRepeat() noexcept;
	bool AutoRepeatIsEnabled() const noexcept;
private:
	void OnKeyPressed(unsigned char keycode) noexcept;
	void OnKeyReleased(unsigned char keycode) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autoRepeatEnabled = false;
	std::bitset<nKeys> keystates;
	std::queue<Event> keybuffer;
	std::queue<char> charbuffer;
};

