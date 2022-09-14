#ifndef LEVEL_THEME_HDR
#define LEVEL_THEME_HDR

#include <memory>
#include <vector>

#include "Background.h"

namespace game
{
    //Data is king.
    //We are going to store everything in share_ptr but still try to use moving more than copying.
    class LevelTheme
    {
    public:
        LevelTheme() = default;
        LevelTheme(LevelTheme&& oldLevelTheme) noexcept;
        LevelTheme(std::shared_ptr<Background>&& background);

        void appendBackgrounds(std::shared_ptr<Background>&& background);
        std::vector<std::shared_ptr<Background>> getBackgrounds() const;
        const std::shared_ptr<Background> const getBackground(unsigned int index) const;
    private:
        std::vector<std::shared_ptr<Background>> _backgrounds;
    };
}

#endif // !LEVEL_THEME_HDR
