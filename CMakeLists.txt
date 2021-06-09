cmake_minimum_required(VERSION 3.19)
project(Java_Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(analyze_to_tokens)
include_directories(def)
include_directories(DFA)
include_directories("Minimize DFA")
include_directories(NFA)

add_executable(Java_Compiler
        analyze_to_tokens/LexicalAnalyzer.cpp
        analyze_to_tokens/LexicalAnalyzer.h
        analyze_to_tokens/Token.h
        def/Imports.h
        def/LexicalAnalyzerScanner.h
        def/RegularDefinition.h
        def/RegularExpression.h
        DFA/GraphAdapter.cpp
        DFA/GraphAdapter.h
        DFA/ResultState.cpp
        DFA/ResultState.h
        DFA/State.cpp
        DFA/State.h
        "Minimize DFA/Minimize.cpp"
        "Minimize DFA/Minimize.h"
        "Minimize DFA/Row.cpp"
        "Minimize DFA/Row.h"
        "Minimize DFA/Table.cpp"
        "Minimize DFA/Table.h"
        NFA/Edge.cpp
        NFA/Edge.h
        NFA/Graph.cpp
        NFA/Graph.h
        NFA/NFA_Generator.cpp
        NFA/NFA_Generator.h
        NFA/Node.cpp
        NFA/Node.h
        src/LexicalAnalyzerScanner.cpp
        src/RegularDefinition.cpp
        src/RegularExpression.cpp
        main.cpp)
