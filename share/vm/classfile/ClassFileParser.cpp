//
// Created by ziya on 2024/12/21.
//

#include "ClassFileParser.h"

ClassFileParser::ClassFileParser(ClassFileStream *stream) {
    _stream = stream;
}

InstanceKlass *ClassFileParser::parseClassFile() {
    InstanceKlass *klass = new InstanceKlass;

    // 魔数
    int magic = stream()->get_u4();
    klass->set_magic(magic);

    // 次版本号
    short minor_version = stream()->get_u2();
    klass->set_minor_version(minor_version);

    // 主版本号
    short major_version = stream()->get_u2();
    klass->set_major_version(major_version);

    // 常量池大小
    // 常量池
    parseConstantPool(klass);

    // 访问权限
    short access_flag = stream()->get_u2();
    klass->set_access_flags(access_flag);

    // 类名
    short this_class = stream()->get_u2();
    klass->set_this_class(this_class);

    string this_class_name = klass->constant_pool()->get_class_name(this_class);
    klass->set_name(this_class_name);

    // 父类名
    short super_class = stream()->get_u2();
    klass->set_super_class(super_class);

    // 接口个数
    klass->set_interfaces_count(stream()->get_u2());

    // 接口
    if (0 != klass->get_interfaces_count()) {
        ERROR_PRINT("接口数不为0\n");
        exit(-1);
    }

    // 属性数量
    // 属性
    parseFields(klass);

    // 方法个数
    // 方法
    parseMethods(klass);

    // 属性个数
    short class_attributes_count = stream()->get_u2();
    klass->set_attributes_count(class_attributes_count);

    // 属性
    for (int i = 0; i < class_attributes_count; ++i) {
        string name = klass->constant_pool()->get_item_string(stream()->get_u2_fast());

        INFO_PRINT("开始解析类属性: %s\n", name.c_str());
        if ("SourceFile" == name) {
            parseClassAttribute(klass);
        } else if ("InnerClasses" == name) {
            parseInnerClasses(klass);
        } else {
            ERROR_PRINT("未做处理的属性: %s\n", name.c_str());

            exit(-1);
        }
    }

    return klass;
}

void ClassFileParser::parseConstantPool(InstanceKlass *klass) {
    // 常量池大小
    short count = stream()->get_u2();
    klass->set_constant_pool_count(count);

    INFO_PRINT("开始解析常量池, 数量：%d\n", count);

    // 常量池
    ConstantPool *pool = new ConstantPool(count);
    klass->set_constant_pool(pool);

    // 解析常量池
    for (int i = 1; i < count; i++) {
        byte tag = stream()->get_u1();

        switch (tag) {
            case JVM_CONSTANT_Utf8: {
                short len = stream()->get_u2();

                // 最后一个字符如果不是\0,输出时会有乱码
                char *str = new char[len + 1];
                *(str + len) = '\0';
                stream()->copy(str, len);

                pool->add_item(i, tag, str);

                break;
            }
            case JVM_CONSTANT_Class:
            case JVM_CONSTANT_String: {
                short str_index = stream()->get_u2();
                pool->add_item(i, tag, str_index);

                break;
            }

            case JVM_CONSTANT_Fieldref:
            case JVM_CONSTANT_Methodref:
            case JVM_CONSTANT_InterfaceMethodref: {
                short class_index = stream()->get_u2();
                short info_index = stream()->get_u2();

                pool->add_item(i, tag, class_index << 16 | info_index);

                break;
            }
            case JVM_CONSTANT_NameAndType: {
                short class_index = stream()->get_u2();
                short info_index = stream()->get_u2();

                pool->add_item(i, tag, class_index << 16 | info_index);

                break;
            }

            default:
                ERROR_PRINT("无法识别的类型: %d\n", tag);
                exit(-1);
        }
    }
}

void ClassFileParser::parseFields(InstanceKlass *klass) {
    // 属性个数
    short count = stream()->get_u2();
    klass->set_fields_count(count);

    INFO_PRINT("开始解析属性信息, 数量: %d\n", count);

    // 解析属性
    for (int i = 0; i < count; ++i) {
        FieldInfo *field = new FieldInfo(klass);

        klass->add_fields(field);

        // access flags
        short access_flags = stream()->get_u2();
        field->set_flags(access_flags);

        // name index
        short name_index = stream()->get_u2();
        field->set_name_index(name_index);

        // name
        string name = klass->constant_pool()->get_item_string(name_index);
        field->set_name(name);

        // descriptor index
        short descriptor_index = stream()->get_u2();
        field->set_descriptor_index(descriptor_index);

        // attribute count
        short attribute_count = stream()->get_u2();
        field->set_attributes_count(attribute_count);

        // 解析 attribute
        if (0 != attribute_count) {
            ERROR_PRINT("\t 类属性的属性不止一个\n");
            exit(-1);
        }
    }
}