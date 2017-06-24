#ifndef SOPHIA_CONCEPT__TYPE_DESCRIPTOR
#define SOPHIA_CONCEPT__TYPE_DESCRIPTOR

#include "sophia/meta/void_t.hpp"

#include <type_traits>
#include <typeindex>
#include <typeinfo>

namespace sophia::concept
  {

  /**
   * @ingroup sophia_concept
   * @author Felix Morgner
   * @since 0.2
   *
   * @brief The concept of a type representing type information
   *
   * This type alias is defined for types that are either deriving from std::type_info or std::type_index, or are std::type_info
   * and std::type_index themselves.
   *
   * @tparam Type The type that has to satisfy the concept
   */
  template<typename Type>
  using type_descriptor = meta::void_t<
    std::enable_if_t<
      std::disjunction<
        std::is_base_of<std::type_info, Type>,
        std::is_base_of<std::type_index, Type>,
        std::is_same<std::type_info, Type>,
        std::is_same<std::type_index, Type>
      >::value,
      Type
    >
  >;

  }

#endif
