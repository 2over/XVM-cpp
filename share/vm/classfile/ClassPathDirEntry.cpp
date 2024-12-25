//
// Created by ziya on 2024/12/20.
//

#include "ClassPathDirEntry.h"

ClassFileStream *ClassPathDirEntry::open_stream(string class_name) {
    FILE *file = NULL;
    uint filesize = 0;

    ClassFileStream *stream = new ClassFileStream(class_name);
    stream->set_class_name(class_name);

    string filepath = _dir + class_name + _suffix;

    // 打开class文件
    if (NULL == (file = fopen(filepath.c_str(), "rb"))) {
        perror("fopen fail");
        exit(-1);
    }

    // 获取class文件字节数
    if (0 != fseek(file, 0, SEEK_END)) {
        perror("fseek fail");
        exit(1);
    }

    filesize = (int) ftell(file);
    if (-1 == filesize) {
        perror("ftell fail");
        exit(1);
    }

    stream->create_container(filesize);

    // 将文件内容读入内存
    fseek(file, 0, SEEK_SET);

    fread(stream->container(), sizeof(char), filesize, file);

    fclose(file);

    return stream;
}

ClassFileStream *ClassPathDirEntry::open_file_stream(string path, string class_name) {
    FILE *file = NULL;
    uint filesize = 0;

    ClassFileStream *stream = new ClassFileStream(class_name);
    stream->set_class_name(class_name);

    // 打开class文件
    if (NULL == (file = fopen(path.c_str(), "rb"))) {
        perror("fopen fail");

        exit(1);
    }

    // 获取class文件字节数
    if (0 != fseek(file, 0, SEEK_END)) {
        perror("fseek fail");
        exit(1);
    }

    filesize = (int) ftell(file);
    if (-1 == filesize) {
        perror("ftell fail");
        exit(1);
    }

    stream->create_container(filesize);

    // 将文件内容读入内存
    fseek(file, 0, SEEK_SET);

    fread(stream->container(), sizeof(char), filesize, file);
    fclose(file);
    return stream;
}
