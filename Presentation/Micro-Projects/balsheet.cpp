#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>

using Transaction = std::tuple<std::string, long long>;

std::ostream &operator<<(std::ostream &os, const Transaction &rhs) {
    using namespace std;
    const auto prec = os.precision();
    const auto flags = os.flags();
    os.precision(2);
    os.setf(std::ios::fixed);
    os << left << setw(28) << get<0>(rhs) << ':'
       << right << setw(10) << (get<1>(rhs)/100.0);
    os.setf(flags);
    os.precision(prec);
    return os;
}

const std::vector<Transaction> transactions = {
    { Transaction{"Balance April 2015"  ,  63218} },
    { Transaction{"Train ticket"        ,  -1200} },
    { Transaction{"Car repair"          , -13250} },
    { Transaction{"Salary May 2015"     ,  18250} },
    { Transaction{"Utiliy cost"         ,  -6850} }
};

int main() {
    std::vector<Transaction> balance_list;
    std::partial_sum(transactions.cbegin(), transactions.cend(),
                     back_inserter(balance_list),
                     [](const Transaction &e1, const Transaction &e2) {
                         return Transaction{std::get<0>(e2), std::get<1>(e1) + std::get<1>(e2)};
                     });
    for (const auto &be : balance_list) std::cout << be << '\n';
#if 0
    std::copy(balance_list.cbegin(), balance_list.cend(),
              std::ostream_iterator<Transaction>{std::cout, "\n"});
#endif
    std::cout << "-----------------------------\n";
    std::vector<Transaction> transaction_list;
    std::adjacent_difference(balance_list.cbegin(), balance_list.cend(),
                     std::back_inserter(transaction_list),
                     [](const Transaction &e1, const Transaction &e2) {
                         return std::make_tuple(std::get<0>(e1), std::get<1>(e1) - std::get<1>(e2));
                     });
    for (const auto &te : transaction_list) std::cout << te << '\n';
#if 0
    std::copy(transaction_list.cbegin(), transaction_list.cend(),
              std::ostream_iterator<Transaction>{std::cout, "\n"});
#endif

}

