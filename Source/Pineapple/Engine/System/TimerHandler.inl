/*------------------------------------------------------------------------------
  Pineapple Game Engine - Copyright (c) 2011-2017 Adam Yaxley
  This software is licensed under the Zlib license (see license.txt for details)
------------------------------------------------------------------------------*/

template <typename T>
void pa::TimerHandler::startTimer(Time time, T&& callback, bool repeat)
{
	m_timers.emplace(time, time + m_world.getTime(), repeat, std::forward<T>(callback));
}