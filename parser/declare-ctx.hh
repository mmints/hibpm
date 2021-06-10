#pragma once

// x occurs at least once
void participation(const char* x);

// x occurs at most once
void atMostOne(const char* x);

// x is the first to occur
void init(const char* x);

// x is the last to occur
void end(const char* x);

// whenever x occurs, y occurs
void respondedExistence(const char* x, const char* y);

// if x occurs, then y occurs after x
void response(const char* x, const char* y);

// if x occurs then y occurs after it without any other x in between
void alternatedResponse(const char* x, const char* y);

// if x occurs then y occurs just after it
void chainResponse(const char* x, const char* y);

// x precedes y
void precedence(const char* x, const char* y);

// whenever y occurs, x precedes y with no other y in between
void alternatedPrecedence(const char* x, const char* y);

// whenever y occurs, x precedes y just before it
void chainPrecedence(const char* x, const char* y);

// x occurs iff y also occurs
void coExistence(const char* x, const char* y);

// if x occurs then y occurs after it, and if y occurs then x precedes y
void succession(const char* x, const char* y);

// x and y occurs alternating without any other x and y in between
void alternatedSuccession(const char* x, const char* y);

// if x occurs then y occurs just after it, and if y occurs then x occurs just before it
void chainSuccession(const char* x, const char* y);

// y does not occur just after x
void notChainSuccession(const char* x, const char* y);

// x never occurs before y
void notSuccession(const char* x, const char* y);

// x and y cannot jointly occur
void notCoExistence(const char* x, const char* y);