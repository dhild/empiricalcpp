
solution "EmpiricalCpp"
    location "build"
    configurations {"Debug", "Release"}
    
    configuration "windows"
        defines {"WIN32"}

dofile("core/projects.lua")
