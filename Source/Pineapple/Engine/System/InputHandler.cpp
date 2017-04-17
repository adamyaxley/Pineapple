/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

#include <Pineapple/Engine/System/InputHandler.h>

pa::InputHandler::InputHandler(pa::World& world)
	: m_world(world)
{
	m_callbackIterator =
		m_world.registerPreStepInstancesCallback([this](pa::World&, const pa::Input& input) { this->process(input); });
}

pa::InputHandler::~InputHandler()
{
	m_world.unregisterPreStepInstancesCallback(m_callbackIterator);
}

// Process instances
void pa::InputHandler::process(const pa::Input& input)
{
	// Loop over the events
	for (auto&& event : input.events)
	{
		// Call appropriate functions
		switch (event.type)
		{
		case Event::Type::KeyPress: onKeyPress(event.key); break;
		case Event::Type::KeyRelease: onKeyRelease(event.key); break;
		case Event::Type::KeyDown: onKeyDown(event.key); break;
		case Event::Type::CharInput: onCharInput(event.input); break;
		case Event::Type::Quit: onQuit(); break;
		}
	}
}
