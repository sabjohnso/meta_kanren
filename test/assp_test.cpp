//
// ... Standard header files
//
#include <cstddef>
#include <type_traits>
#include <iostream>

//
// ... metakanren header files
//
#include <metakanren/list_processing.hpp>


using namespace metakanren::list_processing;


template< typename t >
struct isa
{
  template< typename x >
  struct f : public std::is_same< x, t > {};

  template< typename xs >
  using proc = f< xs >;
};


template< typename  t >
using isa_int = isa< int >::proc< t >;


template< typename  t >
using isa_short = isa< short >::proc< t >;

template< typename  t >
using isa_long_long = isa< long long >::proc< t >;


int
main()
{

  static_assert(   isa< int >::proc< int       >::value, "failed" );
  static_assert( ! isa< int >::proc< short     >::value, "failed to fail!" );
  static_assert( ! isa< int >::proc< long long >::value, "failed to faile!" );
  
  using alist =  typename list<
    cons< short,     datum< size_t, sizeof( short ) > >,
    cons< int,       datum< size_t, sizeof( int )   > >,
    cons< long long, datum< size_t, sizeof( int )   > > >::type;
  
  static_assert( is_list< alist >::value, "" );
  static_assert( is_assoc< alist >::value, "" );
  
  using result0 = typename assp< procedure< isa_int >, alist >::type;
  std::cout << Type< result0 >() << std::endl;
  
  static_assert( std::is_same< result0, cons< int, datum< size_t, sizeof( int ) > > >::value, "Failed test!" );

  using result1 = typename assp< procedure< isa_short >, alist >::type;
  std::cout << Type< result1 >() << std::endl;

  static_assert( std::is_same< result1 , cons< short, datum< size_t, sizeof( short ) > > >::value, "Failed test!" );

						       
  
  
  return 0;
}
