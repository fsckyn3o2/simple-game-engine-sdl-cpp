nametable_title = {
    id = 'title',
    filename = 'common/title.nametable',
    resolution = {
        width = 1,
        height = 4,
        layers = 1,
        ppu = 10
    },
    mapping = {
        {
            name = 'menu_start', graphic = 'menu', position = {x = 0, y = 0, z = 0, step = 0}, value = 10
        }, {
            name = 'menu_option', graphic = 'menu', position = {x = 0, y = 1, z = 0, step = 0}, value = 11
        }, {
            name = 'menu_title', graphic = 'menu', position = {x = 0, y = 2, z = 0, step = 0}, value = 12
        }, {
            name = 'menu_exit', graphic = 'menu', position = {x = 0, y = 3, z = 0, step = 0}, value = 13
        }
    },
    renderer = {
        layers = { 'ALL' },
    }
}