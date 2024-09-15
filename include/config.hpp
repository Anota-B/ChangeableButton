#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(PlayButtonText, std::string, "Play Button Text", "Get an FC!", "Required");
)