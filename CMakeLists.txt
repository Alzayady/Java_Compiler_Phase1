cmake_minimum_required(VERSION 3.15)
project(Project)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")


include_directories(NFA)
include_directories("Minimize DFA")
include_directories(DFA)
include_directories("analyze_to_tokens")
include_directories(def)
include_directories(src)

add_executable(Project main.cpp
        def/Imports.h def/LexicalAnalyzerScanner.h def/RegularDefinition.h def/RegularExpression.h
        src/LexicalAnalyzerScanner.cpp
        analyze_to_tokens/LexicalAnalyzer.cpp analyze_to_tokens/LexicalAnalyzer.h analyze_to_tokens/Token.cpp analyze_to_tokens/Token.h
        DFA/GraphAdapter.cpp DFA/GraphAdapter.h DFA/State.h DFA/State.cpp
        "Minimize DFA/Minimize.h" "Minimize DFA/Table.h" "Minimize DFA/Row.h" "Minimize DFA/Minimize.cpp" "Minimize DFA/Row.cpp" "Minimize DFA/Table.cpp"
        NFA/Node.h NFA/Edge.h NFA/Graph.h NFA/NFA_Generator.h NFA/Edge.cpp NFA/Graph.cpp NFA/NFA_Generator.cpp NFA/Node.cpp
        DFA/ResultState.cpp DFA/ResultState.h
        src/RegularDefinition.cpp src/RegularExpression.cpp
        Phase2/def/InputMatcher.h
        Phase2/def/ParsingTableBuilder.h
        Phase2/src/InputMatcher.cpp
        Phase2/src/ParsingTableBuilder.cpp
        Phase2/userInterface/File.cpp
        Phase2/userInterface/File.h
        )
