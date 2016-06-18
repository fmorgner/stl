#ifndef SOPHIA_META__TRAITS
#define SOPHIA_META__TRAITS

#include <concept/io.hpp>

namespace sophia
  {

  namespace meta
    {

    template<typename Type, typename = void>
    struct is_outputable : std::false_type {};

    /**
     * @ingroup sophia_meta
     * @author Felix Morgner
     * @since 0.1
     *
     * @brief Check if a type satifies the concept "outputable"
     *
     * This meta-programming class makes it possible to check if a type satifies the concept "outputable". For types that
     * satisfy this concept, @p operator<<(std::ostream &, Type const &) must be defined.
     *
     * @sa sophia::concept::outputable
     */
    template<typename Type>
    struct is_outputable<Type, concept::outputable<Type>> : std::true_type {};

    }

  }

#endif

