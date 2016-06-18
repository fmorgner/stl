#ifndef SOPHIA_CONCEPT__IO
#define SOPHIA_CONCEPT__IO

#include <meta/void_t.hpp>

#include <type_traits>
#include <ostream>

namespace sophia
  {

  namespace concept
    {
    /**
     * @ingroup sophia_concept
     * @author Felix Morgner
     * @since 0.1
     *
     * @brief The concept of a type being able to be "<<" shifted onto an std::ostream
     *
     * This type alias is defined for types for which @p operator<<(std::ostream &, Type const &> is defined. The operator must
     * return @p std::ostream @p & to be considered suitable.
     *
     * @tparam Type The type that has to satisfy the concept
     */
    template<typename Type>
    using outputable = meta::void_t<
      std::is_base_of<std::ostream, decltype(operator<<(std::declval<std::ostream &>(), std::declval<Type const &>()))>
    >;

    }

  }

#endif

