require "qt-support"

solution "Template"
	configurations {"debug", "release"}

	buildoptions{"-std=c++11"}
	flags {"Unicode"}

	configuration "debug"
		flags {"ExtraWarnings", "Symbols"}

	configuration "release"
		flags {"OptimizeSpeed"}

	project "mainWidget.bin"
		kind "WindowedApp"
		language "C++"
		uses {"QtGui", "QtWidgets", "QtNetwork"}
		buildoptions{"-fPIC"}
		includedirs{"src"}
		files{
			"src/**.h",
			"src/**.cpp",
			"src/**.ui",
			"src/**.qrc"
		}		
		links {"sfml-graphics","sfml-window","sfml-system"}
