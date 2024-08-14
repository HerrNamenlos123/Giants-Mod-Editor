#include "App.hpp"

#include "battery/fs.hpp"
#include "imgui.h"
#include "implot.h"
#include <stdexcept>

void App::onSetup()
{
    window->setTitle("Giants Mod Editor for Farming Simulator");
    window->bindEmbeddedLuaScript<"src/ui/main.lua">();
    window->setIcon(
        b::Resource::FromBytes(b::embed<"assets/Giants.png">().vec(), "png"));
    window->makeFunctionAvailable("chooseFolder", []() {
        b::filedialog s;
        s.directory = true;
        return s.sync_open().string();
    });
    window->makeFunctionAvailable("scanModFolder", [this](const std::string& modFolder) {
        state.files = {};
        for (auto file : std::filesystem::recursive_directory_iterator(
                 b::fs::path(modFolder).std_path())) {
            if (b::fs::is_regular_file(file.path().u8string())) {
                state.files.emplace_back(file.path().string());
            }
        }
    });
    window->makeFunctionAvailable("clearCache", [this]() {
        state = State();
        modDesc = pugi::xml_document();
    });
    window->makeFunctionAvailable(
        "parseModDesc",
        [this](const std::string& modDescFile) { parseModDesc(modDescFile); });
    window->makeFunctionAvailable(
        "ErrorPopup", [](const std::string& modDesc) { ImGui::OpenPopup("Error"); });
    window->makeFunctionAvailable(
        "getModDescProperty",
        [this](const std::string& property) -> std::optional<std::string> {
            if (property.empty()) {
                return {};
            }
            auto node = modDesc.select_node(property.c_str());
            if (!node) {
                return {};
            }
            auto textNode = node.node().text();
            if (!textNode) {
                return {};
            }
            return textNode.get();
        });
    window->makeFunctionAvailable(
        "setModDescProperty",
        [this](const std::string& property, const std::string& value) {
            if (property.empty()) {
                return;
            }
            auto node = modDesc.select_node(property.c_str());
            if (!node) {
                return;
            }
            node.node().text().set(value.c_str());
        });
    window->makeFunctionAvailable("writeChanges", [this]() {
        modDesc.save_file((state.currentModFolder + "/modDesc.xml").c_str());
    });

    auto luaState = window->getLuaState();
    luabridge::getGlobalNamespace(luaState)
        .beginClass<State>("State")
        .addProperty("currentModFolder", &State::currentModFolder)
        .addProperty("files", &State::files)
        .endClass();

    luabridge::getGlobalNamespace(luaState)
        .beginNamespace("App")
        .addProperty("state", &state)
        .endNamespace();
}

void App::onUpdate()
{
}

void App::onRender()
{
}

void App::onClose()
{
}

void App::parseModDesc(const std::string& modDescFile)
{
    pugi::xml_parse_result result = modDesc.load_file(
        modDescFile.c_str(),
        pugi::parse_default | pugi::parse_comments | pugi::parse_ws_pcdata);
    if (!result) {
        throw std::runtime_error("No modDesc.xml file found");
    }

    if (!modDesc.child("modDesc")) {
        throw std::runtime_error("ModDesc file does not contain a <modDesc> child");
    }
}

std::unique_ptr<b::Application> CreateApp()
{
    return std::make_unique<App>();
}
