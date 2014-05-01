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

	project "qsfml.bin"
		kind "WindowedApp"
		language "C++"
		uses {"QtGui","QtWidgets"}
		links {"sfml-graphics","sfml-window","sfml-system"}
		buildoptions{"-fPIC"}
		files{
			"src/QTSFML/*.h",
			"src/QTSFML/*.cpp",
			"src/QTSFML/*.ui",
			"src/QTSFML/*.qrc"
		}
		

