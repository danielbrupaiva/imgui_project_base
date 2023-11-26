#pragma once
#include "iostream"
#include "string"

#include "imgui.h"

class UI_Screen
{
private:
    std::string m_title;
    ImVec2 m_size;
    ImVec2 m_position;
    ImGuiWindowFlags m_flags;
public:
    UI_Screen(const std::string _title, ImVec2 _size, ImVec2 _position, ImGuiWindowFlags _flags )
        :m_title(_title),m_size(_size),m_position(_position),m_flags(_flags)
    {}
    ~UI_Screen(){}

    virtual void render() = 0;

    /*Getters and setters*/
    std::string title() const;
    void set_title(const std::string &newTitle);
    ImVec2 size() const;
    void set_size(const ImVec2 &newSize);
    ImVec2 position() const;
    void set_position(const ImVec2 &newPosition);
    ImGuiWindowFlags flags() const;
    void set_fags(ImGuiWindowFlags newFlags);
};
/*Getters and setters*/
inline std::string UI_Screen::title() const {  return m_title; }
inline void UI_Screen::set_title(const std::string &newTitle) { m_title = newTitle; }

inline ImVec2 UI_Screen::position() const { return m_position; }
inline void UI_Screen::set_position(const ImVec2 &newPosition) {  m_position = newPosition; }

inline ImGuiWindowFlags UI_Screen::flags() const { return m_flags; }
inline void UI_Screen::set_fags(ImGuiWindowFlags newFlags) {  m_flags = newFlags; }

inline ImVec2 UI_Screen::size() const {  return m_size; }
inline void UI_Screen::set_size(const ImVec2 &newSize) {  m_size = newSize; }
