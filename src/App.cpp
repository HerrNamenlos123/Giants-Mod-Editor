#include "App.hpp"

#include "battery/fs.hpp"
#include "imgui.h"
#include "implot.h"
#include <stdexcept>

void App::onSetup()
{
    b::Folders::SetApplicationName("GiantsModEditor");
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
                // If not exists, create it
                auto fragments = b::split(property, "/");
                auto parentFragments = fragments;
                parentFragments.pop_back();
                auto parent = b::join(parentFragments, "/");

                auto parentNode = modDesc.select_node(parent.c_str());
                if (!parentNode) {
                    return;
                }
                parentNode.node().append_child(fragments[fragments.size() - 1].c_str());
                auto newNode = modDesc.select_node(property.c_str());
                if (!newNode) {
                    return;
                }
                newNode.node().text().set(value.c_str());
            }
            node.node().text().set(value.c_str());
        });
    window->makeFunctionAvailable(
        "removeModDescProperty", [this](const std::string& property) {
            if (property.empty()) {
                return;
            }
            auto node = modDesc.select_node(property.c_str());
            if (!node) {
                throw std::runtime_error("Property not found for removing: " + property);
            }
            node.node().parent().remove_child(node.node());
        });
    window->makeFunctionAvailable(
        "getModDescPropertyChildrenNames",
        [this](const std::string& property) -> std::vector<std::string> {
            if (property.empty()) {
                return {};
            }
            auto node = modDesc.select_node(property.c_str());
            if (!node) {
                return {};
            }
            std::vector<std::string> children;
            for (auto& child : node.node().children()) {
                if (child.type() != pugi::node_element) {
                    continue;
                }
                children.emplace_back(child.name());
            }
            return children;
        });
    window->makeFunctionAvailable("writeChanges", [this]() {
        modDesc.save_file((state.currentModFolder + "/modDesc.xml").c_str(),
                          "    ",
                          pugi::format_default | pugi::format_indent);
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

    try {
        state.currentModFolder = cache["currentModFolder"];
    }
    catch (...) {
        throw std::runtime_error("Loading the cache failed");
    }
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
