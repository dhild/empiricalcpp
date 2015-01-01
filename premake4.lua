
solution "EmpiricalCpp"
    location "build"
    platforms { "x64" }
    configurations {"Debug", "Release"}
    
    configuration "windows"
        defines {"WIN32"}

    configuration "linux"
        buildoptions {"--std=c++11"}

dofile("core/projects.lua")
