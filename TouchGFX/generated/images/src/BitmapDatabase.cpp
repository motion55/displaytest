// 4.21.3 0x8d406b28
// Generated by imageconverter. Please, do not edit!

#include <images/BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_alternate_theme_images_widgets_analogclock_backgrounds_small_plain_dark[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_ANALOGCLOCK_BACKGROUNDS_SMALL_PLAIN_DARK_ID = 0, Size: 240x240 pixels
extern const unsigned char image_alternate_theme_images_widgets_analogclock_hands_small_hour_plain_dark[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_ANALOGCLOCK_HANDS_SMALL_HOUR_PLAIN_DARK_ID = 1, Size: 18x79 pixels
extern const unsigned char image_alternate_theme_images_widgets_analogclock_hands_small_minute_plain_dark[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_ANALOGCLOCK_HANDS_SMALL_MINUTE_PLAIN_DARK_ID = 2, Size: 20x98 pixels
extern const unsigned char image_alternate_theme_images_widgets_analogclock_hands_small_second_plain_dark[]; // BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_ANALOGCLOCK_HANDS_SMALL_SECOND_PLAIN_DARK_ID = 3, Size: 4x100 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_alternate_theme_images_widgets_analogclock_backgrounds_small_plain_dark, 0, 240, 240, 36, 35, 168, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 170, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_alternate_theme_images_widgets_analogclock_hands_small_hour_plain_dark, 0, 18, 79, 7, 19, 4, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 59, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_alternate_theme_images_widgets_analogclock_hands_small_minute_plain_dark, 0, 20, 98, 8, 24, 4, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 73, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_alternate_theme_images_widgets_analogclock_hands_small_second_plain_dark, 0, 4, 100, 1, 1, 2, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 98, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
