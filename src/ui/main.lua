ErrorMessage = nil

function ScanModFolder()
    App.scanModFolder(App.state.currentModFolder)
    -- for _, file in ipairs(files) do
    --     print(file)
    -- end
end

function ParseModDesc()
    App.parseModDesc(App.state.currentModFolder .. "/modDesc.xml")
end

function OpenModFolder()
    App.clearCache()
    App.state.currentModFolder = App.chooseFolder()
    ScanModFolder()
    local status, err = pcall(ParseModDesc)
    if not status then
        ErrorMessage = err
        ImGui.OpenPopup("Error")
        App.clearCache()
    end
end

function writeChanges()
    App.writeChanges()
end

function propertyInput(name, path)
    ImGui.InputText(name, App.getModDescProperty(path), function(value) App.setModDescProperty(path, value) end)
end

function section(text)
    ImGui.Text("")
    ImGui.Text(text)
    ImGui.Separator()
end

function mainContent()
    local state = App.state
    ImGui.Text("Current Mod Folder: " .. state.currentModFolder)
    ImGui.SameLine()
    Button({ text = "Write changes", callback = writeChanges })

    section("Basic")
    propertyInput("Author", "modDesc/author")
    propertyInput("Version", "modDesc/version")

    section("Title")
    local languages = App.getModDescPropertyChildrenNames("modDesc/title")
    for _, lang in ipairs(languages) do
        propertyInput(lang, "modDesc/title/" .. lang)
    end

    section("Description")
    local languages = App.getModDescPropertyChildrenNames("modDesc/description")
    for _, lang in ipairs(languages) do
        propertyInput(lang, "modDesc/description/" .. lang)
    end

    section("Metadata")
    propertyInput("Icon Filename", "modDesc/iconFilename")
end

function mainWindow()
    Button({ text = "Open Mod Folder", callback = OpenModFolder })
    if App.state.currentModFolder ~= "" then
        mainContent()
    end
    if ImGui.BeginPopupModal("Error", 0) then
        if ErrorMessage == nil then
            ImGui.CloseCurrentPopup()
        end

        ImGui.Text(ErrorMessage)
        Button({
            text = "Ok",
            callback = function()
                ErrorMessage = nil
                ImGui.CloseCurrentPopup()
                b.RequestAnimationFrameIn(0)
            end
        })
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
