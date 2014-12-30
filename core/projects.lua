
project "corelib"
    kind "StaticLib"
    language "c++"
    
    files {"src/**.cpp", "src/**.hpp", "include/**.hpp"}
    includedirs {"include", "../thirdparty/include"}
    
		configuration "Debug"
			defines {"DEBUG", "_DEBUG"}
			flags {"Symbols", "ExtraWarnings"}
		
		configuration "Release"
			defines {"RELEASE", "NDEBUG"}
			flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"}

os.execute("cxxtestgen --error-printer -o tests/runner.cpp tests/**.hpp")

project "coretest"
    kind "ConsoleApp"
    language "c++"
    
    links "corelib"
    
    files {"tests/**.cpp", "tests/**.hpp"}
    includedirs {"include", "../thirdparty/include"}
    
		configuration "Debug"
			defines {"DEBUG", "_DEBUG"}
			flags {"Symbols", "ExtraWarnings"}
		
		configuration "Release"
			defines {"RELEASE", "NDEBUG"}
			flags {"OptimizeSpeed", "NoFramePointer", "ExtraWarnings", "NoEditAndContinue"}
    