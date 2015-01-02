
solution "EmpiricalCpp"
    location "build"
    platforms { "x64" }
    configurations {"Debug", "Release"}
    
    configuration "windows"
        defines {"WIN32"}

    configuration "linux"
        buildoptions {"--std=c++11"}
    
    configuration "Debug"
        defines {"DEBUG", "_DEBUG"}
        flags {"Symbols", "ExtraWarnings"}
		
    configuration "Release"
        defines {"RELEASE", "NDEBUG"}
        flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"}

dofile("core/projects.lua")
