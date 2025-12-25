import qbs

QtApplication {

    Depends { name: "Qt"; submodules: ['core', 'network', 'websockets', "quick"] }

    consoleApplication: false

    Group {
        name: "headers"
        files: [
            "modescentremodel.h",
            "modescentreseserver.h",
        ]
    }

    Group {
        name: "sourses"
        files: [
            "main.cpp",
            "modescentremodel.cpp",
            "modescentreseserver.cpp",
        ]
    }

    Group {
        name: "qml"
        files: [
            "qml/ModesCentreServer.qml",
        ]
    }

    Group {
        name: "resource"
        files: [
            "modescentreresource.qrc",
        ]
    }
}
