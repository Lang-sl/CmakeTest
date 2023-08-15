#ifndef UNTITLEDDLL_H
#define UNTITLEDDLL_H

//#ifndef UNTITLEDDLL_GLOBAL_H
//#define UNTITLEDDLL_GLOBAL_H
#if defined(UNTITLEDDLL_LIBRARY)
#  define UNTITLEDDLL_EXPORT __declspec(dllexport)
#else
#  define UNTITLEDDLL_EXPORT __declspec(dllexport)
#endif

class UNTITLEDDLL_EXPORT UntitledDLL
{
public:
    UntitledDLL();
};

extern "C" UNTITLEDDLL_EXPORT int testFormUI(int argc, char* argv[]);

#endif // UNTITLEDDLL_H

