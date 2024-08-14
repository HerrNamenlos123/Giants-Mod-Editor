#pragma once

#include "battery/battery.hpp"
#include "json.hpp"
#include <atomic>

struct ModDesc {
    std::string author;
    std::string version;
};

class App : public b::Application {
public:
    App() = default;
    ~App() override
    {
    }

    ModDesc modDesc;

    void onSetup() override;
    void onUpdate() override;
    void onRender() override;
    void onClose() override;

    void parseModDesc(const std::string& modDescFile);

private:
};
