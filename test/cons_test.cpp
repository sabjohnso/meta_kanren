

//
// ... Standard header files
//
#include <type_traits>

//
// ... metakanren header files
//
#include <metakanren/list_processing.hpp>

using namespace metakanren::list_processing;

int
main()
{
  using t1 = cons<int,nil>;
  
  static_assert( std::is_same< typename car< t1 >::type, int >::value, "Test failed!" );
  static_assert( std::is_same< typename cdr< t1 >::type, nil >::value, "Test failed!" );

  return 0;
  
};
