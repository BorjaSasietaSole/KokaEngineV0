#include "WindowGui.h"

WindowGui::WindowGui() : enabled(true) {}

WindowGui::~WindowGui() {}

void WindowGui::ToggleEnabled() { enabled = !enabled; }
void WindowGui::ToggleFocused() { focused = !focused; }