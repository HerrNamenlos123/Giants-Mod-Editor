#pragma once

#include "battery/battery.hpp"
#include "json.hpp"
#include <atomic>

class App : public b::Application {
public:
    App() = default;
    ~App() override
    {
    }

    void onSetup() override;
    void onUpdate() override;
    void onRender() override;
    void onClose() override;

private:
};
