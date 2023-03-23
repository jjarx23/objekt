#ifndef OBJ_R_H
#define OBJ_R_H

#include <stdarg.h>
#include <stdlib.h>

#ifdef __cplusplus
extern 'C'{
#endif
struct ObjClass{
    //other members go here
    size_t size;
    struct ObjClass *super;
    void (*cstr)(void *obj, va_list *arg);
    void (*dstr)(void *obj);
    int (*rpr)(const void *b, char *str, int len);
};
struct Obj{
    struct ObjClass *class;
    //other members go here
};

typedef struct ObjClass* ObjClass_t;
typedef struct ObjClass ObjClass_st;
typedef struct Obj Obj_st;

#define mut(x, type,y)(*(type *)&x=(y))
#define supercstr(class, obj, arg)((struct ObjClass*)class)->super->cstr(obj, arg);
#define superdstr(class, obj, arg)(((struct ObjClass*)(struct ObjClass*)class)->super)->dstr(obj);
#define superrpr(class, obj, str, len)((struct ObjClass*)class)->super->rpr(obj, str, len);

#ifdef __cplusplus
}
#endif
#endif
