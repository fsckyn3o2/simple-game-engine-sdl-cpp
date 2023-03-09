gameConfig = {
    title = "My Game",
    debug = {
        active = 1,
        fontSize = 14,
        alignment = "TOP_LEFT",
        maxWidth = 400,
        maxHeight = 400,
        lineHeight = 15,
        direction = "DOWN",
        padding = 8,
        border = 1,
        borderColor = { r = 255, g = 0, b = 0, a = 255 },
        color = { r = 255, g = 255, b = 200, a = 255 },
        bgColor = { r = 50, g = 50, b = 50, a = 255 },
        renderInterval = 200,
        plugins = {
            "DEBUG_KEY_EVENT"
        }
    },
    plugin = {
        active = 1,
        renderInterval = 200,
        plugins = {
           "SCREEN",
           "MOUSE"
        },
        configs = {
            MOUSE = { graphicId = "cursor_unicorn_1" },
            SCREEN = { numberScreens = "1", files = "intro" }
        }
    }
}