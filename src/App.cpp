#include "App.hpp"

#include "imgui.h"
#include "implot.h"

void App::onSetup()
{
    window->bindEmbeddedLuaScript<"src/ui/main.lua">();
    window->setIcon(
        b::Resource::FromBytes(b::embed<"assets/Giants.png">().vec(), "png"));
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

std::unique_ptr<b::Application> CreateApp()
{
    return std::make_unique<App>();
}
