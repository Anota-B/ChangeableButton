#include "main.hpp"

#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"

#include "config.hpp"
#include "ModSettingsViewController.hpp"

#include "scotland2/shared/modloader.h"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

Configuration &getConfig() {
  static Configuration config(modInfo);
  return config;
}

MAKE_HOOK_MATCH(LevelUIHook, &GlobalNamespace::StandardLevelDetailViewController::DidActivate, void,
 GlobalNamespace::StandardLevelDetailViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    LevelUIHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    GlobalNamespace::StandardLevelDetailView* standardLevelDetailView = self->_standardLevelDetailView;
    UnityEngine::UI::Button* actionButton = standardLevelDetailView->actionButton;
    UnityEngine::GameObject* gameObject = actionButton->get_gameObject();
    HMUI::CurvedTextMeshPro* actionButtonText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro*>();

    actionButtonText->set_text(getModConfig().PlayButtonText);
}


MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
  *info = modInfo.to_c();

  getConfig().Load();

  // File logging
  Paper::Logger::RegisterFileContextId(PaperLogger.tag);

  PaperLogger.info("Completed setup!");
}

MOD_EXTERN_FUNC void late_load() {
    il2cpp_functions::Init();
    getModConfig().Init(modInfo);

    BSML::Init();

    BSML::Register::RegisterSettingsMenu("ChangeableButton", DidActivate, true);

    PaperLogger.info("Installing hooks...");

    INSTALL_HOOK(PaperLogger, LevelUIHook);

    PaperLogger.info("Installed all hooks!");
}