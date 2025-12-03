// Copyright 2025 Viktoria Buzlaeva

#ifndef LIB_LEXEM_LEXEM_H_
#define LIB_LEXEM_LEXEM_H_

#include <string>

enum TypeLexem { Constant, Variable, OpenBracket, ClosedBracket, Function, Operator };

struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    double (*function)(double);

    Lexem(std::string _name = "", TypeLexem _type = Constant, double _value = DBL_MAX, int _priority = -1, double(*_function)(double) = nullptr)
        : name(_name), type(_type), value(_value), priority(_priority), function(_function) {}
    Lexem(const Lexem& other)
        : name(other.name), type(other.type), value(other.value),
        priority(other.priority), function(other.function) {
    }

    Lexem& operator=(const Lexem& other) {
        if (this != &other) {
            name = other.name;
            type = other.type;
            value = other.value;
            priority = other.priority;
            function = other.function;
        }
        return *this;
    }
};

#endif  // LIB_LEXEM_LEXEM_H_
