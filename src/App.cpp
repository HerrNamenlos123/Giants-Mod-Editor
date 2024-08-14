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
    window->makeFunctionAvailable("clearCache", [this]() { state = State(); });
    window->makeFunctionAvailable(
        "parseModDesc",
        [this](const std::string& modDescFile) { parseModDesc(modDescFile); });
    window->makeFunctionAvailable(
        "ErrorPopup", [](const std::string& modDesc) { ImGui::OpenPopup("Error"); });
    window->makeFunctionAvailable(
        "getModDescProperty",
        [this](const std::vector<std::string>& property) -> std::optional<std::string> {
            if (property.empty()) {
                return {};
            }
            auto& doc = state.modDesc;
            pugi::xml_node node = doc.child(property[0]);
            if (!node) {
                return {};
            }
            for (size_t i = 1; i < property.size(); i++) {
                node = node.child(property[i].c_str());
                if (!node) {
                    return {};
                }
            }
            const x = 5;
            return node.value();
        });
    // window->makeFunctionAvailable("writeChanges", [this]() {});
    // window->makeFunctionAvailable("writeChanges", [this]() {});

    auto luaState = window->getLuaState();
    // luabridge::getGlobalNamespace(luaState)
    //     .beginClass<ModDesc>("ModDesc")
    //     .addProperty("author", &ModDesc::author)
    //     .addProperty("version", &ModDesc::version)
    //     .endClass();

    luabridge::getGlobalNamespace(luaState)
        .beginClass<State>("State")
        // .addProperty("modDesc", &State::modDesc)
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
    pugi::xml_document doc;
    pugi::xml_parse_result result
        = doc.load_file(modDescFile.c_str(), pugi::parse_comments);
    if (!result) {
        throw std::runtime_error("No modDesc.xml file found");
    }

    if (!doc.child("modDesc")) {
        throw std::runtime_error("ModDesc file does not contain a <modDesc> child");
    }
    auto modDescTag = doc.child("modDesc");

    if (!modDescTag.child("author")) {
        throw std::runtime_error("<author> field expected in modDesc.xml");
    }
    state.modDesc.author = modDescTag.child_value("author");

    if (!modDescTag.child("version")) {
        throw std::runtime_error("<version> field expected in modDesc.xml");
    }
    state.modDesc.version = modDescTag.child_value("version");
}

std::unique_ptr<b::Application> CreateApp()
{
    return std::make_unique<App>();
}
