nametable_intro = {
    id = 'intro',
    filename = 'common/intro.nametable',
    resolution = {
        width = 6,
        height = 1,
        layers = 1,
        ppu = 100
    },
    mapping = {
            -- position is not used in the engine , it would be the position of the center of the sprite to place it on the nametable with an "offset" in pixel and not in unit
            -- only step attribute is used currently from position parameter.
            { name = 'intro_logo_engine_s1', graphic = 'logo_engine', position = {x = 0, y = 0, z = 0, step = 0}, value = 10},
            { name = 'intro_logo_engine_s2', graphic = 'logo_engine', position = {x = 0, y = 0, z = 0, step = 1}, value = 11},
            { name = 'intro_logo_engine_s3', graphic = 'logo_engine', position = {x = 0, y = 0, z = 0, step = 2}, value = 12},
            { name = 'intro_logo_engine_s4', graphic = 'logo_engine', position = {x = 0, y = 0, z = 0, step = 3}, value = 13},
            { name = 'intro_logo_engine_s5', graphic = 'logo_engine', position = {x = 0, y = 0, z = 0, step = 4}, value = 14},
            { name = 'intro_logo_engine_s6', graphic = 'logo_engine', position = {x = 0, y = 0, z = 0, step = 5}, value = 15}
    },
    renderer = {
        layers = { 'ALL' }
    }
}