#pragma once

#include "battery/battery.hpp"
#include "pugixml.hpp"

struct State {
    std::string currentModFolder;
    std::vector<std::string> files;
};

class App : public b::Application {
public:
    App() = default;
    ~App() override
    {
    }

    State state;
    pugi::xml_document modDesc;
    b::cachefile cache;

    void onSetup() override;
    void onUpdate() override;
    void onRender() override;
    void onClose() override;

    void parseModDesc(const std::string& modDescFile);

private:
};
