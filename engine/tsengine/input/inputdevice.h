/*

	Low level input device layer
	
	The input device class provides an interface between the operating system and the high level input handlers

*/

#pragma once

#include <tscore/delegate.h>
#include <tsengine/platform/window.h>
#include <tsengine/event/messenger.h>
#include <array>
#include "keycodes.h"

namespace ts
{
	enum EMouseButtons : uint16
	{
		eMouseButtonUnknown = 0,
		eMouseButtonLeft	= 1,
		eMouseButtonRight	= 2,
		eMouseButtonMiddle	= 3,
		eMouseXbutton1		= 4,
		eMouseXbutton2		= 5
	};

	struct SInputMouseEvent
	{
		EMouseButtons buttons;
		int16 deltaX = 0;
		int16 deltaY = 0;
		bool isButtonUp = false;
	};

	struct SInputKeyEvent
	{
		EKeyCode keycode;
		bool isKeyUp = false;
	};

	enum EInputEventType
	{
		eInputEventUnknown	 = 0,
		eInputEventMouse	 = 1,
		eInputEventKeyboard	 = 2
	};

	struct SInputEvent
	{
		EInputEventType type;

		union
		{
			SInputMouseEvent mouse;
			SInputKeyEvent key;
		};

		SInputEvent() {}
	};

	class CInputDevice
	{
	public:
	
		typedef Delegate<void(const SInputEvent&)> Callback;
	
	private:
	
		enum EInputMessage : uint16
		{
			eMessageUnknown	= 0,
			eMessageInput	= 1,
			eMessageExit	= 0xffff,
		};

		struct SInputMessage
		{
			EInputMessage code;
			SInputEvent event;

			SInputMessage() {}
			SInputMessage(EInputMessage msgcode) { code = msgcode; }
		};
		
		CWindow* m_pWindow = nullptr;
		CMessageReciever<SInputMessage> m_messageReciever;

		void messageProcedure();

		std::mutex m_exitMutex;
		Callback m_inputCallback;

		CKeyTable m_keyTable;
		
	public:
	
		CInputDevice(CWindow* window);
		~CInputDevice();
		
		void setInputCallback(const Callback& callback) { m_inputCallback = callback; }
		
		bool onWindowInputEvent(const SWindowEventArgs& args);

	};
}