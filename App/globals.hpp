#pragma once
#include "user.hpp"
#include "FSM.hpp"
#include "database.hpp"
/*GLOBAL VARIABLES*/
namespace Global {

inline auto& db = Core::Database::Instance("localhost", "5432", "imgui", "1234", "project");
inline User system_user;
//FSM definition
#define NUM_OF_STATES 5
inline FSM::eSystemState current_state = FSM::eSystemState::UI_SCREEN1;
inline bool isTransition[NUM_OF_STATES];
//Lockup table with the FSM states
inline std::vector<FSM> StateMachine = {
    {screen1_render, &isTransition[static_cast<int>(FSM::eSystemState::UI_SCREEN1)], 0U, {FSM::eSystemState::UI_SCREEN5, FSM::eSystemState::UI_SCREEN2}},
    {screen2_render, &isTransition[static_cast<int>(FSM::eSystemState::UI_SCREEN2)], 0U, {FSM::eSystemState::UI_SCREEN1, FSM::eSystemState::UI_SCREEN3}},
    {screen3_render, &isTransition[static_cast<int>(FSM::eSystemState::UI_SCREEN3)], 0U, {FSM::eSystemState::UI_SCREEN2, FSM::eSystemState::UI_SCREEN4}},
    {screen4_render, &isTransition[static_cast<int>(FSM::eSystemState::UI_SCREEN4)], 0U, {FSM::eSystemState::UI_SCREEN3, FSM::eSystemState::UI_SCREEN5}},
    {screen5_render, &isTransition[static_cast<int>(FSM::eSystemState::UI_SCREEN5)], 0U, {FSM::eSystemState::UI_SCREEN4, FSM::eSystemState::UI_SCREEN1}}
};
}
