errorMessage = nil

function scanModFolder()
    App.scanModFolder(App.state.currentModFolder)
    -- for _, file in ipairs(files) do
    --     print(file)
    -- end
end

function parseModDesc()
    App.parseModDesc(App.state.currentModFolder .. "/modDesc.xml")
end

function openModFolder()
    App.clearCache()
    App.state.currentModFolder = App.chooseFolder()
    scanModFolder()
    local status, err = pcall(parseModDesc)
    if not status then
        errorMessage = err
        ImGui.OpenPopup("Error")
        App.clearCache()
    end
end

function mainContent()
    local state = App.state
    local modDesc = state.modDesc
    ImGui.Text("Current Mod Folder: " .. state.currentModFolder)
    ImGui.Separator()
    ImGui.InputText("Author", modDesc.author, function(str) modDesc.author = str end)
    ImGui.InputText("Version", modDesc.version, function(str) modDesc.version = str end)
end

function mainWindow()
    Button({ text = "Open Mod Folder", callback = openModFolder })
    if App.state.currentModFolder ~= "" then
        mainContent()
    end
    if ImGui.BeginPopupModal("Error", 0) then
        if errorMessage == nil then
            ImGui.CloseCurrentPopup()
        end
            
        ImGui.Text(errorMessage)
        Button({ text="Ok", callback=function() 
            errorMessage = nil
            ImGui.CloseCurrentPopup()
            b.RequestAnimationFrameIn(0)
        end })
        ImGui.EndPopup()
    end
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


