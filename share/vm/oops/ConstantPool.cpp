//
// Created by ziya on 2024/12/17.
//

#include "ConstantPool.h"

string &ConstantPool::get_item_string(short index) {
    return *(string *) _container[index];
}

string *ConstantPool::get_item_string2(short index) {
    return (string *) _container[index];
}

int ConstantPool::get_item_int(short index) {
    return container()[index];
}

string &ConstantPool::get_class_name_from_fieldref(int index) {
    short class_index = index >> 16;
    return get_item_string(get_item_int(class_index));
}

string &ConstantPool::get_field_name_from_fieldref(int index) {
    short name_and_type_index = index & 0xff;
    short field_name_index = get_item_int(name_and_type_index) >> 16;
    return get_item_string(field_name_index);
}

string &ConstantPool::get_field_descriptor_from_fieldref(int index) {
    short name_and_type_index = index & 0xff;
    short descriptor_name_index = get_item_int(name_and_type_index) & 0xff;
    return get_item_string(descriptor_name_index);
}

string &ConstantPool::get_class_name_from_methodref(int index) {
    short class_index = index >> 16;
    return get_item_string(get_item_int(class_index));
}

string &ConstantPool::get_method_name_from_methodref(int index) {
    short name_and_type_index = index & 0xff;
    short field_name_index = get_item_int(name_and_type_index) >> 16;
    return get_item_string(field_name_index);
}

string &ConstantPool::get_method_descriptor_from_methodref(int index) {
    short name_and_type_index = index & 0xff;
    short descriptor_name_index = get_item_int(name_and_type_index) & 0xff;
    return get_item_string(descriptor_name_index);
}

string &ConstantPool::get_super_class_name(int super_class_index) {
    return get_item_string(get_item_int(super_class_index));
}

string &ConstantPool::get_class_name(int class_index) {
    return get_item_string(get_item_int(class_index));
}