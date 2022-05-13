// Arduino Button Library for MCP23017
// Code refactored from https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#include "JC_Button_MCP23017.h"

/*----------------------------------------------------------------------*
/ initialize a Button object and the pin it's connected to.             *
/-----------------------------------------------------------------------*/
void Button::begin()
{
    pinMode(m_pin, m_puEnable ? INPUT_PULLUP : INPUT);
    m_state = digitalRead(m_pin);
    if (m_invert) m_state = !m_state;
    m_time = millis();
    m_lastState = m_state;
    m_changed = false;
    m_lastChange = m_time;
}

/*----------------------------------------------------------------------*
/ returns the state of the button, true if pressed, false if released.  *
/ does debouncing, captures and maintains times, previous state, etc.   *
/-----------------------------------------------------------------------*/
bool Button::read()
{
    uint32_t ms = millis();
    bool pinVal = digitalRead(m_pin);
    if (m_invert) pinVal = !pinVal;
    if (ms - m_lastChange < m_dbTime)
    {
        m_changed = false;
    }
    else
    {
        m_lastState = m_state;
        m_state = pinVal;
        m_changed = (m_state != m_lastState);
        if (m_changed) m_lastChange = ms;
    }
    m_time = ms;
    return m_state;
}

/*----------------------------------------------------------------------*
 * isPressed() and isReleased() check the button state when it was last *
 * read, and return false (0) or true (!=0) accordingly.                *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool Button::isPressed()
{
    return m_state;
}

bool Button::isReleased()
{
    return !m_state;
}

/*----------------------------------------------------------------------*
 * wasPressed() and wasReleased() check the button state to see if it   *
 * changed between the last two reads and return false (0) or           *
 * true (!=0) accordingly.                                              *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool Button::wasPressed()
{
    return m_state && m_changed;
}

bool Button::wasReleased()
{
    return !m_state && m_changed;
}

/*----------------------------------------------------------------------*
 * pressedFor(ms) and releasedFor(ms) check to see if the button is     *
 * pressed (or released), and has been in that state for the specified  *
 * time in milliseconds. Returns false (0) or true (!=0) accordingly.   *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool Button::pressedFor(uint32_t ms)
{
    return m_state && m_time - m_lastChange >= ms;
}

bool Button::releasedFor(uint32_t ms)
{
    return !m_state && m_time - m_lastChange >= ms;
}

/*----------------------------------------------------------------------*
 * lastChange() returns the time the button last changed state,         *
 * in milliseconds.                                                     *
 *----------------------------------------------------------------------*/
uint32_t Button::lastChange()
{
    return m_lastChange;
}

//#######################################################################


/*----------------------------------------------------------------------*
/ initialize a MCP23017_Button object and the pin it's connected to.             *
/-----------------------------------------------------------------------*/
void MCP23017_Button::begin()
{
    mcp_register.pinMode(mcp_pin, mcp_puEnable ? INPUT_PULLUP : INPUT, mcp_invert);
    mcp_state = mcp_register.digitalRead(mcp_pin);
    //if (mcp_invert) mcp_state = !mcp_state; //Software invert moved to hardware invert on MCP23017
    mcp_time = millis();
    mcp_lastState = mcp_state;
    mcp_changed = false;
    mcp_lastChange = mcp_time;
}

/*----------------------------------------------------------------------*
/ returns the state of the button, true if pressed, false if released.  *
/ does debouncing, captures and maintains times, previous state, etc.   *
/-----------------------------------------------------------------------*/
bool MCP23017_Button::read()
{
    uint32_t ms = millis();
    bool pinVal = mcp_register.digitalRead(mcp_pin);
    //if (mcp_invert) pinVal = !pinVal; //Software invert moved to hardware invert on MCP23017
    if (ms - mcp_lastChange < mcp_dbTime)
    {
        mcp_changed = false;
    }
    else
    {
        mcp_lastState = mcp_state;
        mcp_state = pinVal;
        mcp_changed = (mcp_state != mcp_lastState);
        if (mcp_changed) mcp_lastChange = ms;
    }
    mcp_time = ms;
    return mcp_state;
}

/*----------------------------------------------------------------------*
 * isPressed() and isReleased() check the button state when it was last *
 * read, and return false (0) or true (!=0) accordingly.                *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool MCP23017_Button::isPressed()
{
    return mcp_state;
}

bool MCP23017_Button::isReleased()
{
    return !mcp_state;
}

/*----------------------------------------------------------------------*
 * wasPressed() and wasReleased() check the button state to see if it   *
 * changed between the last two reads and return false (0) or           *
 * true (!=0) accordingly.                                              *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool MCP23017_Button::wasPressed()
{
    return mcp_state && mcp_changed;
}

bool MCP23017_Button::wasReleased()
{
    return !mcp_state && mcp_changed;
}

/*----------------------------------------------------------------------*
 * pressedFor(ms) and releasedFor(ms) check to see if the button is     *
 * pressed (or released), and has been in that state for the specified  *
 * time in milliseconds. Returns false (0) or true (!=0) accordingly.   *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool MCP23017_Button::pressedFor(uint32_t ms)
{
    return mcp_state && mcp_time - mcp_lastChange >= ms;
}

bool MCP23017_Button::releasedFor(uint32_t ms)
{
    return !mcp_state && mcp_time - mcp_lastChange >= ms;
}

/*----------------------------------------------------------------------*
 * lastChange() returns the time the button last changed state,         *
 * in milliseconds.                                                     *
 *----------------------------------------------------------------------*/
uint32_t MCP23017_Button::lastChange()
{
    return mcp_lastChange;
}
