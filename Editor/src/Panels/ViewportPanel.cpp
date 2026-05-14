#include "Panels/ViewportPanel.h"

#include "ImGui/imgui.h"

namespace Editor
{
	void ViewportPanel::OnImGuiRender()
	{
		ImGui::Begin("Viewport");
		ImGui::Text("Scene viewport");
		ImGui::End();
	}
}
