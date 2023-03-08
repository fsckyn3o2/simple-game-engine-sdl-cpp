nametable_lvl1 = {
    id = 'nametable_lvl1',
    filename = 'lvl1.nametable',
    mapping = {
        {
            key = 'test_engine', position = {x = 0, y = 0, z = 0}, value = 10
        },
        {
            key = 'test_engine', position = {x = 1, y = 0, z = 0}, value = 11
        },
        {
            key = 'test_engine', position = {x = 2, y = 0, z = 0}, value = 12
        },
        {
            key = 'test_engine', position = {x = 3, y = 0, z = 0}, value = 13
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