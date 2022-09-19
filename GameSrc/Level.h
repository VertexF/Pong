#ifndef LEVEL_HDR
#define LEVEL_HDR

#include "LevelTheme.h"
#include "Background.h"
#include <memory>

namespace game
{
    class Level 
    {
        public:
            Level() = default;
            Level(int width, int height);

            void setTheme(const std::shared_ptr<LevelTheme>& theme);
            void setBackground(const std::shared_ptr<Background>& background);
            std::shared_ptr<Background> getBackground() const;

            int getWidth() const { return _width; }
            int getHeight() const { return _height; }
        private:
            int _width;
            int _height;

            std::shared_ptr<Background> _background;
    };
}

#endif // !LEVEL_HDR
