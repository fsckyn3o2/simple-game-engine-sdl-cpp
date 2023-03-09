nametable_lvl1 = {
    id = 'nametable_lvl1',
    filename = 'lvl1.nametable',
    mapping = {
        {
            name = 'test_engine', graphic = 'hero', position = {x = 0, y = 0, z = 0}, value = 10
        },
        {
            name = 'test_engine', graphic = 'hero', position = {x = 1, y = 0, z = 0}, value = 11
        },
        {
            name = 'test_engine', graphic = 'hero', position = {x = 2, y = 0, z = 0}, value = 12
        },
        {
            name = 'test_engine', graphic = 'hero', position = {x = 3, y = 0, z = 0}, value = 13
        }
    },
    collider = {
        positions = {
            { x = 0, y = 0 }, { x = resolution.width, y = -1},
            { x = 0, y = resolution.height }, { x = resolution.width, y = resolution.height}
        },
        plugin = { 'KILL_HERO' }
    }
}