//
// Created by ziya on 2024/12/20.
//

#ifndef XVM_CPP_DICTIONARY_H
#define XVM_CPP_DICTIONARY_H
#include "../../../include/common.h"

#include <map>

class Dictionary {
private:
    /**
     * key的格式: java/lang/String 而非 java.lang.String
     */
    map<string, long> _container;

public:
    map<string, long>& container() {
        return _container;
    }

    long find(const string& key) {
        map<string, long> ::iterator it = container().find(key);
        if (it == container().end()) {
            return 0;
        }

        return it->second;
    }

    void add(const string& key, long v) {
        container().insert(pair<string, long>(key, v));
    }
};


#endif //XVM_CPP_DICTIONARY_H
