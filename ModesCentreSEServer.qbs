import qbs

QtApplication {

    name: "Import PDG client/server"

    Depends { name: "Qt"; submodules: ['core', 'network', 'websockets', "quick"] }

    cpp.cxxLanguageVersion: "c++20"
    consoleApplication: false

    Group {
        name: "headers"
        files: [
            "modescentremodel.h",
            "modescentreseserver.h",
            "restapiclient.h",
        ]
    }

    Group {
        name: "sourses"
        files: [
            "main.cpp",
            "modescentremodel.cpp",
            "modescentreseserver.cpp",
            "restapiclient.cpp",
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
