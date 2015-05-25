//
// ... Standard header files
//
#include <type_traits>

//
// ... metakanren header files
//
#include <metakanren/list_processing.hpp>



int
main()
{
  using namespace metakanren::list_processing;
  
  using t1 = typename And< int, nil >::type;
  static_assert( std::is_same< t1, nil >::value, "Failed_test!" );

  using t2 = typename And< nil, int >::type;
  static_assert( std::is_same< t2, nil >::value, "Failed_test!" );

  using t3 = typename And< short, int >::type;
  static_assert( std::is_same< t3, int >::value, "Failed_test!" );

  using t4 = typename And< short, int, long long >::type;
  static_assert( std::is_same< t4, long long >::value, "Failed_test!" );

  return 0;
  

}
