#include "WindowGui.h"

WindowGui::WindowGui() : enabled(true), focused(false) {}

WindowGui::~WindowGui() {}

void WindowGui::ToggleEnabled() { enabled = !enabled; }
void WindowGui::ToggleFocused() { focused = !focused; }