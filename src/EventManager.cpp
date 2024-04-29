#include "EventManager.h"
#include "PCH.h"
#include "settings.h"

bool EventManager::IsPermanent(RE::MagicItem* item)
{
    switch (item->GetSpellType()) {
    case RE::MagicSystem::SpellType::kDisease:
    case RE::MagicSystem::SpellType::kAbility:
    case RE::MagicSystem::SpellType::kAddiction: {
        return true;
    }
    default: {
        return false;
    }
    }
};

void EventManager::ApplySpell(RE::Actor* caster, RE::Actor* target, RE::SpellItem* spell)
{
    if (EventManager::IsPermanent(spell)) {
        target->AddSpell(spell);
    }
    else {
        caster->GetMagicCaster(RE::MagicSystem::CastingSource::kInstant)->CastSpellImmediate(spell, false, target, 1.0F, false, 0.0F, nullptr);
    }
};

void EventManager::ApplyStance(RE::SpellItem* a_spell)
{
    auto menu   = RE::UI::GetSingleton();
    auto player = RE::PlayerCharacter::GetSingleton();
    if (!menu->GameIsPaused()) {
        EventManager::ApplySpell(player, player, a_spell);
        logger::debug("player switched stance to: {}", a_spell->GetName());
    }
}

bool EventManager::HasAnyStance()
{
    auto player   = RE::PlayerCharacter::GetSingleton();
    auto settings = Settings::GetSingleton();
    if (player->HasSpell(settings->HighStanceSpell))
        return true;
    else if (player->HasSpell(settings->MidStanceSpell))
        return true;
    else if (player->HasSpell(settings->LowStanceSpell))
        return true;
    else
        return false;
}
