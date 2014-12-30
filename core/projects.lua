
project "corelib"
    kind "StaticLib"
    language "c++"
    
    files {"src/**.cpp", "include/**.hpp"}
    includedirs {"../thirdparty/include"}
    
		configuration "Debug"
			defines {"DEBUG", "_DEBUG"}
			flags {"Symbols", "ExtraWarnings"}
		
		configuration "Release"
			defines {"RELEASE", "NDEBUG"}
			flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"}

project "coretest"
    kind "ConsoleApp"
    language "c++"
    
    links "corelib"
    
    files {"tests/**.cpp", "tests/**.hpp"}
    includedirs {"../thirdparty/include"}
    