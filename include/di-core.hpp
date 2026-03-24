#pragma once
#include "container.hpp"
#include "bean.hpp"
#include "constructor_metadata.hpp"
#include "setter_metadata.hpp"

#define BEAN                                            \
    inline static int _auto_register_T = []() -> int {\
        Bean::registerBeanByType();                     \
        return 0;                                       \
    }()
    
#define BEAN_WITH_QUALIFIER(str)                        \
    inline static int _auto_register_Q = []() -> int {\
        Bean::registerBeanByQuaifier(str);              \
        return 0;                                       \
    }()

#define AUTOWIRED_SETTER(setter_field_type,setter_field_name)\
    void set_##setter_field_name(setter_field_type setter_field_name){\
        this->setter_field_name = setter_field_name;\
    }\
    inline static int _auto_register_setter_##setter_field_name = []()->int{\
         Setter * setr = new SetterMetadata<Bean::bean_type_name,setter_field_type>(&Bean::bean_type_name::set_##setter_field_name);\
         Bean::addSetter(setr);\
         return 0;\
    }()

#define AUTOWIRED_CONSTRUCTOR(...)\
inline static int _auto_register_ctor_##__COUNTER__ = []()->int{    \
    Constructor * ctor = new ConstructorMetadata<Bean::bean_type_name,__VA_ARGS__>();   \
    Bean::addConstructor(ctor); \
    return 0;   \
}()

#define DEFAULT_CONSTRUCTOR \
inline static int _auto_register_default_constructor = []()->int{\
    Constructor * ctor = new ConstructorMetadata<Bean::bean_type_name>();\
    Bean::addConstructor(ctor);\
    return 0;\
}()

// end of file