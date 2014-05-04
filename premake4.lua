require "qt-support"

solution "Template"
	configurations {"debug", "release"}

	buildoptions{"-std=c++11"}
	flags {"Unicode"}

	configuration "debug"
		flags {"ExtraWarnings", "Symbols"}

	configuration "release"
		flags {"OptimizeSpeed"}
	
	project "map.bin"
		kind "ConsoleApp"
		language "C++"

		files {"src/GameBoard/*"}
		links {"sfml-graphics","sfml-window","sfml-system"}

	project "qtsfml.bin"
		kind "WindowedApp"
--		kind "StaticLib"
		language "C++"
		uses {"QtGui","QtWidgets"}
		links {"sfml-graphics","sfml-window","sfml-system"}
		buildoptions{"-fPIC"}
		files{
			"src/Qt-sfml/**.h",
			"src/Qt-sfml/**.cpp",
			"src/Qt-sfml/**.ui",
			"src/Qt-sfml/**.qrc"
		}
--		excludes {"src/Qt-sfml/QTSFML/Main.cpp"}
		

	project "mainWidget.bin"
		kind "WindowedApp"
		language "C++"
		uses {"QtGui","QtWidgets"}
		buildoptions{"-fPIC"}
		files{
			"src/MainWidget/*.h",
			"src/MainWidget/*.cpp",
			"src/MainWidget/*.ui",
			"src/MainWidget/*.qrc"
		}
		files{
			"src/Qt-sfml/**.h",
			"src/Qt-sfml/**.cpp",
			"src/Qt-sfml/**.ui",
			"src/Qt-sfml/**.qrc"
		}
		excludes {"src/Qt-sfml/QTSFML/Main.cpp"}
--		links {"qtsfml.bin"}		
		links {"sfml-graphics","sfml-window","sfml-system"}

