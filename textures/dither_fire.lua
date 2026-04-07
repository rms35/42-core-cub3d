-- Aseprite Script: dither_fire_flames.lua
-- Applies a checkerboard dither to yellow/orange pixels to simulate transparency

local sprite = app.activeSprite
if not sprite then return end

-- 1. Ensure RGBA mode
if sprite.colorMode ~= ColorMode.RGB then
    app.command.ChangePixelFormat { format="rgb" }
end

-- 2. Flatten layers
app.command.FlattenLayers()
local cel = sprite.cels[1]
if not cel then return end
local image = cel.image

local trans_color = app.pixelColor.rgba(0, 0, 0, 0)

-- 3. Apply Checkerboard Dither to Yellow/Orange pixels
for it in image:pixels() do
    local pixel = it()
    local r = app.pixelColor.rgbaR(pixel)
    local g = app.pixelColor.rgbaG(pixel)
    local b = app.pixelColor.rgbaB(pixel)
    local a = app.pixelColor.rgbaA(pixel)
    
    -- Target bright fire colors (Yellows and Light Oranges)
    if a > 0 and r > 180 and g > 100 then
        -- Checkerboard pattern: if (x + y) is even, make transparent
        if (it.x + it.y) % 2 == 0 then
            it(trans_color)
        end
    end
end

-- 4. Convert back to indexed for XPM optimization (64 colors)
app.command.ChangePixelFormat {
    format="indexed",
    dithering="none",
    ncolors=64
}
