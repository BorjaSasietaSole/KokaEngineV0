#include "WindowGuiConsole.h"

WindowGuiConsole::WindowGuiConsole() {}

WindowGuiConsole::~WindowGuiConsole() {}

WindowGuiConsole::AddLog(const char* log) {
	buf.appendf(log);
	scrollToBottom = true;
}

WindowGuiConsole::Draw() {
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Log", &enabled)) {
		ImGui::End();
		return;
	}
	if (ImGui::Button("Clear")) {
		Clear();
	}
	ImGui::SameLine();
	ImGui::Separator();
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
	ImGui::TextUnformatted(buf.begin());
	if (scrollToBottom) {
		ImGui::SetScrollHereY(1.0f);
	}
	scrollToBottom = true;
	ImGui::EndChild();
	ImGui::End();
}