
//pbds order statistics tree
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, std::less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_map;
//find_by_order returns iterator (pointing to the i'th element)
//order_of_key  returns size_type (number of strictly smaller elements)
//with all the usual methods in std::set, std::map