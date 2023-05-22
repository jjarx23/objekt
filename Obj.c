#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "Obj.h"
#include "Obj.r.h"

static void cstr(void *obj, va_list *arg)
{
    warn("Obj: constructor \n");
}
static void dstr(void *obj)
{
    warn("Obj: destructor \n");
}
static int rpr(const void *b, char *str, int length)
{
    return snprintf(str, length, "Obj %p \n", b);
}
static const char name[] = "Object";
struct ObjClass Class = {sizeof(struct Obj), name, 0, cstr, dstr, rpr};
const void *Obj = &Class;

/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------MetaClasses-------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*
static void mcstr(void *obj, va_list *arg){
    struct ObjClass *o=obj;
    mut(o->size, size_t,va_arg(*arg, size_t));
    mut(o->super, void *,va_arg(*arg, void *));
    //memcpy(&o->cstr,&o->super->cstr, sizeof(struct ObjClass)-((void *)&o->cstr-(void*)o));
    void *fn;
    while((fn=va_arg(*arg, void*))){
        if(fn==((struct ObjClass *)Obj)->cstr)
            o->cstr=va_arg(*arg, void*);
        if(fn==((struct ObjClass *)Obj)->dstr)
            o->dstr=va_arg(*arg, void*);
        if(fn==((struct ObjClass *)Obj)->rpr)
            o->rpr=va_arg(*arg, void*);
        else{
            //printf("Unknown selector\n");
            return;
        }
    }
}
static void mdstr(void *obj){
    printf("Class: can not destroy Class");
}
static int mrpr(const void *b, char *str, int length){
    return printf("Class %p \n", b);
}

struct ObjClass mClass={sizeof(struct ObjClass), &Class, mcstr,mdstr, mrpr};
const struct ObjClass *ObjMetaClass=&mClass;
*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
/*----------------------------Utility---------------------------*/
/*--------------------------------------------------------------*/
/*--------------------------------------------------------------*/
#define size(obj) (((const struct ObjClass *)obj)->size)

void *privateInit(struct ObjClass *type, void *obj, ...)
{
    va_list va;
    va_start(va, obj);
    type->cstr(obj, &va);
    va_end(va);
    return obj;
}

void *neu(const void *clazz, ...)
{
    const struct ObjClass *class = clazz;
    if (class->name == name && clazz != Obj)
        err("Class %p is not %s. Correct name.\n");
    void *child = malloc(size(class));
    memset(child, 0, size(class));
    *(const struct ObjClass **)child = class;
    va_list arg;
    va_start(arg, clazz);
    class->cstr(child, &arg);
    va_end(arg);

    // printf("%p, %p\n", *(void **)child, class);
    return child;
}
void detach(Obj_t child)
{
    if (child)
    {
        if (child->count)
        {
            ((int *)&child->count)[0]--;
        }
        else
        {
            del(child, 0xDA7E);
        }
    }
}
void del(void *child, int magicNo)
{
    if (magicNo != 0xDA7E)
    {
        printf("call to del() is depreciated. Call detach() instaed\n");
        exit(-1);
    }
    const struct ObjClass *class = *(const struct ObjClass **)child;
    class->dstr(child);
    free(child);
}
char differ(const void *a, const void *b)
{
    return a != b;
}
int istypeof(const void *o, const void *type)
{
    const struct ObjClass *class = *(const struct ObjClass **)o;
    if (class == type)
        return 1;
    else
        return class->super ? istypeof(&class->super, type) : 0;
}
/// @brief get a string representation of object "o"
/// @param o candidate object
/// @param buf buffer to write to
/// @param buflen length of buffer
/// @return length of written string
int stringOf(const void *o, char *buf, size_t buflen)
{
    const struct ObjClass *class = *(const struct ObjClass **)o;
    return class->rpr(o, buf, buflen);
}