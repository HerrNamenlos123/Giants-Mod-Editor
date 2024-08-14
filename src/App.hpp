#pragma once

#include "battery/battery.hpp"
#include "json.hpp"
#include <atomic>

struct ModDesc {
    std::string author;
    std::string version;
};

struct State {
    std::string currentModFolder;
    std::vector<std::string> files;
    ModDesc modDesc;
};

class App : public b::Application {
public:
    App() = default;
    ~App() override
    {
    }

    State state;

    void onSetup() override;
    void onUpdate() override;
    void onRender() override;
    void onClose() override;

    void parseModDesc(const std::string& modDescFile);

private:
};
