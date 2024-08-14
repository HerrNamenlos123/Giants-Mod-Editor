currentModFolder = nil
files = nil
errorMessage = nil

function clearCache()
    if currentModFolder == nil then
        return
    end
    currentModFolder = nil
end

function scanModFolder()
    files = App.scanModFolder(currentModFolder)
    -- for _, file in ipairs(files) do
    --     print(file)
    -- end
end

function parseModDesc()
    App.parseModDesc(currentModFolder .. "/modDesc.xml")
end

function openModFolder()
    clearCache()
    currentModFolder = App.chooseFolder()
    scanModFolder()
    local status, err = pcall(parseModDesc)
    if not status then
        errorMessage = err
        ImGui.OpenPopup("Error")
    end
end

function mainContent()
    ImGui.Text("Current Mod Folder: " .. currentModFolder)
    ImGui.Text("Author: " .. App.modDesc.author)
end

function mainWindow()
    Button({ text = "Open Mod Folder", callback = openModFolder })
    if currentModFolder ~= nil then
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


