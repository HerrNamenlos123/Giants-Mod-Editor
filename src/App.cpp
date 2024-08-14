#include "App.hpp"

#include "battery/filedialog.hpp"
#include "battery/fs.hpp"
#include "imgui.h"
#include "implot.h"
#include "pugixml.hpp"
#include <stdexcept>

void App::onSetup()
{
    window->bindEmbeddedLuaScript<"src/ui/main.lua">();
    window->setIcon(
        b::Resource::FromBytes(b::embed<"assets/Giants.png">().vec(), "png"));
    window->makeFunctionAvailable("chooseFolder", []() {
        b::filedialog s;
        s.directory = true;
        return s.sync_open().string();
    });
    window->makeFunctionAvailable("scanModFolder", [](const std::string& modFolder) {
        std::vector<std::string> files;
        for (auto file : std::filesystem::recursive_directory_iterator(
                 b::fs::path(modFolder).std_path())) {
            if (b::fs::is_regular_file(file.path().u8string())) {
                files.emplace_back(file.path().string());
            }
        }
        return files;
    });
    window->makeFunctionAvailable(
        "parseModDesc",
        [this](const std::string& modDescFile) { parseModDesc(modDescFile); });
    window->makeFunctionAvailable(
        "ErrorPopup", [](const std::string& modDesc) { ImGui::OpenPopup("Error"); });

    auto state = window->getLuaState();
    luabridge::getGlobalNamespace(state)
        .beginClass<ModDesc>("ModDesc")
        .addProperty("author", &ModDesc::author)
        .addProperty("version", &ModDesc::version)
        .endClass();

    luabridge::getGlobalNamespace(state)
        .beginNamespace("App")
        .addProperty("modDesc", &modDesc)
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
    modDesc.author = modDescTag.child_value("author");

    if (!modDescTag.child("version")) {
        throw std::runtime_error("<version> field expected in modDesc.xml");
    }
    modDesc.version = modDescTag.child_value("version");
}

std::unique_ptr<b::Application> CreateApp()
{
    return std::make_unique<App>();
}
