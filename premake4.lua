
solution "EmpiricalCpp"
    location "build"
    platforms { "x64" }
    configurations {"Debug", "Release"}
    
    configuration "windows"
        defines {"WIN32"}

dofile("core/projects.lua")
