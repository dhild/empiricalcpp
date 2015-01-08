
project "corelib"
    kind "StaticLib"
    language "c++"
    
    files {"src/**.cpp", "src/**.hpp", "include/**.hpp"}
    includedirs {"include", "../thirdparty/include"}

project "coretest"
    kind "ConsoleApp"
    language "c++"
    
    links "corelib"
    
    files {"tests/**.cpp", "tests/**.hpp"}
    includedirs {"include", "../thirdparty/include"}
    
    defines "BOOST_TEST_DYN_LINK"
    
    configuration "linux"
        links "boost_unit_test_framework"
