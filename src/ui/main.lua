function mainWindow()
    Button({ text = "Rescan", callback = rescan })
    ImGui.SameLine()
    selectedItem = Dropdown({ items = items, selectedItem = selectedItem })
    ImGui.SameLine()
end

function render()
    -- ImGui.ShowDemoWindow()
    -- ImPlot.ShowDemoWindow()
    --b.requestAnimationFrameIn(0)
    Window({
        title = "Main Window",
        left = "0",
        top = "0",
        width = "100%",
        height = "100%",
        border = "0",
        radius = "0",
        flags = ImGuiWindowFlags.NoResize + ImGuiWindowFlags.NoTitleBar,
        callback = mainWindow
    })
end
