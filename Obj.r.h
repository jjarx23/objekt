#ifndef OBJ_R_H
#define OBJ_R_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "Obj.h"
#include "ansi-colors.h"

#ifdef __cplusplus
extern 'C'
{
#endif
    typedef void (*fn_t)();

    struct ObjClass
    {
        // other members go here
        size_t size;
        const char *name;
        const struct ObjClass *super;
        void (*cstr)(void *obj, va_list *arg);
        void (*dstr)(void *obj);
        int (*rpr)(const void *b, char *str, int len);
    };
    struct Obj
    {
        const struct ObjClass *class;
        int const count;
        // other members go here
    };

    typedef struct ObjClass *ObjClass_t;
    typedef struct ObjClass ObjClass_st;
    typedef struct Obj Obj_st;

#define mut(x, type, y) (*(type *)&x = (y))
#define supercstr(class, obj, arg) ((struct ObjClass *)class)->super->cstr(obj, arg);
#define superdstr(class, obj) (((struct ObjClass *)(struct ObjClass *)class)->super)->dstr(obj);
#define superrpr(class, obj, str, len) ((struct ObjClass *)class)->super->rpr(obj, str, len);

    static inline ObjClass_t super(ObjClass_t o)
    {
        return (ObjClass_t)o->super;
    }
    static inline void *classOf(Obj_t o)
    {
        return (void *)o->class;
    }
    static inline const char *className(Obj_t o)
    {
        return o->class->name;
    }
    static inline void mutVoidPtr(void **f, void *n)
    {
        *f = n;
    }
    static inline void attach(Obj_t child)
    {
        if (child)
            ((int *)&child->count)[0]++;
    }
    static inline void fatalErr(char *msg,...)
    {
        printf(RED);
        va_list arg;
        va_start(arg, msg);
        vprintf(msg, arg);
        va_end(arg);
        printf(COLOR_RESET);
        exit(-1);
    }
    static inline void err(char *msg, ...)
    {
        printf(MAG);
        va_list arg;
        va_start(arg, msg);
        vprintf(msg, arg);
        va_end(arg);
        printf(COLOR_RESET);
        exit(-1);
    }
    static inline void warn(char *msg, ...)
    {
        printf(YEL);
        va_list arg;
        va_start(arg, msg);
        vprintf(msg, arg);
        va_end(arg);
        printf(COLOR_RESET);
    }
#ifdef __cplusplus
}
#endif
#endif
