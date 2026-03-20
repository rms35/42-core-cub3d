-- Aseprite Script: cleanup_fire_sprites.lua
-- Removes noise, sets transparency, and converts to optimized XPM

local sprite = app.activeSprite
if not sprite then return end

-- 1. Ensure RGBA mode for processing
if sprite.colorMode ~= ColorMode.RGB then
    app.command.ChangePixelFormat { format="rgb" }
end

-- 2. Flatten layers to a single cel
app.command.FlattenLayers()

local cel = sprite.cels[1]
if not cel then return end
local image = cel.image

-- 3. Replace background (srgb 235,235,235) with transparency
local trans_color = app.pixelColor.rgba(0, 0, 0, 0)

for it in image:pixels() do
    local pixel = it()
    local r = app.pixelColor.rgbaR(pixel)
    local g = app.pixelColor.rgbaG(pixel)
    local b = app.pixelColor.rgbaB(pixel)
    
    -- Tolerance for JPEG artifacts
    if r > 200 and g > 200 and b > 200 then
        it(trans_color)
    end
end

-- 4. Apply a simple Despeckle filter
local copy = image:clone()
for y = 1, image.height - 2 do
    for x = 1, image.width - 2 do
        local pixel = copy:getPixel(x, y)
        if app.pixelColor.rgbaA(pixel) > 0 then
            local neighbors = 0
            for dy = -1, 1 do
                for dx = -1, 1 do
                    if not (dx == 0 and dy == 0) then
                        if app.pixelColor.rgbaA(copy:getPixel(x+dx, y+dy)) > 0 then
                            neighbors = neighbors + 1
                        end
                    end
                end
            end
            if neighbors < 2 then
                image:drawPixel(x, y, trans_color)
            end
        end
    end
end

-- 5. Convert to Indexed Mode (64 colors)
app.command.ChangePixelFormat {
    format="indexed",
    dithering="none",
    ncolors=64
}
