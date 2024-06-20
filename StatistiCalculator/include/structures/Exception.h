#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception {
public:
    virtual const char* what() const = 0;
};

class OutOfRange : public Exception {
public:
    const char* what() const;
};

class BadAlloc : public Exception {
public:
    const char* what() const;
};

#endif