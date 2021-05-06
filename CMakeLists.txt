cmake_minimum_required(VERSION 3.19)
project(Project)

set(CMAKE_CXX_STANDARD 14)

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
        NFA/Node.h NFA/Edge.h NFA/Graph.h NFA/NFA_Generator.h NFA/Edge.cpp NFA/Graph.cpp NFA/NFA_Generator.cpp NFA/Node.cpp)