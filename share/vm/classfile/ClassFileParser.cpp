//
// Created by ziya on 2024/12/21.
//

#include "ClassFileParser.h"
#include "../oops/CodeAttribute.h"

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


void ClassFileParser::parseMethods(InstanceKlass *klass) {
    // 方法个数
    short count = stream()->get_u2();
    klass->set_methods_count(count);

    INFO_PRINT("开始解析方法信息, 数量: %d\n", count);

    // 解析方法
    for (int i = 0; i < count; ++i) {
        MethodInfo *method = new MethodInfo(klass);
        klass->add_method(method);

        method->set_belong_klass(klass);
        method->set_class_name(klass->name());

        // access flags
        short access_flags = stream()->get_u2();
        method->set_flags(access_flags);

        // name index
        short name_index = stream()->get_u2();
        method->set_name_index(name_index);

        // name
        string name = klass->constant_pool()->get_item_string(name_index);
        method->set_name(name);

        // descriptor index
        short descriptor_index = stream()->get_u2();
        method->set_descriptor_index(descriptor_index);

        /**
         * descriptor
         * 查找方法时要用
         * Hotspot是解析阶段完成的
         */
        method->set_descriptor(klass->constant_pool()->get_item_string(descriptor_index));

        // attribute count
        short attributes_count = stream()->get_u2();
        method->set_attributes_count(attributes_count);

        // 如果是native、 abstract方法，停止解析
        if (access_flags & ACC_NATIVE) {
            ERROR_PRINT("\t 这是一个native方法\n");
            continue;
        }

        // 解析 attributes
        for (int j = 0; j < attributes_count; ++j) {
            short attr_name_index = stream()->get_u2_fast();
            string attr_name = klass->constant_pool()->get_item_string(attr_name_index);

            if ("Code" == attr_name) {
                INFO_PRINT("解析方法属性: %s\n", name.c_str());

                parseCodeAttribute(method);
            } else if ("Exceptions" == attr_name) {
                INFO_PRINT("解析方法属性: Exceptions\n");

                parseSignature(method);
            } else if ("Deprecated" == attr_name) {
                INFO_PRINT("解析方法属性: Deprecated\n");

                parseDeprecated(method);
            } else if ("RuntimeVisibleAnnotations" == attr_name) {
                INFO_PRINT("解析方法属性: RuntimeVisibleAnnotations\n");

                parseRuntimeVisibleAnnotations(method);
            } else {
                ERROR_PRINT("未支持的方法属性: %s\n", attr_name.c_str());
                exit(-1);
            }


        }
    }
}

void ClassFileParser::parseCodeAttribute(MethodInfo *method) {
    InstanceKlass *klass = static_cast<InstanceKlass * >(method->klass());

    CodeAttribute *attribute = new CodeAttribute(method);
    method->set_code_attribute(attribute);

    // name index
    short name_index = stream()->get_u2();
    attribute->set_name_index(name_index);

    string name = klass->constant_pool()->get_item_string(name_index);
    attribute->set_name(name);

    // length
    int length = stream()->get_u4();
    attribute->set_length(length);

    // stack
    short stack = stream()->get_u2();
    attribute->set_max_stack(stack);

    // locals
    short locals = stream()->get_u2();
    attribute->set_max_locals(locals);

    // code length
    int code_length = stream()->get_u4();
    attribute->set_code_length(code_length);

    // code
    CodeStream *code_stream = new CodeStream(code_length);
    attribute->set_codes(code_stream);

    stream()->copy(code_stream->codes(), code_length);

    // exceptions table length
    short exception_table_len = stream()->get_u2();
    attribute->set_exception_table_length(exception_table_len);

    if (0 != exception_table_len) {
        attribute->create_exception_table();

        INFO_PRINT("\t\t 开始解析异常表, size:%d\n ", exception_table_len);

        parseExceptionTable(method);
    }

    // attributes count
    short attr_count = stream()->get_u2();
    attribute->set_attributes_count(attr_count);

    // attributes
    for (int i = 0; i < attr_count; ++i) {
        short name_index = stream()->get_u2_fast();
        string name = klass->constant_pool()->get_item_string(name_index);

        if ("LocalVariableTable" == name) {
            parseLocalVariableTable(method);
        } else if ("LineNumberTable" == name) {
            parseLineNumberTable(method);
        } else if ("StackMaptable" == name) {
            INFO_PRINT("\t\t 开始解析方法属性: StackMapTable\n");
            parseStackMapTable(method);
        } else {
            ERROR_PRINT("未处理的方法属性:%s\n", name.c_str());
            exit(-1);
        }
    }
}

void ClassFileParser::parseLocalVariableTable(MethodInfo *method) {
    InstanceKlass *klass = static_cast<InstanceKlass *>(method->klass());
    CodeAttribute *attribute = static_cast<CodeAttribute *>(method->attribute());

    // name index
    short name_index = stream()->get_u2();
    string name = klass->constant_pool()->get_item_string(name_index);

    INFO_PRINT("\t\t 开始解析方法属性: %s\n", name.c_str());

    // length
    int length = stream()->get_u4();

    // table length
    short table_length = stream()->get_u2();

    LocalVariableTable *table = new LocalVariableTable(length);
    attribute->set_local_variable_table(table);

    table->set_name_index(name_index);
    table->set_table_length(table_length);

    // table item
    for (int i = 0; i < table_length; ++i) {
        // start pc
        short start_pc = stream()->get_u2();
        table->table()[i].start_pc = start_pc;

        // length
        short length = stream()->get_u2();
        table->table()[i].length = length;

        // name index
        short name_index = stream()->get_u2();
        table->table()[i].name_index = name_index;

        // descriptor index
        short descriptor_index = stream()->get_u2();
        table->table()[i].descriptor_index = descriptor_index;

        // index
        short index = stream()->get_u2();
        table->table()[i].index = index;

        INFO_PRINT("\t\t\t start pc : %d, length: %d, name index: %d, descriptor index: %d, inedx: %d\n",
                   start_pc, length, name_index, descriptor_index, index);
    }
}

void ClassFileParser::parseLineNumberTable(MethodInfo *method) {
    InstanceKlass *klass = static_cast<InstanceKlass *>(method->klass());
    CodeAttribute *attribute = static_cast<CodeAttribute *>(method->attribute());

    // name index
    short name_index = stream()->get_u2();

    string name = klass->constant_pool()->get_item_string(name_index);

    INFO_PRINT("\t\t 开始解析方法属性: %s\n", name.c_str());

    // length
    int length = stream()->get_u4();

    // table length
    short table_length = stream()->get_u2();

    LineNumberTable *table = new LineNumberTable(length);
    attribute->set_line_number_table(table);

    table->set_name_index(name_index);
    table->set_name(name);
    table->set_table_length(table_length);

    // table item
    for (int i = 0; i < table_length; ++i) {
        // start pc
        short start_pc = stream()->get_u2();
        table->table()[i].start_pc = start_pc;

        // line number
        short line_number = stream()->get_u2();
        table->table()[i].line_number = line_number;

        INFO_PRINT("\t\t\t start pc: %d, line number: %d\n", start_pc, line_number);
    }
}

void ClassFileParser::parseClassAttribute(InstanceKlass *klass) {
    SourceFile *source_file = new SourceFile;
    klass->set_source_file(source_file);

    // name index
    source_file->set_name_index(stream()->get_u2());

    // length
    source_file->set_length(stream()->get_u4());

    // file_index
    source_file->set_sourcefile_index(stream()->get_u2());
}

void ClassFileParser::parseExceptionTable(MethodInfo *method) {
    CodeAttribute *attribute = static_cast<CodeAttribute *>(method->attribute());

    for (int i = 0; i < attribute->get_exception_table_length(); ++i) {
        // start pc
        short start_pc = stream()->get_u2();
        attribute->exception_table()[i].start_pc = start_pc;

        // end pc
        short end_pc = stream()->get_u2();
        attribute->exception_table()[i].end_pc = end_pc;

        // handler pc
        short handler_pc = stream()->get_u2();
        attribute->exception_table()[i].handler_pc = handler_pc;

        // catch type
        short catch_type = stream()->get_u2();
        attribute->exception_table()[i].catch_type = catch_type;
    }
}

void ClassFileParser::parseStackMapTable(MethodInfo *method) {
    CodeAttribute *attribute = static_cast<CodeAttribute *>(method->attribute());

    StackMapTable *table = new StackMapTable;
    attribute->set_stack_map_table(table);

    // attr name index
    table->set_attr_name_index(stream()->get_u2());

    // attr len
    int len = stream()->get_u4();
    table->set_attr_length(len);

    // 后面的不解析, 跳过
    stream()->inc(len);
}

void ClassFileParser::parseExceptions(MethodInfo *method) {
    Exceptions *exceptions = new Exceptions;
    method->set_exceptions(exceptions);

    // name index
    exceptions->set_name_index(stream()->get_u2());

    // length
    int len = stream()->get_u4();
    exceptions->set_length(len);

    stream()->inc(len);
}


void ClassFileParser::parseSignature(MethodInfo *method) {
    Signature *signature = new Signature;
    method->set_signature(signature);

    // name index
    signature->set_name_index(stream()->get_u2());

    // len
    signature->set_length(stream()->get_u4());

    // signature index
    signature->set_signature_index(stream()->get_u2());
}

void ClassFileParser::parseDeprecated(MethodInfo *method) {
    Deprecated *deprecated = new Deprecated;
    method->set_deprecated(deprecated);

    // name index
    deprecated->set_name_index(stream()->get_u2());

    // len
    deprecated->set_length(stream()->get_u4());
}

void ClassFileParser::parseRuntimeVisibleAnnotations(MethodInfo *method) {
    RuntimeVisibleAnnotations *annotations = new RuntimeVisibleAnnotations;
    method->set_runtime_visible_annotations(annotations);

    // name index
    annotations->set_name_index(stream()->get_u2());

    // len
    int len = stream()->get_u4();
    annotations->set_length(len);

    stream()->inc(len);
}

void ClassFileParser::parseInnerClasses(InstanceKlass *klass) {
    InnerClasses *classes = new InnerClasses;
    klass->set_inner_classes(classes);

    // name index
    classes->set_name_index(stream()->get_u2());

    // len
    int len = stream()->get_u4();
    classes->set_length(len);

    stream()->inc(len);
}
