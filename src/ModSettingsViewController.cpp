
#include "HMUI/ViewController.hpp"
#include "HMUI/Touchable.hpp"
#include "bsml/shared/BSML.hpp"

#include "main.hpp"
#include "config.hpp"

using namespace BSML;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace HMUI;

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    if(firstActivation){

        self->get_gameObject()->AddComponent<HMUI::Touchable*>();
        auto* container = BSML::Lite::CreateScrollableSettingsContainer(self->get_transform());
        AddConfigValueInputString(container->get_transform(), getModConfig().PlayButtonText);
    }
}