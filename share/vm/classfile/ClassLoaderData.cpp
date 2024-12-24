//
// Created by ziya on 2024/12/23.
//

#include "ClassLoaderData.h"
#include "../memory/Metaspace.h"


ClassLoaderData *ClassLoaderData::_the_null_class_loader_data = NULL;


Metaspace *ClassLoaderData::metaspace_non_null() {
    if (NULL == _metaspace) {
        if (this == the_null_class_loader_data()) {
            // 根类加载器关联的ClassLoaderData
        } else if (is_anonymous()) {
            // 判断是不是匿名类
        } else { // 还少了个else if，判断是不是引用类i先嗯
            INFO_PRINT("zz\n");

            set_metaspace(new Metaspace(Metaspace::StandardMetaspaceType));

        }
    }


    return _metaspace;
}
