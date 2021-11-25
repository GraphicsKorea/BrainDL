//
// Created by Danny Jang on 2021/11/23.
//

#include "brain/body.h"

#include <cassert>

#include <iostream>

using namespace brain;

body::body()
        :_use_count{0}
{
}

body::~body()
{
    assert(!_use_count);
}

void body::reference()
{
    ++_use_count;
}

void body::release()
{
    if (!--_use_count) {
        delete this;
    }
}

uint64_t body::use_count()
{
    return _use_count;
}
