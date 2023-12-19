#pragma once
#include "iostream"
#include "string"

#include "imgui.h"
namespace Application {
struct UI_Spec{
    std::string title;
    ImVec2 size;
    ImVec2 position;
    ImGuiWindowFlags flags;
};
class UI_Screen
{
private:
    UI_Spec m_screen_spec;
public:
    UI_Screen(UI_Spec _spec ) : m_screen_spec(_spec){};
    ~UI_Screen(){};

    virtual void render() = 0;

    /** Getters and setters **/
    inline std::string get_title() const {  return m_screen_spec.title; }
    inline void  set_title(const std::string &newTitle) { m_screen_spec.title = newTitle; }

    inline ImVec2  get_position() const { return m_screen_spec.position; }
    inline void set_position(const ImVec2 &newPosition) {  m_screen_spec.position = newPosition; }

    inline ImGuiWindowFlags get_flags() const { return m_screen_spec.flags; }
    inline void set_fags(ImGuiWindowFlags newFlags) {  m_screen_spec.flags = newFlags; }

    inline ImVec2 get_size() const {  return m_screen_spec.size; }
    inline void set_size(const ImVec2 &newSize) {  m_screen_spec.size = newSize; }

    inline UI_Spec get_screen_spec() const { return m_screen_spec; }
    inline void set_screen_spec(const UI_Spec &newScreen_spec) { m_screen_spec = newScreen_spec; }
};
}// namespace Application
