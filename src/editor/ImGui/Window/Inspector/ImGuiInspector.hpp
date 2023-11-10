#include "ImguiInspector.h"

namespace vg::editor
{
    //--------------------------------------------------------------------------------------
    ImGuiInspector::ImGuiInspector() :
        ImGuiWindow(style::icon::Inspector, "", "Inspector", ImGuiWindow::StartVisible | ImGuiWindow::AddMenuEntry)
    {
    }

    //--------------------------------------------------------------------------------------
    void ImGuiInspector::DrawGUI()
    {
        ImGui::PushID("ImGuiInspector");
        if (ImGui::IconBegin(style::icon::Inspector, getName().c_str(), &m_isVisible))
        {
            auto * object = getSelection()->GetSelectedObject();
            if (nullptr != object)
            {
                ImGuiWindow::displayObject(object);
            }
        }
        ImGui::End();
        ImGui::PopID();
    }
}