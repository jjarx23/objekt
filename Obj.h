#ifndef OBJ_H
#define OBJ_H

#ifdef __cplusplus
extern 'C'
{
#endif

    extern const void *Obj;
    typedef struct Obj *Obj_t;
    // other declarations go here
    char differ(const void *a, const void *b);
    void *neu(const void *clazz, ...);
    void del(void *obj);
    int istypeof(const void *o, const void *type);
    int stringOf(const void *o, char *buf, size_t buflen);
#ifdef __cplusplus
}
#endif
#endif