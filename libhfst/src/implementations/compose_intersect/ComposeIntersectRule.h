// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef COMPOSE_INTERSECT_RULE_H
#define COMPOSE_INTERSECT_RULE_H

#include "ComposeIntersectFst.h"

namespace hfst
{
  namespace implementations
  {
    class ComposeIntersectRule : public ComposeIntersectFst
    {
    public:
      ComposeIntersectRule(const HfstBasicTransducer &);
      ComposeIntersectRule(void);
      bool known_symbol(size_t symbol);
    protected:
      StringSet symbols;
    };
  }
}

#endif
