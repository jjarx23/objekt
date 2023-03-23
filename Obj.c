#include <stdlib.h>
#include <stdarg.h>
#include "Obj.h"
#include "Obj.r.h"

static void cstr(void *obj, va_list *arg){
    //printf("Obj constructor \n");
}
static void dstr(void *obj){
    //printf("Obj destructor \n");
}
static int rpr(const void *b, char *str, int length){
    return printf("Obj %p \n", b);
}
struct ObjClass Class={sizeof(struct Obj), 0, cstr,dstr, rpr};
const void *Obj=&Class;

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
#define size(obj)(((const struct ObjClass *)obj)->size)

void *privateInit(struct ObjClass *type, void *obj,...){
  va_list va;
  va_start(va, obj);
  type->cstr(obj, &va);
  va_end(va);
  return obj;
}

void *neu(const void *clazz, ...){
    const struct ObjClass *class =clazz;
    void *child=malloc(size(class));
    memset(child, 0, size(class));
*(const struct ObjClass **)child=class;
    va_list arg;
    va_start(arg, clazz);
    class->cstr(child, &arg);
    va_end(arg);
    return child;
}
void del(void *child){
    const struct ObjClass*class=child;
    class->dstr(child);
    free(child);
}
char differ(const void *a, const void *b){
    return a!=b;
}
int istypeof(void *o, void *type){
    struct ObjClass *class =*(const struct ObjClass **)o;
    if(class==type)return 1;
    else return class->super? istypeof(&class->super, type):0;
}