ErrorMessage = nil
AddNewEntryProperty = ""
AddNewEntryLanguage = ""

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

function propertyInputText(name, path)
    ImGui.PushID(path)
    Button({
        text = "X",
        callback = function()
            App.removeModDescProperty(path)
        end
    })
    ImGui.SameLine()
    ImGui.InputText(name, App.getModDescProperty(path), function(value)
        App.setModDescProperty(path, value)
    end, 0)
    ImGui.PopID(name)
end

function propertyInputTextMultiline(name, path)
    ImGui.PushID(path)
    Button({
        text = "X",
        callback = function()
            openAddEntryPopup("modDesc/title")
        end
    })
    ImGui.SameLine()
    ImGui.InputTextMultiline(name, App.getModDescProperty(path), function(value)
        App.setModDescProperty(path, value)
    end, ImVec2(0, 0), 0)
    ImGui.PopID(name)
end

function section(text)
    ImGui.Text("")
    ImGui.Text(text)
    ImGui.Separator()
end

function openAddEntryPopup(path)
    AddNewEntryProperty = path
    AddNewEntryLanguage = ""
    ImGui.OpenPopup("Add Entry")
end

function mainContent()
    local state = App.state
    ImGui.Text("Current Mod Folder: " .. state.currentModFolder)
    ImGui.SameLine()
    Button({
        text = "Write changes",
        callback = writeChanges
    })

    section("Basic")
    propertyInputText("Author", "modDesc/author")
    propertyInputText("Version", "modDesc/version")

    section("Title")
    local languages = App.getModDescPropertyChildrenNames("modDesc/title")
    for _, lang in ipairs(languages) do
        propertyInputText(lang, "modDesc/title/" .. lang)
    end
    Button({
        text = "Add Entry",
        callback = function()
            openAddEntryPopup("modDesc/title")
        end
    })

    section("Description")
    local languages = App.getModDescPropertyChildrenNames("modDesc/description")
    for _, lang in ipairs(languages) do
        propertyInputTextMultiline(lang, "modDesc/description/" .. lang)
    end
    Button({
        text = "Add Entry",
        callback = function()
            openAddEntryPopup("modDesc/description")
        end
    })

    section("Metadata")
    propertyInputText("Icon Filename", "modDesc/iconFilename")
end

function mainWindow()
    Button({
        text = "Open Mod Folder",
        callback = OpenModFolder
    })
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
    if ImGui.BeginPopup("Add Entry", 0) then
        ImGui.InputText("Language", AddNewEntryLanguage, function(value)
            AddNewEntryLanguage = value
        end, 0)
        Button({
            text = "Add",
            callback = function()
                App.setModDescProperty(AddNewEntryProperty .. "/" .. AddNewEntryLanguage, "")
                ImGui.CloseCurrentPopup()
            end
        })
        ImGui.EndPopup()
    end
end

function render()
    -- ImGui.ShowDemoWindow()
    -- ImPlot.ShowDemoWindow()
    -- b.requestAnimationFrameIn(0)
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
