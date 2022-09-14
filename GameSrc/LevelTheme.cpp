#include "LevelTheme.h"

#include <Tempest.h>

namespace game 
{
    LevelTheme::LevelTheme(LevelTheme&& oldLevelTheme) noexcept
    {
        if (this != &oldLevelTheme)
        {
            _backgrounds = std::move(oldLevelTheme._backgrounds);
        }
    }

    LevelTheme::LevelTheme(std::shared_ptr<Background>&& background)
    {
        _backgrounds.emplace_back(std::move(background));
    }

    void LevelTheme::appendBackgrounds(std::shared_ptr<Background>&& background)
    {
        _backgrounds.emplace_back(std::move(background));
    }

    std::vector<std::shared_ptr<Background>> LevelTheme::getBackgrounds() const
    {
        return _backgrounds;
    }

    const std::shared_ptr<Background> const LevelTheme::getBackground(unsigned int index) const
    {
        if ((_backgrounds.size() - 1) < index)
        {
            TEMPEST_CORE_ASSERT("This value doesn't exist in the array of backgrounds.");
        }
        return _backgrounds.at(index);
    }
}