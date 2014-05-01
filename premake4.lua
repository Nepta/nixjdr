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

