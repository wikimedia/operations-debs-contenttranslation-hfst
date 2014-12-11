#ifndef HEADER_COMPOSE_INTERSECT_UTILITIES_H
#define HEADER_COMPOSE_INTERSECT_UTILITIES_H

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <vector>
#include <algorithm>
#include <utility>

namespace hfst
{
  namespace implementations
  {
    namespace compose_intersect_utilities
    {
      template <class X,class C> class SpaceSavingSet
      {
    protected:
      typedef std::vector<X> XVector;

    public:
      typedef typename XVector::const_iterator const_iterator;
      typedef typename XVector::iterator iterator;

      const_iterator begin(void) const
      { return container_.begin(); }
      
      const_iterator end(void) const
      { return container_.end(); }
      
      iterator begin(void)
      { return container_.begin(); }
      
      iterator end(void)
      { return container_.end(); }
      
      SpaceSavingSet &operator=(const SpaceSavingSet &another)
      {
        container_ = another.container_;
        return *this;
      }
      
      void insert(const X &x)
      {
        iterator least_upper_bound = get_least_upper_bound(x);
        const X &new_x = *least_upper_bound;
        if (least_upper_bound == end() or not (x == new_x))
          { add_value(x,least_upper_bound); }
      }

      const_iterator find(const X &x) const
      {
        const_iterator least_upper_bound = get_least_upper_bound(x);
        if (least_upper_bound == end())
          { return end(); }

        const X &new_x = *least_upper_bound;
        if (new_x != x)
          { return end(); }

        return least_upper_bound;
      }

      void clear(void)
      { container_.clear(); }

      bool has_element(const X &x) const
      { return find(x) != end(); }

      size_t size(void) const
      { return container_.size(); }

    protected:
      static C comparator;

      static struct ReverseCompare
      {
        bool operator() (const X &x1,const X &x2) const
        { return comparator()(x1,x2); }
      } reverse_comp;

      XVector container_;

      const_iterator get_least_upper_bound(const X &x) const
      { 
        const_iterator it = container_.begin();
        for ( ; it != container_.end(); ++it)
          { 
        if (not comparator(*it,x))
          { break; }
          }
        return it;
      }

      iterator get_least_upper_bound(const X &x)
      { 
        iterator it = container_.begin();
        for ( ; it != container_.end(); ++it)
          { 
        if (not comparator(*it,x))
          { break; }
          }
        return it;
      }

      void add_value(const X &x,iterator least_upper_bound)
      { container_.insert(least_upper_bound,x); }
      };

    }
  }
}

#endif // HEADER_COMPOSE_INTERSECT_UTILITIES_H
